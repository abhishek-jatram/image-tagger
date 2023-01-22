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

bool NNInterface::GetOutput(std::shared_ptr<Tensor3D<float>>& output_tensor) {
    if (state_ == State::RUNNING) {
        LOG("Wait for model exeuction to complete. Retry fetching output in sometime");
        return false;
    }
    if (state_ == State::INITIALIZATION_FAILED) {
        LOG("Cannot fetch output, model initilization failed");
        return false;
    }
    if (state_ == State::READY_TO_RUN) {
        LOG("Results already fetched");
    }

    if(model_config_.platform == ModelPlatform::TENSORFLOWLITE) {
        float* data;
        size_t w,h,d;
        bool status = tflite_backend_->FetchOutput(&data, w, h, d);
        if (!status) return status;
        output_tensor = std::make_shared<Tensor3D<float>>(w,h,d, data);
    }

    state_ = State::READY_TO_RUN;
    return true;
}

NNInterface::~NNInterface() {
    state_ = State::NONE;
}