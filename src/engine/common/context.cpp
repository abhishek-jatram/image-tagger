#include "context.hpp"

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