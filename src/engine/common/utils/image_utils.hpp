#ifndef __UTILS_IMAGE_UTILS__
#define __UTILS_IMAGE_UTILS__
#include <opencv2/opencv.hpp>
#include "common/types/tensor3d.hpp"
#include <memory>

namespace ImageUtils {
    bool ConvertMatToTensor3D(const cv::Mat mat, std::shared_ptr<Tensor3D<float>>& tensor);
    // bool ConvertTensor3DToMat(const Tensor3D<float>& tensor, cv::Mat mat);
}
#endif // __UTILS_IMAGE_UTILS__