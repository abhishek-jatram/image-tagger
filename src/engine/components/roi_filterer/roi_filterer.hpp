#ifndef __COMPONENT_ROI_FILTERER__
#define __COMPONENT_ROI_FILTERER__

#include "common/context.hpp"
#include "common/types/roi.hpp"
#include "framework/filterer.hpp"

class ROIFilterer: public Filterer<ROI> {
public:
    ROIFilterer(Context context, std::string& model_name);
    ~ROIFilterer();
    std::vector<ROI> Filter(std::vector<ROI>& ROIs);
protected:
    void ApplyThresholding(std::vector<ROI>& ROIs);
    std::shared_ptr<MappingInfo> mapper_;
};
#endif // __COMPONENT_ROI_FILTERER__