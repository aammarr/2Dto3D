#pragma once
//#include<opencv\cv.h>
//#include<opencv\highgui.h>
#include<iostream>
#include<stdio.h>
#include<stdarg.h>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>


class LineDetection
{
	std::vector<cv::Vec4i> lines;
	std::vector<cv::Vec4f> linesLSD;
	std::vector<cv::Vec4i> linesSH;
public:
	LineDetection();
	cv::Mat detectImageLines(cv::Mat imgContours/*, std::vector<cv::Vec4i> lines*/);
	cv::Mat detectVerticalLines(cv::Mat image, int value);
	cv::Mat detectHorizontalLines(cv::Mat image, int value);
	void detectLSD(cv::Mat image);
	cv::Mat Standard_Hough(int, void*, cv::Mat edges, cv::Mat imageLines);
	bool isEqual(const cv::Vec4i& _l1, const cv::Vec4i& _l2);
	//void LineSegmentDetector::detect(const InputArray _image, OutputArray _lines, OutputArray width = noArray(), OutputArray prec = noArray(), OutputArray nfa = noArray());
	bool intersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2, cv::Point2f &r);
	std::vector<cv::Vec4i> getLines();
	std::vector<cv::Vec4f> getLinesLSD();
	std::vector<cv::Vec4i> getLinesSH();
	~LineDetection();
};

