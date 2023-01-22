#ifndef __CLASSIFIER_MAPPING_INFO__
#define __CLASSIFIER_MAPPING_INFO__
#include "mapping_info.hpp"

class ClassifierMappingInfo: public MappingInfo {
public:
    ClassifierMappingInfo(std::string mapping_data): MappingInfo(mapping_data){};
}
#endif // __CLASSIFIER_MAPPING_INFO__