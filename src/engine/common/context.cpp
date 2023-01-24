#include "context.hpp"
#include "json.hpp"
#include <cassert>

std::shared_ptr<ModelConfig> Context::GetModelConfig(const std::string& model_name) {
    if (model_config_map_.find(model_name) == model_config_map_.end()) {
        return nullptr;
    }
    return model_config_map_[model_name];
}

void Context::AddModelConfig(const std::string& model_name, std::shared_ptr<ModelConfig> model_config) {
    if (model_config_map_.find(model_name) != model_config_map_.end()) {
        LOG("Over-writing model config for %s", model_name.c_str());
    }
    model_config_map_[model_name] = model_config;
}

std::shared_ptr<MappingInfo> Context::GetMappingInfo(const std::string& model_name) {
    if (model_config_map_.find(model_name) == model_config_map_.end()) {
        return nullptr;
    }
    return model_config_map_[model_name]->mapping_info;
}

ModelConfig::ModelConfig(std::string& config_data, std::string& key, std::shared_ptr<MappingInfo> mapping_info) {
    json json_data = json::parse(config_data);
    assert (!json_data && "Check json format of config_data");

    this->path = json_data[key]["path"];

    std::string platform_str = json_data[key]["platform"];
    auto pos = find(kModelPlatformStr.begin(), kModelPlatformStr.end(), platform_str) - kModelPlatformStr.begin();
    assert(pos < kModelPlatformStr.size() && "Model platfom in config is invalid");
    this->platform = static_cast<ModelPlatform>(pos);;

    std::string type_str = json_data[key]["type"];
    pos = find(kModelTypeStr.begin(), kModelTypeStr.end(), type_str) - kModelTypeStr.begin();
    assert(pos < kModelTypeStr.size() && "Model type in config is invalid");
    this->type = static_cast<ModelType>(pos);

    this->input_shape.width = json_data[key]["input-shape"]["width"];
    this->input_shape.height = json_data[key]["input-shape"]["height"];
    this->input_shape.depth = json_data[key]["input-shape"]["depth"];

    this->output_layer_names = json_data[key]["output-layers"];
    this->mapping_info = mapping_info;
}
