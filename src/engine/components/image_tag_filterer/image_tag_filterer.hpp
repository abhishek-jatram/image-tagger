#ifndef __COMPONENT_IMAGE_TAG_FILTERER__
#define __COMPONENT_IMAGE_TAG_FILTERER__

#include "common/context.hpp"
#include "common/types/tag.hpp"
#include "framework/filterer.hpp"

class ImageTagFilterer: public Filterer<Tag> {
public:
    ImageTagFilterer(Context context, std::string& model_name);
    ~ImageTagFilterer();
    std::vector<Tag> Filter(std::vector<Tag>& tags);
protected:
    void ApplyThresholding(std::vector<Tag>& tags);
    std::shared_ptr<MappingInfo> mapper_;
};
#endif // __COMPONENT_IMAGE_TAG_FILTERER__