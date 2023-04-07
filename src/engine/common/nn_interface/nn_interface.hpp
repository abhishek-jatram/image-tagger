#ifndef __NN_INTERFACE__
#define __NN_INTERFACE__

#include "common/context.hpp"
#include "tflite_backend.hpp"
#include "opencv_backend.hpp"
#include "common/types/tensor3d.hpp"
#include <memory>
#include <opencv2/opencv.hpp>

class NNInterface {
public:
    NNInterface(const std::shared_ptr<ModelConfig>& model_config);
    bool Initialize(); // TODO: Define an asynchronous version
    bool Run(std::shared_ptr<Tensor3D<float>> input_tensor); // TODO: Define an asynchronous version | Assuming single input
    bool Run(cv::Mat& input_image);
    std::vector<Tensor3D<float>> GetOutput(const std::vector<std::string> output_layer_names);
    ~NNInterface();

private:
    Tensor3D<float> get_tensor_from_rects(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores);
    cv::Mat preprocess_image(cv::Mat image);
    double resize_factor_x = 1; // target size / source size
    double resize_factor_y = 1;

    std::shared_ptr<ModelConfig> model_config_;
    enum State {
        NONE,
        INITIALIZING,
        READY_TO_RUN,
        INITIALIZATION_FAILED,
        RUNNING,
        READY_TO_FETCH
    };
    State state_ = NONE;

    std::unique_ptr<TFLiteBackend> tflite_backend_;
    std::unique_ptr<OpenCVBackend> opencv_backend_;

};

#endif // __NN_INTERFACE__