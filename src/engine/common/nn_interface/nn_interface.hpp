#ifndef __NN_INTERFACE__
#define __NN_INTERFACE__

#include "context.hpp"
#include "tflite_backend.hpp"
#include "types/tensor3d.hpp"
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
};

#endif // __NN_INTERFACE__