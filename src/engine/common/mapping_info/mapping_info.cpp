#include "mapping_info.hpp"

MappingInfo::MappingInfo(const std::string& mapping_data) {
    json_data_ = json::parse(mapping_data);
    applicable_type_ = json_data_["applicable-type"];
    if (applicable_type_ == "Tag") {
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
    }
    else if (applicable_type_ == "ROI") {
        if (json_data_.contains("nms-threshold"))
            nms_threshold_ = json_data_["nms-threshold"];
        for (int i=0; i<json_data_["roi-info"].size(); i++) {
            std::string tag = json_data_["roi-info"][i]["label"];
            float min_area_to_image_ratio = json_data_["roi-info"][i]["min-area-to-image-ratio"];
            float max_area_to_image_ratio = json_data_["roi-info"][i]["max-area-to-image-ratio"];
            float threshold = json_data_["roi-info"][i]["threshold"];
            float min_iou_to_reject = json_data_["roi-info"][i]["min-iou-to-reject"];

            roi_labels_.push_back(tag);
            min_area_to_image_ratio_thresholds_[tag] = min_area_to_image_ratio;
            max_area_to_image_ratio_thresholds_[tag] = max_area_to_image_ratio;
            roi_thresholds_[tag] = threshold;
            min_iou_to_reject_thresholds_[tag] = min_iou_to_reject;
        }
    }
    else {
        assert(false && "unknown applicable-type in mapping-info");
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
    return 1.0f; // Let the tag not get filtered-in if it doesn't exist in mapping data
}

size_t MappingInfo::NoOfBaselineTagsOf(const std::string& display_tag) {
    if (display2baseline_.find(display_tag) == display2baseline_.end())
        return 0;
    return display2baseline_[display_tag].size();
}

std::vector<std::string> MappingInfo::GetROILabels() {
    return roi_labels_;
}

size_t MappingInfo::GetNoOfROIs() {
    return roi_labels_.size();
}

float MappingInfo::GetROIThreshold(const std::string& roi_label) {
    if (roi_thresholds_.find(roi_label) != roi_thresholds_.end())
        return roi_thresholds_[roi_label];
    return 1.0f;
}

float MappingInfo::GetMinAreaToImageRatio(const std::string& roi_label) {
    if (min_area_to_image_ratio_thresholds_.find(roi_label) != min_area_to_image_ratio_thresholds_.end())
        return min_area_to_image_ratio_thresholds_[roi_label];
    return 1.0f;
}

float MappingInfo::GetMaxAreaToImageRatio(const std::string& roi_label) {
    if (max_area_to_image_ratio_thresholds_.find(roi_label) != max_area_to_image_ratio_thresholds_.end())
        return max_area_to_image_ratio_thresholds_[roi_label];
    return 0.0f;
}

float MappingInfo::GetMinIOUToReject(const std::string& roi_label) {
    if (min_iou_to_reject_thresholds_.find(roi_label) != min_iou_to_reject_thresholds_.end())
        return min_iou_to_reject_thresholds_[roi_label];
    return 1.0f;
}

float MappingInfo::GetNMSThreshold() {
    return nms_threshold_;
}
