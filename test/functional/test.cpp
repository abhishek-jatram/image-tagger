#include <iostream>
#include "../../src/engine/engine.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/objdetect.hpp>
#include "common/types/tag.hpp"
#include "common/types/roi.hpp"
#include <vector>

void display_output_tags(cv::Mat image, std::vector<Tag> output) {
    int height = image.rows;
    float scale = height/20.0f;
    // TODO: Add white background behind the text
    for(int i=0; i<output.size(); i++) {
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

void display_output_rois(cv::Mat image, std::vector<ROI> output, int wait_key=0) {
    // TODO: Add white background behind the text
    for(int i=0; i<output.size(); i++) {
        cv::Rect box(output[i].x1, output[i].y1, output[i].x2 - output[i].x1 + 1, output[i].y2 - output[i].y1 + 1);
        cv::rectangle(image, box, cv::Scalar(0,255,0), 3);
        cv::Scalar color(20,230,50);

        std::stringstream label;
        label << output[i].label << "(" << output[i].score << ")";
        cv::putText(
            image, // source
            label.str(), // text 
            {cv::Point(box.x+20, box.y+20)}, // location
            cv::FONT_HERSHEY_COMPLEX_SMALL, // font
            1.0, // scale
            color, // BGR color
            1, // line thickness
            cv::LINE_AA // anti-alias
        );
    }
    cv::imshow("Result", image);
    cv::waitKey(wait_key);
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
    display_output_tags(image, tags);
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
    // display_output_rois(image, rois);
}

void test_human_tagger() {
    ImageTaggerEngine<ROI> engine(TaggerType::HUMAN_TAGGER);
    // cv::Mat image(640, 480, CV_8UC3);
    // randu(image, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::Mat image = cv::imread("input_data/person.png");

    std::vector<ROI> rois = engine.Execute(image);
    std::cout << "ROIs found: " << rois.size() << "\n";
    display_output_rois(image, rois);

    cv::VideoCapture cap("input_data/person_walking_720.mp4");
    cv::Mat current_frame;
    cap >> current_frame;
    while (!current_frame.empty()) {
        std::vector<ROI> rois = engine.Execute(current_frame);
        display_output_rois(current_frame, rois, 1);
        cap >> current_frame;
    }
}

int main() {
    test_human_tagger();
    // test_scene_tagger();
    // test_object_tagger();
    return 0;
}
