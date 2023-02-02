#ifndef __IMAGE_TAGGER_ENGINE__
#define __IMAGE_TAGGER_ENGINE__

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include "framework/tagger.hpp"

enum TaggerType {
    SCENE_TAGGER,
    OBJECT_TAGGER
};

template <typename T>
class ImageTaggerEngine {
public:
    ImageTaggerEngine(TaggerType tagger_type);
    ~ImageTaggerEngine();
    std::vector<T> Execute(cv::Mat image);
private:
    std::shared_ptr<Tagger<T>> tagger_;
};

#endif // __IMAGE_TAGGER_ENGINE__