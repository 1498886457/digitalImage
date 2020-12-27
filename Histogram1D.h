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

    static Mat getHistogram(const Mat& image);  // �õ��ݶ�ֱ��ͼ����ֵ
    static Mat getHistogramImage(const cv::Mat& image, int zoom);  // �õ���ֵ������ʾ��ͼ�������
    static Mat getImageOfHistogram(const Mat& hist, int zoom);  // ��ͼ�����淽������


private:
    int histSize[1]; // ֱ��ͼ�е����ӵ�����
    float hranges[2]; // ֵ��Χ
    const float* ranges[1];  // ֵ��Χ��ָ��
    int channels[1];  // Ҫ����ͨ������

};