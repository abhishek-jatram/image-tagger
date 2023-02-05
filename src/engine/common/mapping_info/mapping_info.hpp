#ifndef __MAPPING_INFO__
#define __MAPPING_INFO__
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class MappingInfo {
public:
    MappingInfo(const std::string& mapping_data);
    ~MappingInfo();
    // applicable-type: Tag
    std::vector<std::string> GetDisplayTags();
    std::vector<std::string> GetBaselineTags();
    std::vector<std::string> GetDisplayTagsOf(const std::string& baseline_tag);
    std::vector<std::string> GetBaselineTagsOf(const std::string& display_tag);
    float GetDisplayThreshold(const std::string& display_tag);
    size_t NoOfBaselineTagsOf(const std::string& display_tag);

    // applicable-type: ROI
    std::vector<std::string> GetROILabels();
    size_t GetNoOfROIs();
    float GetROIThreshold(const std::string& roi_label);
    float GetMinAreaToImageRatio(const std::string& roi_label);
    float GetMaxAreaToImageRatio(const std::string& roi_label);
    float GetMinIOUToReject(const std::string& roi_label);

    float GetNMSThreshold();
private:
    json json_data_;
    std::string applicable_type_;
    // applicable-type: Tag
    std::vector<std::string> display_tags_;
    std::vector<std::string> baseline_tags_;
    std::unordered_map<std::string, std::vector<std::string>> baseline2display_;
    std::unordered_map<std::string, std::vector<std::string>> display2baseline_;
    std::unordered_map<std::string, float> display_thresholds_;

    // applicable-type: ROI
    std::vector<std::string> roi_labels_;
    std::unordered_map<std::string, float> roi_thresholds_;
    std::unordered_map<std::string, float> min_area_to_image_ratio_thresholds_;
    std::unordered_map<std::string, float> max_area_to_image_ratio_thresholds_;
    std::unordered_map<std::string, float> min_iou_to_reject_thresholds_;
    float nms_threshold_ = 0.5f;
};
#endif // __MAPPING_INFO__