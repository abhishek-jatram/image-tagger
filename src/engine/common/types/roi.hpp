#ifndef __COMMON_TYPES_ROI__
#define __COMMON_TYPES_ROI__

#include <string>

class ROI {
public:
    std::string label;
    float score;
    int image_width, image_height;
    int x1, y1, x2, y2; // box relative to image_w, image_h
};
#endif // __COMMON_TYPES_ROI__