#include "image_tag_mapper.hpp"
#include <algorithm>

ImageTagMapper::ImageTagMapper(Context context, std::string model_name): Mapper<Tag>(context, model_name) {
    mapper = context.GetMappingInfo(model_name);
}

ImageTagMapper::~ImageTagMapper() {
}

std::vector<Tag> ImageTagMapper::FetchDisplayTags() {
    std::vector<Tag> display_tags;
    std::vector<std::string> display_tag_labels = mapper->GetDisplayTags();
    for (int i=0; i<display_tag_labels.size(); i++) {
        label_to_tag_idx[display_tag_labels[i]] = i;
        Tag display_tag;
        display_tag.label = display_tag_labels[i];
        display_tag.score = 0;
        display_tags.push_back(display_tag);
    }
    return display_tags;
}

void ImageTagMapper::ComputeScores(std::vector<Tag>& display_tags, std::vector<Tag>& base_tags) {
    std::unordered_map<std::string, int> label_to_tag_idx;
    for (int i=0; i<display_tags.size(); i++) {
        label_to_tag_idx[display_tags[i].label] = i;
    }

    // display tag score = SUM (baseline scores of display tag) / no. of baseline tags
    for (int i=0 ; i<base_tags.size(); i++) {
        for (std::string display_tag: mapper->GetDisplayTagsOf(base_tags[i].label)) {
            int display_id = label_to_tag_idx[display_tag];
            display_tags[display_id] += base_tags[i].score;
        }
    }

    for (int i=0; i<display_tags.size(); i++) {
        int n_baselines = mapper->NoOfBaselineTagsOf(display_tags[i]);
        if (n_baselines)
            display_tag[i].score /= n_baselines;
    }
}

void ImageTagMapper::SortDisplayTags(std::vector<Tag>& display_tags) {
    std::sort(display_tags.begin(), display_tags.end(),
        [](Tag& tag1, Tag& tag2){
            return tag1.score > tag2.score;
        }
    );
}

ImageTagMapper::std::vector<Tag> Map(std::vector<Tag>& base_tags) {
    std::vector<Tag> display_tags = FetchDisplayTags();
    ComputeScores(display_tags, base_tags);
    SortDisplayTags(display_tags);
    return display_tags;
}