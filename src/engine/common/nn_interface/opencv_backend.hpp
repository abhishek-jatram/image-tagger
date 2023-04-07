#ifndef __NNINTERFACE__OPENCV_BACKEND__
#define __NNINTERFACE__OPENCV_BACKEND__

#include <string>
#include <opencv2/opencv.hpp>
#include <unordered_map>

class OpenCVBackend {
public:
    enum ModelType {
        HOG_BASED_PEOPLE_DETECTOR,
        NONE
    };
    enum OutputType {
        RECTS, // ROIs, label & scores
        LABELS, // label & scores
        SCORE, // score
        IMAGE // cv::Mat, score
    };
    OpenCVBackend(ModelType model_type, const std::string& model_path);
    ~OpenCVBackend();
    bool Initialize();
    bool Invoke(cv::Mat image);
    OutputType GetOutputType();
    bool GetOutput(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores);
    bool GetOutput(std::vector<int>& label_ids, std::vector<double>& scores);
private:
    std::unordered_map<ModelType, OutputType> kModelOutputType {
        {HOG_BASED_PEOPLE_DETECTOR, RECTS}
    };
    ModelType model_type_;
    std::string model_path_;

    class Executor {
    public:
        virtual ~Executor() {}
        virtual bool Initialize() = 0;
        virtual bool Run(cv::Mat image) = 0;
        virtual bool Output(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores) {
            return false;
        }
        virtual bool Output(std::vector<int>& label_ids, std::vector<double>& scores) {
            return false;
        }
        virtual bool Output(double& score) {
            return false;
        }
        virtual bool Output(cv::Mat output_image) {
            return false;
        }
    };
    std::shared_ptr<Executor> executor_;

    class HogPeopleDetector: public Executor {
    public:
        HogPeopleDetector(){}
        ~HogPeopleDetector(){}
        bool Initialize();
        bool Run(cv::Mat image);
        bool Output(std::vector<cv::Rect>& rois, std::vector<int>& label_ids, std::vector<double>& scores);
    private:
        cv::HOGDescriptor hog_;
        std::vector<cv::Rect> output_rois_;
        std::vector<double> output_scores_;
    };
};
#endif //__NNINTERFACE__OPENCV_BACKEND__
