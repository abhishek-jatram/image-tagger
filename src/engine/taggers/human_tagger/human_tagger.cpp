#include "human_tagger.hpp"

HumanTagger::HumanTagger(std::shared_ptr<ModelExecutor<ROI>> human_detector,
    std::shared_ptr<Filterer<ROI>> filterer):
        Tagger<ROI>(),human_detector_(human_detector), filterer_(filterer){
}

HumanTagger::~HumanTagger() {
}

std::vector<ROI> HumanTagger::Execute(cv::Mat image) {
    std::vector<ROI> output_rois;
    // Run human detector
    bool status;
    status = human_detector_->Run(image);
    if (!status) return {};

    // Extract ROIs
    status = human_detector_->GetOutput(output_rois);
    if (!status) return {};

    // Filter ROIs
    output_rois = filterer_->Filter(output_rois);

    return output_rois;
}