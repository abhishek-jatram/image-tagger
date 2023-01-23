#ifndef __FRAMEWORK_MAPPER__
#define __FRAMEWORK_MAPPER__

#include <vector>
#include <string>
#include "common/context.hpp"

template <typename T>
class Mapper {
public:
    Mapper(Context context, std::string model_name):
        context_(context), model_name_(model_name) {}
    virtual ~Mapper() {}
    virtual std::vector<T> Map(std::vector<T>& base_entities);
private:
    Context context_;
    std::string model_name_;
};
#endif // __FRAMEWORK_MAPPER__