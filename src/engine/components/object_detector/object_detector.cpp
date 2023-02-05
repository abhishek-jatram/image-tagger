#include "object_detector.hpp"

ObjectDetector::ObjectDetector(Context context, std::string model_name):
       ModelExecutor<ROI>(context, model_name) {
    std::shared_ptr<ModelConfig> model_config = context.GetModelConfig(model_name);
    if (model_config != nullptr) {
        nn_interface_ = std::make_shared<NNInterface>(model_config);
        nn_interface_->Initialize();
    }
}

ObjectDetector::~ObjectDetector(){
}

bool ObjectDetector::Run(cv::Mat image) {
    return nn_interface_->Run(image);
}

bool ObjectDetector::GetOutput(std::vector<ROI>& output) {
    auto layer_names = context_.GetModelConfig(model_name_)->output_layer_names;
    std::vector<Tensor3D<float>> output_tensors = 
        nn_interface_->GetOutput(layer_names);

    if (output_tensors.empty())
        return false;
    // Logic to convert tensor to ROIs
    //   apply nms
    //   apply labels
    return true;
}
