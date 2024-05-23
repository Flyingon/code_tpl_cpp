#include <opencv2/opencv.hpp>
#include <iostream>


void img_gray(const cv::Mat &img, cv::Mat &result) {

    // Convert to grayscale
    cv::cvtColor(img, result, cv::COLOR_BGR2GRAY);

}


void canny_edge(const cv::Mat &img, cv::Mat &result) {

    cv::Mat grayImage;
    cv::cvtColor(img, grayImage, cv::COLOR_BGR2GRAY);
    cv::Canny(grayImage, result, 100, 200);
}

void gaussian_blur(const cv::Mat &img, cv::Mat &result) {

    cv::GaussianBlur(img, result, cv::Size(15, 15), 0);

}

void rotation(const cv::Mat &img, cv::Mat &result) {

    cv::Point2f center(img.cols/2.0, img.rows/2.0);
    double angle = 45.0;
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(img, result, rotationMatrix, img.size());

}

/*
 	1.	边缘检测：
	•	将图像转换为灰度图像。
	•	使用中值滤波器来减少噪声。
	•	使用 Canny 边缘检测算法检测边缘。
	2.	边缘增强：
	•	使用膨胀操作（cv::dilate）来增强边缘。
	•	使用腐蚀操作（cv::erode）来调整边缘的厚度。
	•	通过阈值化（cv::threshold）将边缘图像转换为二值图像。
	3.	图像平滑：
	•	使用双边滤波器（cv::bilateralFilter）对图像进行平滑处理，保留边缘细节。
	4.	融合处理：
	•	使用按位与操作（cv::bitwise_and）将边缘图像和平滑后的图像结合，形成卡通效果
*/
void cartoonV1 (const cv::Mat &img, cv::Mat &result) {
    cv::Mat grayImage, edges;
    cv::cvtColor(img, grayImage, cv::COLOR_BGR2GRAY);
    cv::medianBlur(grayImage, grayImage, 7); // Reduce noise
    cv::Canny(grayImage, edges, 50, 150);

    // Step 2: Edge enhancement
    cv::Mat edgesDilated;
    cv::dilate(edges, edgesDilated, cv::Mat(), cv::Point(-1, -1));
    cv::erode(edgesDilated, edges, cv::Mat(), cv::Point(-1, -1));
    cv::threshold(edges, edges, 127, 255, cv::THRESH_BINARY_INV);

    // Step 3: Image smoothing with bilateral filter
    cv::Mat smoothedImage;
    cv::bilateralFilter(img, smoothedImage, 9, 75, 75);

    // Step 4: Combine edges with smoothed image
//    cv::Mat cartoonImage;
    cv::bitwise_and(smoothedImage, smoothedImage, result, edges);
}

/*
	1.	边缘检测：
	•	将图像转换为灰度图像。
	•	使用中值滤波器减少噪声。
	•	使用 Canny 边缘检测算法检测边缘。
	•	使用阈值化将边缘图像转换为二值图像。
	2.	颜色量化：
	•	使用K-means聚类算法减少图像的颜色数量。这个步骤有助于将图像的颜色变得更加平滑和简单，类似于动漫风格。
	3.	融合处理：
	•	使用按位与操作将边缘图像和颜色量化后的图像结合，形成动漫效果
 */

void colorQuantization(const cv::Mat& src, cv::Mat& dst, int k) {
    cv::Mat data;
    src.convertTo(data, CV_32F);
    data = data.reshape(1, data.total());

    // Apply K-means clustering
    std::vector<int> labels;
    cv::Mat1f colors;
    cv::kmeans(data, k, labels,
               cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 10, 1.0),
               3, cv::KMEANS_PP_CENTERS, colors);

    // Convert back to 8-bit color and reshape
    dst = cv::Mat(src.size(), src.type());
    for (size_t i = 0; i < data.rows; ++i) {
        dst.at<cv::Vec3b>(i / src.cols, i % src.cols) = colors(labels[i], 0);
    }
}

void cartoonV2 (const cv::Mat &img, cv::Mat &result) {
    // Step 1: Edge detection
    cv::Mat grayImage, edges;
    cv::cvtColor(img, grayImage, cv::COLOR_BGR2GRAY);
    cv::medianBlur(grayImage, grayImage, 7); // Reduce noise
    cv::Canny(grayImage, edges, 50, 150);
    cv::threshold(edges, edges, 100, 255, cv::THRESH_BINARY_INV);

    // Step 2: Image smoothing with bilateral filter
    cv::Mat smoothedImage;
    cv::bilateralFilter(img, smoothedImage, 9, 75, 75);

    // Step 3: Combine edges with smoothed image
    cv::Mat edgesColor;
    cv::cvtColor(edges, edgesColor, cv::COLOR_GRAY2BGR); // Convert edges to 3 channels
    result = smoothedImage & edgesColor;
}

// Function to apply pixelation effect
cv::Mat pixelateImage(const cv::Mat& src, cv::Mat &result, int pixelSize) {
    cv::Mat smallImage;
    // Resize down
    cv::resize(src, smallImage, cv::Size(src.cols / pixelSize, src.rows / pixelSize), 0, 0, cv::INTER_LINEAR);
    // Resize up to the original size
    cv::resize(smallImage, result, cv::Size(src.cols, src.rows), 0, 0, cv::INTER_NEAREST);
    return result;
}
