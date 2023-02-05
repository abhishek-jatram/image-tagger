#include <iostream>
#include "../../src/engine/engine.hpp"
#include <opencv2/opencv.hpp>
#include "common/types/tag.hpp"
#include "common/types/roi.hpp"
#include <vector>

void display_output(cv::Mat image, std::vector<Tag> output) {
    int height = image.rows;
    float scale = height/20.0f;
    // TODO: Add white background behind the text
    for(int i=0; i<output.size()+1; i++){
        cv::putText(
            image, // source
            output[0].label, // text 
            {static_cast<int>(scale), static_cast<int>(scale*(i+1))}, // location
            cv::FONT_HERSHEY_COMPLEX_SMALL, // font
            1.0, // scale
            cv::Scalar(20,230,50), // BGR color
            1, // line thickness
            cv::LINE_AA // anti-alias
        );
    }
    cv::imshow("Result", image);
    cv::waitKey(0);
}

void test_scene_tagger() {
    ImageTaggerEngine<Tag> engine(TaggerType::SCENE_TAGGER);
    cv::Mat image(640, 480, CV_8UC3);
    randu(image, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

    std::vector<Tag> tags = engine.Execute(image);
    std::cout << "Tags found: " << tags.size() << "\n";
    for (Tag& tag: tags) {
        std::cout << tag.label << ": "<< tag.score << "\n";
    }
    display_output(image, tags);
}

void test_object_tagger() {
    ImageTaggerEngine<ROI> engine(TaggerType::OBJECT_TAGGER);
    cv::Mat image(640, 480, CV_8UC3);
    randu(image, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

    std::vector<ROI> rois = engine.Execute(image);
    std::cout << "ROIs found: " << rois.size() << "\n";
    for (ROI& roi: rois) {
        std::cout << roi.label << ": "<< roi.score << "\n";
    }
    // display_output(image, rois);
}

int main() {

    test_scene_tagger();
    test_object_tagger();
    return 0;
}
