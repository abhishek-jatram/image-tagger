#include "object_tagger.hpp"

ObjectTagger::ObjectTagger(std::shared_ptr<ModelExecutor<ROI>> object_detector,
    std::shared_ptr<Filterer<ROI>> filterer):
        Tagger<ROI>(),object_detector_(object_detector), filterer_(filterer){
}

ObjectTagger::~ObjectTagger() {
}

std::vector<ROI> ObjectTagger::Execute(cv::Mat image) {
    std::vector<ROI> output_rois;
    // Run object detector
    bool status;
    status = object_detector_->Run(image);
    if (!status) return {};

    // Extract ROIs
    status = object_detector_->GetOutput(output_rois);
    if (!status) return {};

    // Filter ROIs
    output_rois = filterer_->Filter(output_rois);

    return output_rois;
}