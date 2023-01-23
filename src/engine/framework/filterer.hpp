#ifndef __FRAMEWORK_FILTERER__
#define __FRAMEWORK_FILTERER__

#include <vector>
#include <string>
#include "common/types/tag.hpp"
#include "common/context.hpp"


template <typename T>
class Filterer {
public:
    Filterer(Context context, std::string model_name):
        context_(context), model_name_(model_name) {}
    virtual ~Filterer() {}
    virtual std::vector<T> Filter(std::vector<T>& entities);
private:
    Context context_;
    std::string model_name_;
};
#endif // __FRAMEWORK_FILTERER__