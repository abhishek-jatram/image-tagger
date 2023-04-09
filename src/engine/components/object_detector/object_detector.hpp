#ifndef __COMPONENTS_OBJECT_DETECTOR__
#define __COMPONENTS_OBJECT_DETECTOR__

#include "framework/model_executor.hpp"
#include "common/types/roi.hpp"
#include "common/context.hpp"

class ObjectDetector: public ModelExecutor<ROI> {
public:
    ObjectDetector(Context context, std::string model_name);
    ~ObjectDetector();

    virtual bool Run(cv::Mat image);
    virtual bool GetOutput(std::vector<ROI>& output);
    virtual bool Finetune(std::vector<ROI>& final_output);
protected:
    ObjectDetector();
};

#endif // __COMPONENTS_OBJECT_DETECTOR__
