#include "image_tag_mapper_top_n.hpp"
#include <algorithm>

void ImageTagMapperTopN::ComputeScores(std::vector<Tag>& display_tags, std::vector<Tag>& base_tags) {
    // Sort baseline tags based on score
    std::sort(base_tags.begin(),base_tags.end(),
        [](Tag& tag1, Tag& tag2){
            return tag1.score > tag1.score;
        }
    );

    // display tag label to display tag index mapping
    std::unordered_map<std::string, int> label_to_tag_idx;
    for (int i=0; i<display_tags.size(); i++) {
        label_to_tag_idx[display_tags[i].label] = i;
    }

    // display tag score = SUM (Top-N of its baseline scores) / Top-N
    std::vector<int> n_baseline_count;// no of baseline considered for each display tag.
    n_baseline_count.reserve(display_tags.size());
    for (int i=0 ; i<base_tags.size(); i++) {
        for (std::string display_tag: mapper_->GetDisplayTagsOf(base_tags[i].label)) {
            int display_id = label_to_tag_idx[display_tag];
            if (n_baseline_count[display_id] < n_tops_) {
                n_baseline_count[display_id]++;
                display_tags[display_id].score += base_tags[i].score;
            }
        }
    }

    for (int i=0; i<display_tags.size(); i++) {
        if (n_baseline_count[i]) {
            display_tags[i].score /= n_baseline_count[i];
        }
    }
}