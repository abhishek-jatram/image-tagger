#include "nn_interface.hpp"
#include "utils/image_utils.hpp"

NNInterface::NNInterface(const std::shared_ptr<ModelConfig>& model_config){
    model_config_ = model_config;
    state_ = State::INITIALIZING;
    if(model_config_->platform == ModelPlatform::TENSORFLOWLITE) {
        tflite_backend_ = std::make_unique<TFLiteBackend>(model_config->path);
    }
    else if(model_config_->platform == ModelPlatform::OPENCV) {
        OpenCVBackend::ModelType model_type = OpenCVBackend::ModelType::NONE;
        if (model_config_->type == HOG_BASED_PEOPLE_DETECTOR) {
            model_type = OpenCVBackend::ModelType::HOG_BASED_PEOPLE_DETECTOR;
        }
        opencv_backend_ = std::make_unique<OpenCVBackend>(model_type, model_config->path);
    }
}

NNInterface::~NNInterface() {
    state_ = State::NONE;
}

bool NNInterface::Initialize() {
    if (state_ == State::READY_TO_RUN) {
        return true;
    }
    if(model_config_->platform == ModelPlatform::TENSORFLOWLITE) {
        bool status = tflite_backend_->Initialize();
        state_ = status ? State::READY_TO_RUN : State::INITIALIZATION_FAILED;
    }
    else if(model_config_->platform == ModelPlatform::OPENCV) {
        bool status = opencv_backend_->Initialize();
        state_ = status ? State::READY_TO_RUN : State::INITIALIZATION_FAILED;
    }
    else {
        LOG("NNInterface does not support the requested platform (%s) yet", kModelPlatformStr[static_cast<int>(model_config_->platform)].c_str());
        state_ = State::INITIALIZATION_FAILED;
    }
    return true;
}

bool NNInterface::Run(std::shared_ptr<Tensor3D<float>> input_tensor) {
    if(model_config_->platform == ModelPlatform::TENSORFLOWLITE) {
        if (!input_tensor) return false;
        bool status = tflite_backend_->Invoke(input_tensor->data());
        if (!status) {
            state_ = State::READY_TO_RUN;
            return false;
        }
    }
    state_ = State::READY_TO_FETCH;
    return true;
}

cv::Mat NNInterface::preprocess_image(cv::Mat image) {
    Shape input_shape = model_config_->input_shape;
    if (input_shape.width == -1 && input_shape.height == -1) {
        resize_factor_x = 1;
        resize_factor_y = 1;
    }
    if (input_shape.width == -1) {
        resize_factor_y = (double) input_shape.height / image.rows;
        resize_factor_x = resize_factor_y;
    }
    else if (input_shape.height == -1) {
        resize_factor_x = (double) input_shape.width / image.cols;
        resize_factor_y = resize_factor_x;
    }
    else {
        resize_factor_x = (double) input_shape.width / image.cols;
        resize_factor_y = (double) input_shape.height / image.rows;
    }

    cv::resize(image, image, cv::Size(), resize_factor_x, resize_factor_y);
    // handle depth
    return image;
}


bool NNInterface::Run(cv::Mat& input_image) {
    // Resize image to input size if not there already
    input_image = preprocess_image(input_image);
    if (state_ == State::INITIALIZATION_FAILED) {
        LOG("Cannot run the model, initialization failed");
        return false;
    }
    if (state_ != State::READY_TO_RUN && state_ != State::READY_TO_FETCH) {
        LOG("Initialize the model to run it");
        return false;
    }
    state_ = State::RUNNING;
    if(model_config_->platform == ModelPlatform::OPENCV) {
        if (input_image.empty()) return false;
        bool status = opencv_backend_->Invoke(input_image);
        if (!status) {
            state_ = State::READY_TO_RUN;
            return false;
        }
        state_ = State::READY_TO_FETCH;
        return true;
    }
    std::shared_ptr<Tensor3D<float>> input_tensor;
    bool status = ImageUtils::ConvertMatToTensor3D(input_image, input_tensor);
    if (!status) return false;

    return Run(input_tensor);    
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

    if(model_config_->platform == ModelPlatform::TENSORFLOWLITE) {
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
    else if(model_config_->platform == ModelPlatform::OPENCV) {
        if (opencv_backend_->GetOutputType() == OpenCVBackend::OutputType::RECTS) {
            std::vector<cv::Rect> rois;
            std::vector<int> label_ids;
            std::vector<double> scores;
            bool status = opencv_backend_->GetOutput(rois, label_ids, scores);
            if (!status) {
                LOG("Failed to fetch output from the model %s", model_config_->path.c_str());
                return {};
            }
            return {get_tensor_from_rects(rois, label_ids, scores)};
        }
    }
    state_ = State::READY_TO_RUN;
    return output;
}

Tensor3D<float> NNInterface::get_tensor_from_rects(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores) {
    int n_rects = rois.size();
    // x1,y1,x2,y2,class,score
    Tensor3D<float> output_tensor(1,n_rects,6);
    for (int i=0; i<n_rects; i++) {
        output_tensor(0,i,0) = rois[i].x / resize_factor_x;
        output_tensor(0,i,1) = rois[i].y / resize_factor_y;
        output_tensor(0,i,2) = (rois[i].x + rois[i].width) / resize_factor_x;
        output_tensor(0,i,3) = (rois[i].y + rois[i].height) / resize_factor_y;
        output_tensor(0,i,4) = (label_ids.size() == n_rects ? label_ids[i] : 0);
        output_tensor(0,i,5) = (scores.size() == n_rects ? scores[i] : 0);
    }
    return output_tensor;
}
