#ifndef __MAPPING_INFO__
#define __MAPPING_INFO__
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class MappingInfo {
public:
    MappingInfo(const std::string& mapping_data);
    ~MappingInfo();
    std::vector<std::string> GetDisplayTags();
    std::vector<std::string> GetBaselineTags();
    std::vector<std::string> GetDisplayTagsOf(const std::string& baseline_tag);
    std::vector<std::string> GetBaselineTagsOf(const std::string& display_tag);
    float GetDisplayThreshold(const std::string& display_tag);

private:
    json json_data_;
    std::vector<std::string> display_tags_;
    std::vector<std::string> baseline_tags_;
    std::unordered_map<std::string, std::vector<std::string>> baseline2display_;
    std::unordered_map<std::string, std::vector<std::string>> display2baseline_;
    std::unordered_map<std::string, float> display_thresholds_;
};
#endif // __MAPPING_INFO__