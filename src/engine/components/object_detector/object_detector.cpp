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
    auto roi_labels = context_.GetModelConfig(model_name_)->mapping_info->GetROILabels();
    std::vector<Tensor3D<float>> output_tensors = 
        nn_interface_->GetOutput(layer_names);

    if (output_tensors.empty())
        return false;
    // Logic to convert tensor to ROIs
    using Dim = Tensor3D<float>::Dimension;
    if (output_tensors.size() == 1 && output_tensors[0].GetLength(Dim::X) == 1 && 
        output_tensors[0].GetLength(Dim::Z) == 6) {
        // the tensor output format is x1,y1,x2,y2,label_id,score
        int n_rois = output_tensors[0].GetLength(Dim::Y);
        for (int i=0; i<n_rois; i++) {
            ROI roi;
            roi.x1 = (size_t) output_tensors[0](0,i,0);
            roi.y1 = (size_t) output_tensors[0](0,i,1);
            roi.x2 = (size_t) output_tensors[0](0,i,2);
            roi.y2 = (size_t) output_tensors[0](0,i,3);
            size_t label_id = (size_t) output_tensors[0](0,i,4);
            if (roi_labels.size() >label_id)
                roi.label = roi_labels[label_id];
            roi.score = output_tensors[0](0,i,5);
            output.push_back(roi);
        }
    }
    //   apply nms
    //   apply labels
    return true;
}
