#ifndef __HUMAN_DETECTOR_MAPPING_DATA__
#define __HUMAN_DETECTOR_MAPPING_DATA__
#include <string>

std::string human_detector_mapping_data = R"(
{ 
  "applicable-type": "ROI",
  "nms-threshold": 0.3,
  "roi-info": [
    {
      "label": "human",
      "min-area-to-image-ratio": 0.3,
      "max-area-to-image-ratio": 0.8,
      "threshold": 0.6,
      "min-iou-to-reject": 0.3
    }
  ]
}
)";
#endif // __HUMAN_DETECTOR_MAPPING_DATA__