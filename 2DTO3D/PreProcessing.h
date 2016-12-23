#pragma once
#ifndef __MYHEADER_H
#define __MYHEADER_H
//#include<opencv\cv.h>
//#include<opencv\highgui.h>
#include<iostream>
#include<stdio.h>
#include<stdarg.h>
#include<vector>
#include<string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

class PreProcessing
{
public:

	
	PreProcessing();

	//Conversion of orignal image to black and white
	cv::Mat convertToBnW(cv::Mat imgInput);
	cv::Mat PreProcessing::applyThreshold(cv::Mat imgInput);

	~PreProcessing();

	
};

#endif