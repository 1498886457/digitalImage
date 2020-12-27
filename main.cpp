#include"Histogram1D.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;
const int grayMax = 255;

Mat finalImage(Mat image)
{
	int graylevel[grayMax + 1];
	Mat img;
	image.copyTo(img);
	if (!image.data)
	{
		Mat error;
		return error;
	}
	for (int i = 0; i < image.rows - 1; i++)
	{
		uchar* ptr = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols - 1; j++)
		{
			int x = ptr[j];
			graylevel[x]++;
		}
	}
	for (int i = 0; i < img.rows - 1; i++)
	{
		uchar* imgptr = img.ptr<uchar>(i);
		uchar* imageptr = image.ptr<uchar>(i);
		for (int j = 0; j < img.cols - 1; j++)
		{
			int sumpiexl = 0;
			for (int k = 0; k < imageptr[j]; k++)
			{
				sumpiexl = graylevel[k]+ sumpiexl;
			}
			imgptr[j] = (grayMax * sumpiexl / (image.rows * image.cols));
		}
	}

	return img;
}

Mat Demist(Mat image) {
	int n = image.rows * image.cols;
	int graylevel[grayMax + 1] = { 0 };
	double px[grayMax + 1] = { 0 };
	double cdfx[grayMax + 1] = { 0 };
	double cdfx_min = INT16_MAX;
	Mat img;
	image.copyTo(img);
	for (int i = 0; i < image.rows - 1; i++)
	{
		uchar* ptr = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols - 1; j++) {
			int x = ptr[j];
			graylevel[x]++;
		}
	}
	for (int i = 0; i < grayMax + 1; i++)
		px[i] = graylevel[i] / (double)n;
	bool flag = 1;
	for (int i = 0; i < grayMax + 1; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cdfx[i] += px[i];
		}
		if (flag == 1 && cdfx[i] != 0)
		{
			cdfx_min = cdfx[i];
			flag == 0;
		}
	}

	for (int i = 0; i < img.rows - 1; i++)
	{
		uchar* ptr = img.ptr<uchar>(i);
		for (int j = 1; j < img.cols - 1; j++) {
			double temp = (cdfx[ptr[j]] - cdfx_min)/(n - cdfx_min);
			temp *= grayMax;
			ptr[j] = round(temp);
		}
	}
	return img;
}
int line(int x, double k,double b) {
	return k * x + b;
}

Mat newImage(Mat image){
	int N = image.rows * image.cols;
	int graylevel[grayMax + 1] = { 0 };
	int px_min = 0;
	int px_max = 255;
	Mat img;
	image.copyTo(img);
	for (int i = 0; i < image.rows - 1; i++)
	{
		uchar* ptr = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols - 1; j++) {
			int x = ptr[j];
			graylevel[x]=1;
		}
	}


	for (int i = 0; i < grayMax + 1; i++)
	{ 		if (graylevel[i] != 0) {
			px_min = i;
			break;
		}
	}
	for (int i = grayMax; i >= 0; i--)
	{
		if (graylevel[i] != 0) {
			px_max = i;
			break;
		}
	}
	double k,b;
	if (px_max - px_min != 0)
	{
		k = 255 / (px_max - px_min);
		b = 255 - k * px_max;
	}
	else {
		k = 1;
		b = 0;
	}

	for (int i = 0; i < img.rows - 1; i++)
	{
		uchar* ptr = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols - 1; j++) {
			ptr[j] = line(ptr[j],k,b);
		}
	}
	return img;
}

int main()
{
	Mat image = imread("Lpic5.jpg",1);
	Histogram1D h;
	cvtColor(image, image, CV_BGR2GRAY);
	Mat out = Demist(image); 
	imshow("原图1", h.getHistogramImage(image, 1));
	imshow("原图", image);
	imshow("处理后", out);
	imshow("处理后1", h.getHistogramImage(out, 1));
	equalizeHist(image, image);
	imshow("openCV", h.getHistogramImage(image, 1));
	imshow("openCV1", image);
	waitKey();
	return 0;
}