#ifndef __TAGGER_FACTORY__
#define __TAGGER_FACTORY__

#include "framework/tagger.hpp"
#include "engine.hpp"

template <typename T>
class TaggerFactory {
public:
    static std::shared_ptr<Tagger<T>> GetTagger(TaggerType tagger_type);
private:
    static std::shared_ptr<Tagger<T>> GetSceneTagger();
    static std::shared_ptr<ModelConfig> GetModelConfig(std::string& model_name);
};

#endif // __TAGGER_FACTORY__