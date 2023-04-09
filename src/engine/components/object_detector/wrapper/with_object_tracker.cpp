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
        bool status = detector_->GetOutput(output);
        if (!status || output.empty())
            return status;
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
        roi.score = detected_rois_[i].score;
        output.push_back(roi);
    }

    // If the current rois deviate largely from previous rois then reset
    double deviation = get_max_centroid_distance(output, prev_tracked_rois_);
    if (deviation > (kMaxCentroidDeviation / scale_ratio_)) {
        reset_ = true;
        output.clear();
        if (!detector_->Run(tracker_input_image_)){
            return false;
        }
        if(!detector_->GetOutput(output)) {
            return false;
        }
        // scale back the rois w.r.to original image
        for (ROI& roi: output) {
            roi.x1 /= scale_ratio_;
            roi.y1 /= scale_ratio_;
            roi.x2 /= scale_ratio_;
            roi.y2 /= scale_ratio_;
        }
    }
    prev_tracked_rois_ = output;
    return true;    
}

bool WithObjectTracker::Finetune(std::vector<ROI>& final_output) {
    if (final_output.empty()){
        reset_ = true;
    }
    else if (reset_) {
        multi_tracker_ = cv::MultiTracker::create();
        // multi_tracker_->clear();
        reset_ = false;
        for (ROI& roi: final_output) {
            cv::Rect roi_rect(roi.x1 * scale_ratio_, roi.y1 * scale_ratio_, roi.width() * scale_ratio_, roi.height() * scale_ratio_);
            multi_tracker_->add(create_tracker(tracker_type_), tracker_input_image_, roi_rect);
        }
        detected_rois_ = final_output;
        prev_tracked_rois_ = final_output;
    }
    return true;
}

double WithObjectTracker::get_avg_centroid_distance(std::vector<ROI>& rois1, std::vector<ROI>& rois2) {
    if(rois1.size() != rois2.size()) {
        return std::numeric_limits<float>::max();
    }
    int n_rois = rois1.size();
    double avg_dist = 0.0f;
    for (int i=0; i<n_rois; i++) {
        double dist = std::pow((rois1[i].x1 + rois1[i].x2)/2 - (rois2[i].x1 + rois2[i].x2)/2, 2);
        dist += std::pow((rois1[i].y1 + rois1[i].y2)/2 - (rois2[i].y1 + rois2[i].y2)/2, 2);
        avg_dist = std::sqrt(dist);
    }
    avg_dist /= n_rois;
    return avg_dist;
}

double WithObjectTracker::get_max_centroid_distance(std::vector<ROI>& rois1, std::vector<ROI>& rois2) {
    if(rois1.size() != rois2.size()) {
        return std::numeric_limits<float>::max();
    }
    int n_rois = rois1.size();
    double max_dist = 0.0f;
    for (int i=0; i<n_rois; i++) {
        double dist = std::pow((rois1[i].x1 + rois1[i].x2)/2 - (rois2[i].x1 + rois2[i].x2)/2, 2);
        dist += std::pow((rois1[i].y1 + rois1[i].y2)/2 - (rois2[i].y1 + rois2[i].y2)/2, 2);
        dist = std::sqrt(dist);
        max_dist = std::max(dist, max_dist);
    }
    return max_dist;
}
