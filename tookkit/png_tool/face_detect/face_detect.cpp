#include <opencv2/opencv.hpp>
#include <iostream>

// base64 解码函数
std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

void face_detect(const std::string& file_name, const std::string& cascade_name) {
    // Load the image
    cv::Mat img = cv::imread(file_name);
    if (img.empty()) {
        std::cout << "Could not read the image: " << file_name << std::endl;
        return;
    }

    // Convert to grayscale
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    // Histogram equalization
    cv::equalizeHist(img_gray, img_gray);

    // Load the cascade classifier
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(cascade_name)) {
        std::cout << "Error loading cascade file: " << cascade_name << std::endl;
        return;
    }

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img_gray, faces);

    // Draw rectangles around each face
    for (const auto& face : faces) {
        cv::rectangle(img, face, cv::Scalar(255, 0, 255), 5);
    }

    // Display the result
    cv::imshow("Face detection", img);
    cv::waitKey(0);  // Wait for a key press to close the window
}

void face_detect_by_base64(const std::string& image_base64, const std::string& cascade_name) {
    // 解码 base64 字符串
    std::string decoded_string = base64_decode(image_base64);
    // 将解码后的字符串转换为字节数组
    std::vector<uchar> data(decoded_string.begin(), decoded_string.end());

    // 使用 OpenCV 将字节数组转换为 cv::Mat
    cv::Mat img = cv::imdecode(data, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not decode image" << std::endl;
        return;
    }

    // Convert to grayscale
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    // Histogram equalization
    cv::equalizeHist(img_gray, img_gray);

    // Load the cascade classifier
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(cascade_name)) {
        std::cout << "Error loading cascade file: " << cascade_name << std::endl;
        return;
    }

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img_gray, faces);

    // Draw rectangles around each face
    for (const auto& face : faces) {
        cv::rectangle(img, face, cv::Scalar(255, 0, 255), 5);
    }

    // Display the result
    cv::imshow("Face detection", img);
    cv::waitKey(0);  // Wait for a key press to close the window
}