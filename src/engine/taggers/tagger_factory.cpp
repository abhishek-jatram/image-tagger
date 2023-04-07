#include "tagger_factory.hpp"
#include "scene_tagger/scene_tagger.hpp"
#include "object_tagger/object_tagger.hpp"
#include "human_tagger/human_tagger.hpp"

#include "components/image_classifier/image_classifier.hpp"
#include "components/image_tag_mapper/image_tag_mapper.hpp"
#include "components/image_tag_filterer/image_tag_filterer.hpp"

#include "components/object_detector/object_detector.hpp"
#include "components/roi_filterer/roi_filterer.hpp"

#include "common/mapping_info/classifier101_mapping_data.hpp"
#include "common/mapping_info/object_detector_101_mapping_data.hpp"
#include "common/mapping_info/human_detector_mapping_data.hpp"

template<> std::shared_ptr<Tagger<Tag>> TaggerFactory::GetTagger<Tag>(TaggerType tagger_type) {
    switch (tagger_type) {
        case SCENE_TAGGER:
            return GetSceneTagger();
        default:
            LOG("The tagger type is not supported for Tags");
    }
    return nullptr;
}

template<> std::shared_ptr<Tagger<ROI>> TaggerFactory::GetTagger<ROI>(TaggerType tagger_type) {
    switch (tagger_type) {
        case OBJECT_TAGGER:
            return GetObjectTagger();
        case HUMAN_TAGGER:
            return GetHumanTagger();
        default:
            LOG("The tagger type is not supported for ROIs");
    }
    return nullptr;
}

std::shared_ptr<Tagger<Tag>> TaggerFactory::GetSceneTagger() {
    std::string model_name = "classifier101";
    std::shared_ptr<ModelConfig> model_config = GetModelConfig(model_name);
    Context context;
    context.AddModelConfig(model_name, model_config);

    std::shared_ptr<ImageClassifier> classifier = 
        std::make_shared<ImageClassifier>(context, model_name);
    std::shared_ptr<ImageTagMapper> mapper = 
        std::make_shared<ImageTagMapper>(context, model_name);
    std::shared_ptr<ImageTagFilterer> filterer = 
        std::make_shared<ImageTagFilterer>(context, model_name);

    return std::make_shared<SceneTagger>(classifier, mapper, filterer);
}

std::shared_ptr<Tagger<ROI>> TaggerFactory::GetObjectTagger() {
    std::string model_name = "objectdetector101";
    std::shared_ptr<ModelConfig> model_config = GetModelConfig(model_name);
    Context context;
    context.AddModelConfig(model_name, model_config);

    std::shared_ptr<ObjectDetector> detector = 
        std::make_shared<ObjectDetector>(context, model_name);
    std::shared_ptr<ROIFilterer> filterer = 
        std::make_shared<ROIFilterer>(context, model_name);

    return std::make_shared<ObjectTagger>(detector, filterer);;
}

std::shared_ptr<Tagger<ROI>> TaggerFactory::GetHumanTagger() {
    std::string model_name = "humandetector-hog";
    std::shared_ptr<ModelConfig> model_config = GetModelConfig(model_name);
    Context context;
    context.AddModelConfig(model_name, model_config);

    std::shared_ptr<ObjectDetector> detector = 
        std::make_shared<ObjectDetector>(context, model_name);
    std::shared_ptr<ROIFilterer> filterer = 
        std::make_shared<ROIFilterer>(context, model_name);

    // TODO: Create tracker module and add it to HumanTagger
    return std::make_shared<HumanTagger>(detector, filterer);
}

std::shared_ptr<ModelConfig> TaggerFactory::GetModelConfig(std::string& model_name) {
    std::string models_config_data = R"(
        {
            "classifier101_config": {
                "path" : "classifier101.tf",
                "platform" : "TENSORFLOWLITE",
                "type" : "CLASSIFIER",
                "input-shape" : {
                    "width" : 300,
                    "height" : 300,
                    "depth" : 3
                },
                "output-layers" : [
                    "probs"
                ]
            },
            "objectdetector101_config": {
                "path" : "objectdetector101.tf",
                "platform" : "TENSORFLOWLITE",
                "type" : "OBJECTDETECTOR",
                "input-shape" : {
                    "width" : 300,
                    "height" : 300,
                    "depth" : 3
                },
                "output-layers" : [
                    "bounding-boxes"
                ]
            },
            "humandetector-hog": {
                "path" : "",
                "platform" : "OPENCV",
                "type" : "HOG_BASED_PEOPLE_DETECTOR",
                "input-shape" : {
                    "width" : 300,
                    "height" : -1,
                    "depth" : 3
                },
                "output-layers" : [
                ]
            }
        }
    )";
    if (model_name == "classifier101") {
        std::shared_ptr<MappingInfo> mapping_info =
            std::make_shared<MappingInfo>(classifier101_mapping_data);
        std::shared_ptr<ModelConfig> model_config =
            std::make_shared<ModelConfig>(models_config_data, "classifier101_config", mapping_info);
        return model_config;
    }
    if (model_name == "objectdetector101") {
         std::shared_ptr<MappingInfo> mapping_info =
            std::make_shared<MappingInfo>(object_detector_101_mapping_data);
        std::shared_ptr<ModelConfig> model_config =
            std::make_shared<ModelConfig>(models_config_data, "objectdetector101_config", mapping_info);
        return model_config;
    }
    if (model_name == "humandetector-hog") {
         std::shared_ptr<MappingInfo> mapping_info =
            std::make_shared<MappingInfo>(human_detector_mapping_data);
        std::shared_ptr<ModelConfig> model_config =
            std::make_shared<ModelConfig>(models_config_data, "humandetector-hog", mapping_info);
        return model_config;
    }
    return nullptr;
}