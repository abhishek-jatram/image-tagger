#ifndef __FRAMEWORK_MODEL_EXECUTOR__
#define __FRAMEWORK_MODEL_EXECUTOR__

#include <string>
#include <opencv2/opencv.hpp>
#include "common/context.hpp"
#include "common/types/tensor3d.hpp"
#include "common/nn_interface/nn_interface.hpp"

template <typename T>
class ModelExecutor {
public:
    ModelExecutor(const Context& context, std::string model_name):
        context_(context), model_name_(model_name) {}
    virtual ~ModelExecutor() {};
    virtual bool Run(cv::Mat image);
    virtual bool GetOutput(cv::Mat image, std::vector<T>& output);
protected:
    Context context_;
    std::string model_name_;
    std::shared_ptr<NNInterface> nn_interface_;
};

#endif // __FRAMEWORK_MODEL_EXECUTOR__