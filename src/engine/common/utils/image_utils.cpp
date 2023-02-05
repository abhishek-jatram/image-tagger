#include "image_utils.hpp"

namespace ImageUtils {
    bool ConvertMatToTensor3D(const cv::Mat img, std::shared_ptr<Tensor3D<float>>& tensor) {
        int n_channels = img.channels();
        int height = img.rows;
        int width = img.cols;

        cv::Mat img_f(height, width, CV_32FC(n_channels));
        if (img.depth() != CV_32F) {
            img.convertTo(img_f, CV_32F);
        } else {
            img_f = img;
        }
        
        tensor = std::make_shared<Tensor3D<float>>(width, height, n_channels);
        if (n_channels == 1) {
            for(int i=0; i<height; i++)
            for(int j=0; j<width; j++)
                (*tensor)(j,i,0) = img_f.at<float>(i,j);
        }
        else if (n_channels == 2) {
            for(int i=0; i<height; i++)
            for(int j=0; j<width; j++)
            for (int k=0; k<n_channels; k++)
                (*tensor)(j,i,k) = img_f.at<cv::Vec2f>(i,j)[k];
        }
        else if (n_channels == 2) {
            for(int i=0; i<height; i++)
            for(int j=0; j<width; j++)
            for (int k=0; k<n_channels; k++)
                (*tensor)(j,i,k) = img_f.at<cv::Vec3f>(i,j)[k];
        }
        else if (n_channels == 4) {
            for(int i=0; i<height; i++)
            for(int j=0; j<width; j++)
            for (int k=0; k<n_channels; k++)
                (*tensor)(j,i,k) = img_f.at<cv::Vec<float,4>>(i,j)[k];
        }
        return true;
    }
} // namespace