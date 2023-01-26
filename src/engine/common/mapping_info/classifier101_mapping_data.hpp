#ifndef __CLASSIFIER101_MAPPING_DATA__
#define __CLASSIFIER101_MAPPING_DATA__
#include <string>

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
#endif // __CLASSIFIER101_MAPPING_DATA__