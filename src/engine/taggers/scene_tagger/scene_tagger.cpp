#include "scene_tagger.hpp"

SceneTagger::SceneTagger(std::shared_ptr<ModelExecutor<Tag>> classifier,
    std::shared_ptr<Mapper<Tag>> mapper, std::shared_ptr<Filterer<Tag>> filterer):
        Tagger<Tag>(),classifier_(classifier), mapper_(mapper), filterer_(filterer){
}

SceneTagger::~SceneTagger() {
}

std::vector<Tag> SceneTagger::Execute(cv::Mat image) {
    std::vector<Tag> output_tags;
    // Run classifier
    bool status;
    status = classifier_->Run(image);
    if (!status) return {};

    // Extract tags
    status = classifier_->GetOutput(output_tags);
    if (!status) return {};

    // Map tags
    output_tags = mapper_->Map(output_tags);

    // Filtertags
    output_tags = filterer_->Filter(output_tags);

    return output_tags;
}