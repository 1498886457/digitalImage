#include "Histogram1D.h"

Histogram1D::Histogram1D() {
    // ׼��һάֱ��ͼ��Ĭ�ϲ���
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

    // ����ֱ��ͼ
    cv::calcHist(&image, 1, h1.channels, cv::Mat(), hist, 1, h1.histSize, h1.ranges);

    return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat& image, int zoom = 1) {  // �õ���ֵ������ʾ��ͼ�������
    // ���ȼ���ֱ��ͼ
    Mat hist = getHistogram(image);

    // ����ͼ��
    return getImageOfHistogram(hist, zoom);
}

cv::Mat Histogram1D::getImageOfHistogram(const Mat& hist, int zoom) {  // ��ͼ�����淽������, ֱ��ͼͼ��
    // ȡ������ֵ�����ֵ����Сֵ
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

    // ȡ��ֱ��ͼ�Ĵ�С
    int histSize = hist.rows;

    // ������ʾֱ��ͼ�ķ���ͼ��
    cv::Mat histImg(histSize * zoom, histSize * zoom, CV_8U, cv::Scalar(255));
    // ������ߵ�Ϊ90%����ͼ��߶ȣ������Ӹ���
    int hpt = static_cast<int>(0.9 * histSize);
    // Ϊÿ�����ӻ���ֱ��
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