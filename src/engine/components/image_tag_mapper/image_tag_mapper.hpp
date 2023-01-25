#ifndef __COMPONENTS_IMAGE_TAG_MAPPER__
#define __COMPONENTS_IMAGE_TAG_MAPPER__
#include "framework/mapper.hpp"
#include "common/types/tag.hpp"

class ImageTagMapper: public Mapper<Tag> {
public:
    ImageTagMapper(Context context, std::string model_name);
    ~ImageTagMapper();
    std::vector<Tag> Map(std::vector<Tag>& base_entities);
protected:
    std::vector<Tag> FetchDisplayTags();
    void ComputeScores(std::vector<Tag>& display_tags, std::vector<Tag>& base_tags);
    void SortDisplayTags(std::vector<Tag>& display_tags);
private:
    std::shared_ptr<MappingInfo> mapper;
}
#endif // __COMPONENTS_IMAGE_TAG_MAPPER__