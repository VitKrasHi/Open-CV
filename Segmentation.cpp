/Сегментация. Конвертация изображения в HSV

#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("input.jpg");
    cv::Mat hsv, mask, result;

    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::inRange(hsv, cv::Scalar(35, 50, 50), cv::Scalar(85, 255, 255), mask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::drawContours(img, contours, -1, cv::Scalar(0, 255, 0), 2);

    cv::imshow("Segmentation", img);
    cv::waitKey(0);
    return 0;
}
