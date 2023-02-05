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

ModelConfig::ModelConfig(std::string& config_data, std::string key, std::shared_ptr<MappingInfo> mapping_info) {
    json json_data;
    try {
        json_data = json::parse(config_data);
    } catch (std::exception& ex) {
        LOG("Caught exception while parsing config data of model %s", key.c_str());
    }
    assert (!json_data.is_null() && "Check json format of config_data");

    json json_config = json_data[key];
    assert (!json_config.is_null() && "Check json format of config_data of model");

    if (!json_config.contains("path") ||
        !json_config.contains("platform") ||
        !json_config.contains("type") ||
        !json_config.contains("input-shape") ||
        !json_config.contains("output-layers") ) {
        assert (false && "Provide required configs in config_data of model"); 
    }
    this->path = json_config["path"];
    std::string platform_str = json_config["platform"];
    auto pos = find(kModelPlatformStr.begin(), kModelPlatformStr.end(), platform_str) - kModelPlatformStr.begin();
    assert(pos < kModelPlatformStr.size() && "Model platfom in config is invalid");
    this->platform = static_cast<ModelPlatform>(pos);;

    std::string type_str = json_config["type"];
    pos = find(kModelTypeStr.begin(), kModelTypeStr.end(), type_str) - kModelTypeStr.begin();
    assert(pos < kModelTypeStr.size() && "Model type in config is invalid");
    this->type = static_cast<ModelType>(pos);

    this->input_shape.width = json_config["input-shape"]["width"];
    this->input_shape.height = json_config["input-shape"]["height"];
    this->input_shape.depth = json_config["input-shape"]["depth"];

    this->output_layer_names = json_config["output-layers"];
    this->mapping_info = mapping_info;
}
