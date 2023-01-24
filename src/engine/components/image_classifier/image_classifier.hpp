#ifndef __COMPONENTS_IMAGE_CLASSIFIER__
#define __COMPONENTS_IMAGE_CLASSIFIER__

#include "framework/model_executor.hpp"
class ImageClassifier: public ModelExecutor<Tag> {
public:
    ImageClassifier(Context context, std::string model_name):
        ModelExecutor<Tag>(context, model_name) {}
    ~ImageClassifier();

    bool Run(cv::Mat image);
    bool GetOutput(cv::Mat image, std::vector<Tag>& output);
private:
    bool convertToBaselineTags(std::vector<float> probs, std::vector<Tag>& output);
}

#endif // __COMPONENTS_IMAGE_CLASSIFIER__