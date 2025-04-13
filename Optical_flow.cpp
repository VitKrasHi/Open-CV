/ Оптический поток для трекинга движения

#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap("video.mp4");
    cv::Mat prevFrame, prevGray, currFrame, currGray;
    std::vector<cv::Point2f> prevPts, currPts;

    // Захват первого кадра
    cap >> prevFrame;
    cv::cvtColor(prevFrame, prevGray, cv::COLOR_BGR2GRAY);

    // Детекция углов (Shi-Tomasi)
    cv::goodFeaturesToTrack(prevGray, prevPts, 100, 0.3, 7);

    while (cap.read(currFrame)) {
        cv::cvtColor(currFrame, currGray, cv::COLOR_BGR2GRAY);

        // Вычисление оптического потока
        std::vector<uchar> status;
        std::vector<float> err;
        cv::calcOpticalFlowPyrLK(prevGray, currGray, prevPts, currPts, status, err);

        // Отрисовка треков
        for (size_t i = 0; i < currPts.size(); i++) {
            if (status[i]) {
                cv::line(currFrame, prevPts[i], currPts[i], cv::Scalar(0, 255, 0), 2);
                cv::circle(currFrame, currPts[i], 3, cv::Scalar(0, 0, 255), -1);
            }
        }

        cv::imshow("Optical Flow", currFrame);
        if (cv::waitKey(30) == 27) break;

        // Обновление предыдущего кадра
        prevGray = currGray.clone();
        prevPts = currPts;
    }

    return 0;
}
