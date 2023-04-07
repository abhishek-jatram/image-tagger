#include "opencv_backend.hpp"

#define LOG(format, ...) printf(format "\n", ##__VA_ARGS__)

OpenCVBackend::OpenCVBackend(ModelType model_type, const std::string& model_path) : model_type_(model_type), model_path_(model_path) {
    if (model_type_ == ModelType::HOG_BASED_PEOPLE_DETECTOR) {
        executor_ = std::make_shared<HogPeopleDetector>();
    }
}

OpenCVBackend::~OpenCVBackend() {
}

bool OpenCVBackend::Initialize() {
    return executor_->Initialize();
}
bool OpenCVBackend::Invoke(cv::Mat image) {
    return executor_->Run(image);
}
OpenCVBackend::OutputType OpenCVBackend::GetOutputType() {
    return kModelOutputType[model_type_];
}

bool OpenCVBackend::GetOutput(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores) {
    if (kModelOutputType[model_type_] != RECTS) {
        LOG("The expected output format is incorrect");
        return false;
    }
    return executor_->Output(rois, label_ids, scores);
}

// HogPeopleDetector
bool OpenCVBackend::HogPeopleDetector::Initialize() {
    hog_.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    return true;
}
bool OpenCVBackend::HogPeopleDetector::Run(cv::Mat image) {
    hog_.detectMultiScale(image, output_rois_, output_scores_);
    return true;
}
bool OpenCVBackend::HogPeopleDetector::Output(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores) {
    rois = output_rois_;
    scores = output_scores_;
    return true;
}
