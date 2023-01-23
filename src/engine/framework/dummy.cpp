#include "mapper.hpp"
#include "filterer.hpp"
#include "model_executor.hpp"
#include "common/types/tag.hpp"
#include "common/context.hpp"

class DummyMapper: public Mapper<Tag> {
public:
    DummyMapper(Context context): Mapper<Tag>(context, "model.tflite"){}
};
class DummyFilterer: public Filterer<Tag> {
public:
    DummyFilterer(Context context): Filterer<Tag>(context, "model.tflite"){}
};
void test() {
    Context context;
    DummyMapper mapper(context);
    std::vector<Tag> tags = {};
    mapper.Map(tags);

    DummyFilterer filterer(context);
    filterer.Filter(tags);
}