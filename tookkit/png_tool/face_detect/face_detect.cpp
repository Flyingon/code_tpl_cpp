#include <opencv2/opencv.hpp>
#include <iostream>

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

//int main() {
//    std::string file_name = "path_to_image.jpg";  // Specify the path to your image
//    std::string cascade_name = "path_to_cascade.xml";  // Specify the path to your cascade file
//    face_detect(file_name, cascade_name);
//    return 0;
//}
