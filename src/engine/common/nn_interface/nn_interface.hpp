#ifndef __NN_INTERFACE__
#define __NN_INTERFACE__

#include "context.hpp"
#include <memory>
#include "tflite_backend.hpp"
#include "types/tensor3d.hpp"

class NNInterface {
public:
    NNInterface(const ModelConfig& model_config);
    bool Initialize(); // TODO: Define an asynchronous version
    bool Run(std::shared_ptr<Tensor3D<float>> input_tensor); // TODO: Define an asynchronous version
    // bool Run(cv::Mat& input_tensor); // TODO: integrate opencv
    bool GetOutput(std::shared_ptr<Tensor3D<float>>& output_tensor);
    ~NNInterface();

private:
    ModelConfig model_config_;
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