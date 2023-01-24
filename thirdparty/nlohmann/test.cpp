#include "json.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using json = nlohmann::json;

std::string classifier101_mapping_data = R"(
{  "display-info": [
    {
      "label": "DisplayTag1",
      "threshold": 0.5,
      "cluster-info": "DisplayTag2",
      "tag-type": "Background"
    },
    {
      "label": "DisplayTag2",
      "threshold": 0.6,
      "cluster-info": "DisplayTag2",
      "tag-type": "Background"
    },
    {
      "label": "DisplayTag3",
      "threshold": 0.4,
      "cluster-info": "DisplayTag3",
      "tag-type": "Foreground"
    }
  ],
  "baseline-info": [
    {
      "label": "baseline1",
      "suppression-threshold": 0.2,
      "display-tags": [
        "DisplayTag1",
        "DisplayTag2"
      ]
    },
    {
      "label": "baseline2",
      "suppression-threshold": 0.12,
      "display-tags": [
        "DisplayTag1"
      ]
    },
    {
      "label": "baseline3",
      "suppression-threshold": 0.4,
      "display-tags": [
        "DisplayTag3"
      ]
    },
    {
      "label": "baseline4",
      "suppression-threshold": 0.24,
      "display-tags": [
        "DisplayTag2"
      ]
    }
  ]
}
)";

int main() {
    json json_data = json::parse(classifier101_mapping_data);

    std::cout << json_data["display-info"].size() << "\n";
    for (int i=0; i<json_data["display-info"].size(); i++) {
        std::cout << json_data["display-info"][i]["label"] << "\n";
    }

    std::string baseline_tag = json_data["baseline-info"][0]["label"];
    std::vector<std::string> display_tags = json_data["baseline-info"][0]["display-tags"];
    for(auto& tag: display_tags) {
        std::cout<<tag<<" ";
    }
    std::cout<<"\n";

    std::unordered_map<std::string, std::vector<std::string>> display2baseline_;
    for(auto& tag: display_tags) {
        display2baseline_[tag].push_back(baseline_tag); 
    }

    for(auto& tag: display2baseline_["DisplayTag1"])
        std::cout << tag <<" ";
    std::cout << "\n";
    return 0;
}