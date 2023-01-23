#include "tflite_backend.hpp"
#include <cstring>
// #include "tensorflow/lite/interpreter.h"
// #include "tensorflow/lite/kernels/register.h"
// #include "tensorflow/lite/model.h"
// #include "tensorflow/lite/tools/gen_op_registration.h"

TFLiteBackend::TFLiteBackend(const std::string& model_path): model_path_(model_path) {
}
TFLiteBackend::~TFLiteBackend() {
    //destroy model
}


bool TFLiteBackend::Initialize() {
    // StderrReporter error_reporter;
    // std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(model_path_, &error_reporter);
    // return (model ? true : false);
    return true;
}

bool TFLiteBackend::Invoke(float* input) {
    // tflite::ops::builtin::BuiltinOpResolver resolver;
    // std::unique_ptr<tflite::Interpreter> interpreter;
    // tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    // // Resize input tensors, if desired.
    // interpreter->AllocateTensors();

    // const std::vector<int>& t_inputs = interpreter->inputs();
    // TfLiteTensor* tensor = interpreter->tensor(t_inputs[0]);

    // size_t input_size = tensor->dims->size;

    // size_t batch_size = tensor->dims->data[0];
    // size_t h = tensor->dims->data[1];
    // size_t w = tensor->dims->data[2];
    // size_t channels = tensor->dims->data[3];

    // float* model_input = interpreter->typed_input_tensor<float>(0);
    // std::memcpy(model_input, input, input_size * sizeof(float));

    // interpreter->Invoke();
    return true;
}

bool TFLiteBackend::FetchOutput(const std::string& layer_name, float** output, size_t& w, size_t& h, size_t& d) {
    // *output = interpreter->typed_output_tensor<float>(0);
    *output = new float[4];
    w = 4;
    h = 1;
    d = 1;
    return true;
}