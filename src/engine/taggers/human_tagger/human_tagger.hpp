#ifndef __HUMAN_TAGGER_
#define __HUMAN_TAGGER_

#include "framework/tagger.hpp"
#include "common/types/roi.hpp"
#include "framework/model_executor.hpp"
#include "framework/filterer.hpp"
#include "framework/mapper.hpp"
#include <memory>
#include <opencv2/opencv.hpp>

class HumanTagger: public Tagger<ROI> {
public:
    HumanTagger(std::shared_ptr<ModelExecutor<ROI>> human_detector,
        std::shared_ptr<Filterer<ROI>> filterer);
    ~HumanTagger();
    std::vector<ROI> Execute(cv::Mat image);
protected:
    std::shared_ptr<ModelExecutor<ROI>> human_detector_;
    std::shared_ptr<Filterer<ROI>> filterer_;
};

#endif // __HUMAN_TAGGER_