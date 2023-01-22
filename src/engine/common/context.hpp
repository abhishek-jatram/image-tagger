#ifndef __ENGINE_CONTEXT__
#define __ENGINE_CONTEXT__
#include <string>
#include <unordered_map>
#include <memory>
#include "mapping_info/mapping_info.hpp"

enum ModelPlatform {
    TENSORFLOW,
    TENSORFLOWLITE,
    PYTORCH
};

enum ModelType {
    CLASSIFIER,
    OBJECTDETECTOR,
    SEGMENTER
}

using Size = std::tupple<size_t, size_t, size_t>

struct ModelConfig {
    std::string path;
    ModelPlatform platform;
    ModelType type;
    Size input_size;
    std::shared_ptr<MappingInfo> mapping_info;
};

class Context {
private:
    std::unordered_map<std::string, ModelConfig> model_config_map_;
public:
    // ModelConfig LoadConfig(std::string config_path); // TODO: Load the config from a file provided externally
    ModelConfig GetModelConfig(std::string model_name);
    void AddModelConfig(std::string model_name, ModelConfig model_config);
    std::shared_ptr<MappingInfo> GetMappingInfo(std::string model_name);
};
#endif // __ENGINE_CONTEXT__