#ifndef __COMPONENT_WRAPPER_OBJECT_TRACKER__
#define __COMPONENT_WRAPPER_OBJECT_TRACKER__

#include "framework/model_executor.hpp"
#include "common/types/roi.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"

class WithObjectTracker: public ModelExecutor<ROI> {
public:
    enum TrackerType{BOOSTING, MIL, KCF, TLD, MEDIANFLOW, GOTURN, MOSSE, CSRT};

    WithObjectTracker(std::shared_ptr<ModelExecutor<ROI>> detector, TrackerType type = TrackerType::CSRT);
    ~WithObjectTracker();

    bool Run(cv::Mat image);
    bool GetOutput(std::vector<ROI>& output);
    bool Finetune(std::vector<ROI>& final_output);

private:
    std::shared_ptr<ModelExecutor<ROI>> detector_;
    bool reset_;
    std::vector<ROI> detected_rois_;

    cv::Mat tracker_input_image_;
    cv::Ptr<cv::Tracker> tracker_;
    cv::Ptr<cv::MultiTracker> multi_tracker_;
    TrackerType tracker_type_;
    std::vector<ROI> prev_tracked_rois_;

    int kTrackerInputSize = 200;
    double kMaxCentroidDeviation = kTrackerInputSize/10;
    double scale_ratio_ = 1.0; // target_size / source_size

    cv::Ptr<cv::Tracker> create_tracker(TrackerType type);
    double get_avg_centroid_distance(std::vector<ROI>& rois1, std::vector<ROI>& rois2);
    double get_max_centroid_distance(std::vector<ROI>& rois1, std::vector<ROI>& rois2);


};
#endif // __COMPONENT_WRAPPER_OBJECT_TRACKER__
