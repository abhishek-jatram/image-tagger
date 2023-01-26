#include "image_tag_filterer.hpp"
#include <algorithm>

ImageTagFilterer::ImageTagFilterer(Context context, std::string& model_name):
    Filterer<Tag>(context, model_name) {
    mapper_ = context.GetMappingInfo(model_name);
}

ImageTagFilterer::~ImageTagFilterer() {
}

void ImageTagFilterer::ApplyThresholding(std::vector<Tag>& tags) {
    auto new_tags_end = std::remove_if(tags.begin(), tags.end(),
        [&](Tag& tag){
            return tag.score < mapper_->GetDisplayThreshold(tag.label);
        }
    );
    tags.erase(new_tags_end, tags.end());
}

std::vector<Tag> ImageTagFilterer::Filter(std::vector<Tag>& tags) {
    // Assuming the tags to be sorted by mapper
    ApplyThresholding(tags);
    return tags;
}