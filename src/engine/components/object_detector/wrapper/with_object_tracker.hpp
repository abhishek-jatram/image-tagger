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

    virtual bool Run(cv::Mat image);
    virtual bool GetOutput(std::vector<ROI>& output);
private:
    std::shared_ptr<ModelExecutor<ROI>> detector_;
    bool reset_;
    std::vector<ROI> detected_rois_;

    cv::Mat tracker_input_image_;
    cv::Ptr<cv::Tracker> tracker_;
    cv::Ptr<cv::MultiTracker> multi_tracker_;
    TrackerType tracker_type_;
    cv::Ptr<cv::Tracker> create_tracker(TrackerType type);

    int kTrackerInputSize = 200;
    double scale_ratio_ = 1.0; // target_size / source_size

};
#endif // __COMPONENT_WRAPPER_OBJECT_TRACKER__
