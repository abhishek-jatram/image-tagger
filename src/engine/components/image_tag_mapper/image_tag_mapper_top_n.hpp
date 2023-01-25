#ifndef __COMPONENTS_IMAGE_TAG_MAPPER_TOP_N__
#define __COMPONENTS_IMAGE_TAG_MAPPER_TOP_N__
#include "framework/mapper.hpp"
#include "common/types/tag.hpp"

// ImageTagMapperTopN can be used to eliminate the bias of baseline counts
// If a display tags has large number of baselines then the sum of score could contribute to large display score
// So as to avoid that bias, consider only top-N baselines per display tag.
class ImageTagMapperTopN: public ImageTagMapper {
public:
    ImageTagMapperTopN(Context context, std::string model_name, int n_tops=3):
        ImageTagMapper(context, model_name), n_tops_(n_tops){}
protected:
    void ComputeScores(std::vector<Tag>& display_tags, std::vector<Tag>& base_tags);
    int n_tops_;
}
#endif // __COMPONENTS_IMAGE_TAG_MAPPER_TOP_N__