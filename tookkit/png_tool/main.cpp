#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include "face_detect/face_detect.cpp"

std::string haarcascades_path = "/usr/local/share/opencv4/haarcascades";

int main(int argc, char** argv) {
    std::string fname = "/Users/yuanzhaoyi/Docs/photo/Pattaya/IMG_0451.JPG";
    face_detect(fname, haarcascades_path + "/haarcascade_frontalcatface.xml");
//    face_detect(fname, haarcascades_path + "/haarcascade_frontalface_alt.xml");

//    if (target == "1") cname = haarcascades_path + "/haarcascade_frontalface_alt.xml";
//    else if (target == "2") cname =  haarcascades_path + "/haarcascade_frontalcatface.xml";
//    else if (target == "3") cname =  haarcascades_path + "/lbpcascade_animeface.xml";
//    else std::cout << "检测对象输入有误" << std::endl;

//    christmas_hat(fname, cname);
    return 0;
}
