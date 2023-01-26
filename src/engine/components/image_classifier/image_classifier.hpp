#ifndef __COMPONENTS_IMAGE_CLASSIFIER__
#define __COMPONENTS_IMAGE_CLASSIFIER__

#include "framework/model_executor.hpp"
#include "common/types/tag.hpp"
#include "common/context.hpp"

class ImageClassifier: public ModelExecutor<Tag> {
public:
    ImageClassifier(Context context, std::string model_name);
    ~ImageClassifier();

    bool Run(cv::Mat image);
    bool GetOutput(std::vector<Tag>& output);
private:
    bool convertToBaselineTags(std::vector<float> probs, std::vector<Tag>& output);
};

#endif // __COMPONENTS_IMAGE_CLASSIFIER__