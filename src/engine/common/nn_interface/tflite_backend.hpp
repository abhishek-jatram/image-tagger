#ifndef __NNINTERFACE__TFLITE_BACKEND__
#define __NNINTERFACE__TFLITE_BACKEND__

#include <string>

class TFLiteBackend {
public:
    TFLiteBackend(const std::string& model_path);
    ~TFLiteBackend();
    bool Initialize();
    bool Invoke(float* input);
    bool FetchOutput(const std::string& layer_name, float** output, size_t& w, size_t& h, size_t& d);
private:
    std::string model_path_;
};
#endif //__NNINTERFACE__TFLITE_BACKEND__
