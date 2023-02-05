#include "roi_filterer.hpp"
#include <algorithm>

ROIFilterer::ROIFilterer(Context context, std::string& model_name):
    Filterer<ROI>(context, model_name) {
    mapper_ = context.GetMappingInfo(model_name);
}

ROIFilterer::~ROIFilterer() {
}

void ROIFilterer::ApplyThresholding(std::vector<ROI>& output_rois) {
    auto new_rois_end = std::remove_if(output_rois.begin(), output_rois.end(),
        [&](ROI& roi){
            return roi.score < mapper_->GetROIThreshold(roi.label);
        }
    );
    output_rois.erase(new_rois_end, output_rois.end());
}

std::vector<ROI> ROIFilterer::Filter(std::vector<ROI>& ROIs) {
    // Assuming the ROIs to be sorted by mapper
    ApplyThresholding(ROIs);
    return ROIs;
}