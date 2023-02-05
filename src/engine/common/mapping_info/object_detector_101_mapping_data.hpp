#ifndef __OBJECT_DETECTOR_101_MAPPING_DATA__
#define __OBJECT_DETECTOR_101_MAPPING_DATA__
#include <string>

std::string object_detector_101_mapping_data = R"(
{ 
  "applicable-type": "ROI",
  "nms-threshold": 0.3,
  "roi-info": [
    {
      "label": "object1",
      "min-area-to-image-ratio": 0.3,
      "max-area-to-image-ratio": 0.8,
      "threshold": 0.4,
      "min-iou-to-reject": 0.3
    },
    {
      "label": "object2",
      "min-area-to-image-ratio": 0.4,
      "max-area-to-image-ratio": 1,
      "threshold": 0.5,
      "min-iou-to-reject": 0.3
    },
    {
      "label": "object3",
      "min-area-to-image-ratio": 0.1,
      "max-area-to-image-ratio": 0.6,
      "threshold": 0.6,
      "min-iou-to-reject": 0.3
    }
  ]
}
)";
#endif // __OBJECT_DETECTOR_101_MAPPING_DATA__