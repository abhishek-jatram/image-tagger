#ifndef __FRAMEWORK_TAGGER__
#define __FRAMEWORK_TAGGER__

#include <vector>
#include <opencv2/opencv.hpp>

template <typename T>
class Tagger {
public:
    Tagger(){}
    virtual ~Tagger() {}
    virtual std::vector<T> Execute(cv::Mat image) = 0;
};
#endif // __FRAMEWORK_TAGGER__