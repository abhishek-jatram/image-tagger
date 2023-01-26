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
    Tagger(){}
    virtual ~Tagger() {}
    virtual std::vector<T> Execute(cv::Mat image);
};
#endif // __FRAMEWORK_TAGGER__