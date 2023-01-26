#include "engine.hpp"
#include "tagger_factory.hpp"

template <typename T>
ImageTaggerEngine<T>::ImageTaggerEngine(TaggerType tagger_type) {
    tagger_ = TaggerFactory<T>::GetTagger(TaggerType::SCENE_TAGGER);
}

template <typename T>
ImageTaggerEngine<T>::~ImageTaggerEngine(){
}

template <typename T>
std::vector<T> ImageTaggerEngine<T>::Execute(cv::Mat image) {
    return tagger_->Execute(image);
}