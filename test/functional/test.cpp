#include <iostream>
#include "../../src/engine/engine.hpp"
#include <opencv2/opencv.hpp>
#include "common/types/tag.hpp"
#include <vector>
int main() {
    ImageTaggerEngine<Tag> engine(TaggerType::SCENE_TAGGER);
    cv::Mat image(640, 480, CV_32F, cv::Scalar(0, 0, 0));
    std::vector<Tag> tags = engine.Execute(image);
    std::cout << "Tags found: " << tags.size() << "\n";
    for (Tag& tag: tags) {
        std::cout << tag.label << ": "<< tag.score << "\n";
    }
    return 0;
}
