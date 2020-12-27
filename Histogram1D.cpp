#include "Histogram1D.h"

Histogram1D::Histogram1D() {
    // 准备一维直方图的默认参数
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 256.0;
    ranges[0] = hranges;
    channels[0] = 0;
}


Histogram1D::~Histogram1D()
{
}

cv::Mat Histogram1D::getHistogram(const cv::Mat& image) {
    cv::Mat hist;
    Histogram1D h1;

    // 计算直方图
    cv::calcHist(&image, 1, h1.channels, cv::Mat(), hist, 1, h1.histSize, h1.ranges);

    return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat& image, int zoom = 1) {  // 得到数值，并显示成图像的类型
    // 首先计算直方图
    Mat hist = getHistogram(image);

    // 创建图像
    return getImageOfHistogram(hist, zoom);
}

cv::Mat Histogram1D::getImageOfHistogram(const Mat& hist, int zoom) {  // 画图，上面方法调用, 直方图图像
    // 取得箱子值得最大值和最小值
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

    // 取得直方图的大小
    int histSize = hist.rows;

    // 用于显示直方图的方形图像
    cv::Mat histImg(histSize * zoom, histSize * zoom, CV_8U, cv::Scalar(255));
    // 设置最高点为90%（即图像高度）的箱子个数
    int hpt = static_cast<int>(0.9 * histSize);
    // 为每个箱子画垂直线
    for (int h = 0; h < histSize; h++) {
        float binVal = hist.at<float>(h);
        if (binVal > 0)
        {
            int intensity = static_cast<int>(binVal * hpt / maxVal);
            cv::line(histImg, cv::Point(h * zoom, histSize * zoom),
                cv::Point(h * zoom, (histSize - intensity) * zoom),
                cv::Scalar(0), zoom);
        }
    }
    return histImg;

}