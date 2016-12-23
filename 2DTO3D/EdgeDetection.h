#pragma once
#ifndef __MYHEADER_EDGE_H
#define __MYHEADER_EDGE_H
#include<iostream>
#include<stdio.h>
#include<stdarg.h>
#include<vector>
#include<string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "potracelib.h"
class EdgeDetection
{
public:
	EdgeDetection();

	cv::Mat detectImageEdges(cv::Mat image);

	void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);

	static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);

	~EdgeDetection();
};

#endif
