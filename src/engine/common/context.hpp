#ifndef __ENGINE_CONTEXT__
#define __ENGINE_CONTEXT__
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "mapping_info/mapping_info.hpp"

// TODO: Design a logger
#define LOG printf

enum ModelPlatform {
    TENSORFLOW,
    TENSORFLOWLITE,
    PYTORCH
};
// Order of the ModelPlatformStr is dependent on the order of ModelPlatform
static const char* kModelPlatformStr[] = {
    "TENSORFLOW",
    "TENSORFLOWLITE",
    "PYTORCH"
};

enum ModelType {
    CLASSIFIER,
    OBJECTDETECTOR,
    SEGMENTER
};

struct Shape {
    size_t width, height, depth;
    Shape(size_t w, size_t h, size_t d):
        width(w), height(h), depth(d){}
};

struct ModelConfig {
    std::string path;
    ModelPlatform platform;
    ModelType type;
    Shape input_shape;
    std::shared_ptr<MappingInfo> mapping_info;
};

class Context {
private:
    std::unordered_map<std::string, std::shared_ptr<ModelConfig>> model_config_map_;
public:
    // ModelConfig LoadConfig(std::string config_path); // TODO: Load the config from a file provided externally
    std::shared_ptr<ModelConfig> GetModelConfig(const std::string& model_name);
    void AddModelConfig(const std::string& model_name, std::shared_ptr<ModelConfig> model_config);
    std::shared_ptr<MappingInfo> GetMappingInfo(const std::string& model_name);
};
#endif // __ENGINE_CONTEXT__