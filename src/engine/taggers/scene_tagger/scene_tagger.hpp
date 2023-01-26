#ifndef __SCENE_TAGGER__
#define __SCENE_TAGGER__

#include "framework/tagger.hpp"
#include "common/types/tag.hpp"
#include "framework/model_executor.hpp"
#include "framework/filterer.hpp"
#include "framework/mapper.hpp"
#include <memory>
#include <opencv2/opencv.hpp>

class SceneTagger: public Tagger<Tag> {
public:
    SceneTagger(std::shared_ptr<ModelExecutor<Tag>> classifier,
        std::shared_ptr<Mapper<Tag>> mapper, std::shared_ptr<Filterer<Tag>> filterer);
    ~SceneTagger();
    std::vector<Tag> Execute(cv::Mat image);
protected:
    std::shared_ptr<ModelExecutor<Tag>> classifier_;
    std::shared_ptr<Mapper<Tag>> mapper_;
    std::shared_ptr<Filterer<Tag>> filterer_;
};

#endif // __SCENE_TAGGER__