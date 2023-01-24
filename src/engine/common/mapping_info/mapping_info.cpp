#include "mapping_info.hpp"

MappingInfo::MappingInfo(const std::string& mapping_data) {
    json_data_ = json::parse(mapping_data);

    // Display Tags
    for (int i=0; i<json_data_["display-info"].size(); i++) {
        std::string tag = json_data_["display-info"][i]["label"];
        float threshold = json_data_["display-info"][i]["threshold"];

        display_tags_.push_back(tag);
        display_thresholds_[tag] = threshold;
    }

    // Baseline Tags
    for (int i=0; i<json_data_["baseline-info"].size(); i++) {
        std::string tag = json_data_["baseline-info"][i]["label"];
        std::vector<std::string> display_tags = json_data_["baseline-info"][i]["display-tags"];
 
        baseline_tags_.push_back(tag);
        baseline2display_[tag] = display_tags;
        for (std::string& display_tag: display_tags) {
            display2baseline_[display_tag].push_back(tag);
        }
    }
};

MappingInfo::~MappingInfo() {
}

std::vector<std::string> MappingInfo::GetDisplayTags() {
    return display_tags_;
}

std::vector<std::string> MappingInfo::GetBaselineTags() {
    return baseline_tags_;
}

std::vector<std::string> MappingInfo::GetDisplayTagsOf(const std::string& baseline_tag){
    if (baseline2display_.find(baseline_tag) != baseline2display_.end())
        return baseline2display_[baseline_tag];
    return {};
}

std::vector<std::string> MappingInfo::GetBaselineTagsOf(const std::string& display_tag){
    if (display2baseline_.find(display_tag) != display2baseline_.end())
        return display2baseline_[display_tag];
    return {};
}

float MappingInfo::GetDisplayThreshold(const std::string& display_tag) {
    if (display_thresholds_.find(display_tag) != display_thresholds_.end())
        return display_thresholds_[display_tag];
    return {};
}