#ifndef __FRAMEWORK_TAGGER__
#define __FRAMEWORK_TAGGER__

#include "common/types/tag.hpp"
#include "common/types/roi.hpp"
#include "common/context.hpp"
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

template <typename T>
class Tagger {
public:
    Tagger(Context context, std::string model_name):
        context_(context), model_name_(model_name) {}
    virtual ~Tagger() {}
    virtual std::vector<T> Execute(cv::Mat image);
private:
    Context context_;
    std::string model_name_;
};
#endif // __FRAMEWORK_TAGGER__