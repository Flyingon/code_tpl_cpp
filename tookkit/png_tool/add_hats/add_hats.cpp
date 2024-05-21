#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <string>
#include <iostream>

std::vector<cv::Rect> face_detect(cv::Mat& img, const std::string& cname) {
    cv::Mat img_gray, img_hist;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_hist);
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(cname)) {
        std::cout << "Error loading cascade file. Check file path!" << std::endl;
        return {};
    }
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img_hist, faces);
    return faces;
}

void christmas_hat(const std::string& fname, const std::string& cname) {
    cv::Mat img = cv::imread(fname);
    std::vector<cv::Rect> faces = face_detect(img, cname);
    std::vector<cv::Mat> hats;
    for (int i = 0; i < 3; ++i) {
        hats.push_back(cv::imread("/Users/yuanzhaoyi/Develop/image-tools/opencv-christmas-hat/img/hats/hat_" + std::to_string(i + 1) + ".png", cv::IMREAD_UNCHANGED));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (const auto& face : faces) {
        std::uniform_int_distribution<> dis(0, hats.size() - 1);
        cv::Mat hat = hats[dis(gen)];
        double scale = double(face.height) / hat.rows * 2;
        cv::resize(hat, hat, cv::Size(), scale, scale);

        int x_offset = face.x + face.width / 2 - hat.cols / 2;
        int y_offset = face.y - hat.rows / 2;
        int x1 = std::max(x_offset, 0);
        int x2 = std::min(x_offset + hat.cols, img.cols);
        int y1 = std::max(y_offset, 0);
        int y2 = std::min(y_offset + hat.rows, img.rows);

        cv::Mat hat_region = hat(cv::Range(std::max(0, -y_offset), hat.rows + std::min(0, img.rows - (y_offset + hat.rows))),
                                 cv::Range(std::max(0, -x_offset), hat.cols + std::min(0, img.cols - (x_offset + hat.cols))));

        for (int c = 0; c < img.channels(); ++c) {
            cv::Mat roi = img(cv::Range(y1, y2), cv::Range(x1, x2));
            if (c < 3) {
                for (int y = 0; y < hat_region.rows; ++y) {
                    for (int x = 0; x < hat_region.cols; ++x) {
                        int hat_pixel_val = hat_region.at<cv::Vec4b>(y, x)[c];
                        int img_pixel_val = roi.at<cv::Vec3b>(y, x)[c];
                        float alpha = hat_region.at<cv::Vec4b>(y, x)[3] / 255.0;
                        roi.at<cv::Vec3b>(y, x)[c] = uchar(alpha * hat_pixel_val + (1 - alpha) * img_pixel_val);
                    }
                }
            }
        }
    }
    // Display the result
    cv::imshow("Face add hats", img);
    cv::waitKey(0);  // Wait for a key press to close the window
//    cv::imwrite("img/result/" + fname.substr(fname.find_last_of("/") + 1), img);
}

//std::string haarcascades_path = "/usr/local/share/opencv4/haarcascades";
//
//int main(int argc, char** argv) {
//    std::string fname = "/Users/yuanzhaoyi/Docs/photo/Pattaya/IMG_0473.JPG";
//    std::cout << "请选择要添加圣诞帽的对象: 1 人 2 猫 3 动漫 (默认1) ";
//    std::string target;
//    std::cin >> target;
//    std::string cname;
//    if (target.empty()) target = "1";
//    if (target == "1") cname = haarcascades_path + "/haarcascade_frontalface_alt.xml";
//    else if (target == "2") cname =  haarcascades_path + "/haarcascade_frontalcatface.xml";
//    else if (target == "3") cname =  haarcascades_path + "/lbpcascade_animeface.xml";
//    else std::cout << "检测对象输入有误" << std::endl;
//
//    christmas_hat(fname, cname);
//    return 0;
//}
