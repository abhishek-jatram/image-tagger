#include "with_object_tracker.hpp"

WithObjectTracker::WithObjectTracker(std::shared_ptr<ModelExecutor<ROI>> detector, TrackerType type) 
        : detector_(detector),
        reset_(true),
        tracker_type_(type) {
    multi_tracker_ = cv::MultiTracker::create();
}
WithObjectTracker::~WithObjectTracker() {}

cv::Ptr<cv::Tracker> WithObjectTracker::create_tracker(TrackerType type) {
    switch (type) {
        case TrackerType::BOOSTING: return cv::TrackerBoosting::create();
        case TrackerType::MIL: return cv::TrackerMIL::create();
        case TrackerType::KCF: return cv::TrackerKCF::create();
        case TrackerType::TLD: return cv::TrackerTLD::create();
        case TrackerType::MEDIANFLOW: return cv::TrackerMedianFlow::create();
        case TrackerType::GOTURN: return cv::TrackerGOTURN::create();
        case TrackerType::MOSSE: return cv::TrackerMOSSE::create();
        case TrackerType::CSRT: return cv::TrackerCSRT::create();
    }
    return nullptr;
}

bool WithObjectTracker::Run(cv::Mat image) {
    tracker_input_image_ = image.clone();
    scale_ratio_ = (double) kTrackerInputSize / std::max(image.cols, image.rows);
    cv::resize(image, tracker_input_image_, cv::Size(), scale_ratio_, scale_ratio_);
    if (reset_) {
        return detector_->Run(image);
    }
    return multi_tracker_->update(tracker_input_image_);
}

bool WithObjectTracker::GetOutput(std::vector<ROI> &output) {
    if (reset_) {
        if (!detector_->GetOutput(output))
            return false;
        detected_rois_ = output;
        reset_ = false;
        for (ROI& roi: output) {
            cv::Rect roi_rect(roi.x1 * scale_ratio_, roi.y1 * scale_ratio_, roi.width() * scale_ratio_, roi.height() * scale_ratio_);
            multi_tracker_->add(create_tracker(tracker_type_), tracker_input_image_, roi_rect);
        }
        return true;
    }

    std::vector<cv::Rect2d> tracked_rois = multi_tracker_->getObjects();
    if (tracked_rois.empty())
        reset_ = true;
    for(size_t i=0; i<tracked_rois.size(); i++) {
        ROI roi;
        roi.x1 = tracked_rois[i].x / scale_ratio_;
        roi.y1 = tracked_rois[i].y / scale_ratio_;
        roi.x2 = (tracked_rois[i].x + tracked_rois[i].width - 1) / scale_ratio_;
        roi.y2 = (tracked_rois[i].y + tracked_rois[i].height - 1) / scale_ratio_;
        roi.label = detected_rois_[i].label;
        roi.score = 1.0;
        output.push_back(roi);
    }
    return true;    
}
