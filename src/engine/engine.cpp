#include "engine.hpp"
#include "tagger_factory.hpp"
#include "common/types/tag.hpp"
#include "common/types/roi.hpp"

template <typename T>
ImageTaggerEngine<T>::ImageTaggerEngine(TaggerType tagger_type) {
    tagger_ = TaggerFactory::GetTagger<T>(tagger_type);
}

template <typename T>
ImageTaggerEngine<T>::~ImageTaggerEngine(){
}

template <typename T>
std::vector<T> ImageTaggerEngine<T>::Execute(cv::Mat image) {
    return tagger_->Execute(image);
}

// Definitions per template
template class ImageTaggerEngine<Tag>;
template class ImageTaggerEngine<ROI>;