#ifndef __OBJECT_TAGGER__
#define __OBJECT_TAGGER__

#include "framework/tagger.hpp"
#include "common/types/roi.hpp"
#include "framework/model_executor.hpp"
#include "framework/filterer.hpp"
#include "framework/mapper.hpp"
#include <memory>
#include <opencv2/opencv.hpp>

class ObjectTagger: public Tagger<ROI> {
public:
    ObjectTagger(std::shared_ptr<ModelExecutor<ROI>> object_detector,
        std::shared_ptr<Filterer<ROI>> filterer);
    ~ObjectTagger();
    std::vector<ROI> Execute(cv::Mat image);
protected:
    std::shared_ptr<ModelExecutor<ROI>> object_detector_;
    std::shared_ptr<Filterer<ROI>> filterer_;
};

#endif // __OBJECT_TAGGER__