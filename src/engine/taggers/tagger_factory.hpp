#ifndef __TAGGER_FACTORY__
#define __TAGGER_FACTORY__

#include "framework/tagger.hpp"
#include "engine.hpp"
#include "common/types/tag.hpp"
#include "common/types/roi.hpp"
#include "common/context.hpp"

class TaggerFactory {
public:
    template <typename T>
    static std::shared_ptr<Tagger<T>> GetTagger(TaggerType tagger_type);
protected:
    static std::shared_ptr<Tagger<Tag>> GetSceneTagger();
    static std::shared_ptr<Tagger<ROI>> GetObjectTagger();
    static std::shared_ptr<Tagger<ROI>> GetHumanTagger();

    static std::shared_ptr<ModelConfig> GetModelConfig(std::string& model_name);
};

#endif // __TAGGER_FACTORY__