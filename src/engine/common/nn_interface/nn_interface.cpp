#include "nn_interface.hpp"

NNInterface::NNInterface(const ModelConfig& model_config): model_config_(model_config) {
    state_ = State::INITIALIZING;
    if(model_config_.platform == ModelPlatform::TENSORFLOWLITE) {
        tflite_backend_ = std::make_unique<TFLiteBackend>(model_config.path);
    }
}

bool NNInterface::Initialize() {
    if (state_ == State::READY_TO_RUN) {
        return true;
    }
    if(model_config_.platform == ModelPlatform::TENSORFLOWLITE) {
        bool status = tflite_backend_->Initialize();
        state_ = status ? State::INITIALIZATION_FAILED : State::READY_TO_RUN;
    }
    else {
        LOG("NNInterface does not support the requested platform (%s) yet", kModelPlatformStr[model_config_.platform]);
    }
    return true;
}

bool NNInterface::Run(std::shared_ptr<Tensor3D<float>> input_tensor) {
    if (state_ != State::READY_TO_RUN && state_ != State::READY_TO_FETCH) {
        LOG("Initialize the model to run it");
        return false;
    }
    state_ = State::RUNNING;
    if(model_config_.platform == ModelPlatform::TENSORFLOWLITE) {
        if (!input_tensor) return false;
        bool status = tflite_backend_->Invoke(input_tensor->data());
        if (!status) return false;
    }
    state_ = State::READY_TO_FETCH;
    return true;
}

std::vector<Tensor3D<float>> 
        NNInterface::GetOutput(const std::vector<std::string> output_layer_names) {
    std::vector<Tensor3D<float>> output;
    if (state_ == State::RUNNING) {
        LOG("Wait for model exeuction to complete. Retry fetching output in sometime");
        return {};
    }
    if (state_ == State::INITIALIZATION_FAILED) {
        LOG("Cannot fetch output, model initilization failed");
        return {};
    }
    if (state_ == State::READY_TO_RUN) {
        LOG("Results already fetched");
    }

    if(model_config_.platform == ModelPlatform::TENSORFLOWLITE) {
        float* data;
        size_t w,h,d;
        for (std::string layer_name: output_layer_names) {
            bool status = tflite_backend_->FetchOutput(layer_name, &data, w, h, d);
            if (!status) {
                LOG("The requested layer %s cannot be fetched, aborting fetching of layers", layer_name.c_str());
                return {};
            }
            Tensor3D<float> output_tensor = 
                Tensor3D<float>(w,h,d, data, true);
            output.push_back(output_tensor);
            delete data;
        }
    }

    state_ = State::READY_TO_RUN;
    return output;
}

NNInterface::~NNInterface() {
    state_ = State::NONE;
}