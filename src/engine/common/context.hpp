#ifndef __ENGINE_CONTEXT__
#define __ENGINE_CONTEXT__
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "mapping_info/mapping_info.hpp"

// TODO: Design a logger
#define LOG(format, ...) printf(format "\n", ##__VA_ARGS__)

enum ModelPlatform {
    TENSORFLOW,
    TENSORFLOWLITE,
    PYTORCH
};
// Order of the ModelPlatformStr is dependent on the order of ModelPlatform
static const std::vector<std::string>
kModelPlatformStr = {
    "TENSORFLOW",
    "TENSORFLOWLITE",
    "PYTORCH"
};

enum ModelType {
    CLASSIFIER,
    OBJECTDETECTOR,
    SEGMENTER
};
// Order of the kModelTypeStr is dependent on the order of ModelType
static const std::vector<std::string>
kModelTypeStr = {
    "CLASSIFIER",
    "OBJECTDETECTOR",
    "SEGMENTER"
};

struct Shape {
    size_t width, height, depth;
    Shape(size_t w, size_t h, size_t d):
        width(w), height(h), depth(d){}
    Shape(){}
};

class ModelConfig {
public:
    std::string path;
    ModelPlatform platform;
    ModelType type;
    Shape input_shape;
    std::shared_ptr<MappingInfo> mapping_info;
    std::vector<std::string> output_layer_names;

    // FromFile(std::string& config_file);
    ModelConfig(std::string config_data, std::string key, std::shared_ptr<MappingInfo> mapping_info);
};

class Context {
private:
    std::unordered_map<std::string, std::shared_ptr<ModelConfig>> model_config_map_;
public:
    Context(){};
    // ModelConfig LoadConfig(std::string config_path); // TODO: Load the config from a file provided externally
    std::shared_ptr<ModelConfig> GetModelConfig(const std::string& model_name);
    void AddModelConfig(const std::string& model_name, std::shared_ptr<ModelConfig> model_config);
    std::shared_ptr<MappingInfo> GetMappingInfo(const std::string& model_name);
};
#endif // __ENGINE_CONTEXT__