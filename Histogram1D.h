#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include"opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

class Histogram1D
{
public:
    Histogram1D();
    ~Histogram1D();

    static Mat getHistogram(const Mat& image);  // 得到梯度直方图的数值
    static Mat getHistogramImage(const cv::Mat& image, int zoom);  // 得到数值，并显示成图像的类型
    static Mat getImageOfHistogram(const Mat& hist, int zoom);  // 画图，上面方法调用


private:
    int histSize[1]; // 直方图中的箱子的数量
    float hranges[2]; // 值范围
    const float* ranges[1];  // 值范围的指针
    int channels[1];  // 要检查的通道数量

};