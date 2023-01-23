#ifndef __COMMON_TYPES_SEGMENT__
#define __COMMON_TYPES_SEGMENT__

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>
#include <memory>

class Segment {
public:
    std::string label;
    float score;
    std::shared_ptr<Tensor3D<float>> mask;

    cv::Mat ToMat() {
        int w = mask->GetLength(Dimension::X);
        int h = mask->GetLength(Dimension::Y);
        int d = mask->GetLength(Dimension::Z);
        float* data = mask->data();
        cv::Mat<float> mat(h,w,CV_32FC(d), data);
        return mat;
    }
};
#endif // __COMMON_TYPES_SEGMENT__