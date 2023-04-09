#include "image_classifier.hpp"

ImageClassifier::ImageClassifier(Context context, std::string model_name):
       ModelExecutor<Tag>(context, model_name) {
    std::shared_ptr<ModelConfig> model_config = context.GetModelConfig(model_name);
    if (model_config != nullptr) {
        nn_interface_ = std::make_shared<NNInterface>(model_config);
        nn_interface_->Initialize();
    }
}

ImageClassifier::~ImageClassifier(){
}

bool ImageClassifier::Run(cv::Mat image) {
    return nn_interface_->Run(image);
}

bool ImageClassifier::GetOutput(std::vector<Tag>& output) {
    auto layer_names = context_.GetModelConfig(model_name_)->output_layer_names;
    std::vector<Tensor3D<float>> output_tensors = 
        nn_interface_->GetOutput(layer_names);

    if (output_tensors.empty())
        return false;
    
    float* data = output_tensors[0].data();
    size_t data_size = output_tensors[0].size();
    std::vector<float> flattened_output {data, data + data_size};
    bool status = convertToBaselineTags(flattened_output, output);
    return status;
}

bool ImageClassifier::convertToBaselineTags(std::vector<float> probs, std::vector<Tag>& output) {
    std::shared_ptr<MappingInfo> mapping_info = context_.GetModelConfig(model_name_)->mapping_info;
    std::vector<std::string> baseline_tags = mapping_info->GetBaselineTags();

    if (baseline_tags.size() != probs.size())
        return false;

    for (int i=0; i<baseline_tags.size(); i++) {
        Tag tag;
        tag.label = baseline_tags[i];
        tag.score = probs[i];
        output.push_back(tag);
    }
    return true;
}

bool ImageClassifier::Finetune(std::vector<Tag>& final_output) {
    return true;
}
