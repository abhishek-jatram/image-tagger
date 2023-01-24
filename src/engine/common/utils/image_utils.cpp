#include "image_utils.hpp"

namespace ImageUtils {
    bool ConvertMatToTensor3D(const cv::Mat img, std::shared_ptr<Tensor3D<float>>& tensor) {
        int n_channels = img.channels();
        int height = img.rows;
        int width = img.cols;

        if (img.depth() != CV_32F) {
            img.convertTo(img, CV_32F);
        }
        
        float* data = (float*) img.data;
        tensor = std::make_shared<Tensor3D<float>>(width, height, n_channels);
        for(int i=0; i<img.rows; i++) {
            for(int j=0; j<img.cols; j++) {
                for (int k=0; k<img.channels(); k++){
                    (*tensor)(j,i,k) = data[img.step * j + i + k];
                }
            }
        }
        return true;
    }
} // namespace