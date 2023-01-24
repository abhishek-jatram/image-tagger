#ifndef __UTILS_IMAGE_UTILS__
#define __UTILS_IMAGE_UTILS__
#include <opencv2/opencv.hpp>
#include "types/tensor3d.hpp"
#include <memory>

namespace ImageUtils {
    bool ConvertMatToTensor3D(const cv::Mat mat, std::shared_ptr<Tensor3D<float>>& tensor);
}
#endif // __UTILS_IMAGE_UTILS__