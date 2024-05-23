#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include "face_detect/face_detect.cpp"
#include "add_hats/add_hats.cpp"
#include "functions/basicfuncs.cpp"

std::string haarcascades_path = "/usr/local/share/opencv4/haarcascades";

int main(int argc, char** argv) {
    std::string target = "1";
//    std::string fname = "/Users/yuanzhaoyi/Docs/photo/Pattaya/IMG_0609.JPG";
    std::string fname = "/Users/yuanzhaoyi/Develop/temp/human1.jpeg";
//    face_detect(fname, haarcascades_path + "/haarcascade_frontalcatface.xml");

//    face_detect_by_base64("", haarcascades_path + "/haarcascade_frontalface_alt.xml");
//    face_detect(fname, haarcascades_path + "/haarcascade_frontalface_alt.xml");

//    std::string cname;
//    if (target == "1") cname = haarcascades_path + "/haarcascade_frontalface_alt.xml";
//    else if (target == "2") cname =  haarcascades_path + "/haarcascade_frontalcatface.xml";
//    else if (target == "3") cname =  haarcascades_path + "/lbpcascade_animeface.xml";
//    else std::cout << "检测对象输入有误" << std::endl;
//
//    christmas_hat(fname, cname);
//
    // Load the image
    cv::Mat img = cv::imread(fname);
    if (img.empty()) {
        std::cout << "Could not read the image: " << fname << std::endl;
        return -1;
    }
    cv::Mat img_result;

//    img_gray(img, img_result);
//    canny_edge(img, img_result);
//    gaussian_blur(img, img_result);
//    rotation(img, img_result);
//    cartoonV1(img, img_result);
//    cartoonV2(img, img_result);
    pixelateImage(img, img_result, 4);

    // Display the result
    cv::imshow("Result img", img_result);
    cv::waitKey(0);  // Wait for a key press to close the window
    return 0;
}
