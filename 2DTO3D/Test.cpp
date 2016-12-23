#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "stdio.h"
#include "string"
#include <stdlib.h>

using namespace cv;
using namespace std;

int lowerH = 168;
int upperH = 256;

int lowerS = 175;
int upperS = 256;

int lowerV = 0;
int upperV = 256;

IplImage* frame = 0;
IplImage* frame2 = 0;
IplImage* imgHSV = 0;
IplImage* imgThresh = 0;

//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;

void draw_conture(IplImage * temp)
{
	/*
	cv::Mat tempm(temp,true);
	findContours( tempm , contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	vector<vector<cv::Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<float>area( contours.size() );

	for(  int i = 0; i < contours.size(); i++ )
	{
	approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
	boundRect[i] = boundingRect( Mat(contours_poly[i]) ) ;
	area[i]= contourArea(Mat(contours_poly[i]));
	}

	const CvScalar color=CV_RGB(0x00,0xFF,0x00);
	for( int i = 0; i< contours.size(); i++ )
	{
	if (area[i]>1000)
	rectangle(tempm, boundRect[i].tl(), boundRect[i].br(), color, 1, 1, 0 );
	}
	*/

	CvSeq* contour;  //hold the pointer to a contour
	CvSeq* result;     //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	cvFindContours(temp, storage, &contour, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	for (; contour != 0; contour = contour->h_next)
	{
		result = cvApproxPoly(contour, sizeof(CvContour),
			storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);
		CvRect rect = cvBoundingRect(contour, 0); //extract bounding box for current contour
		if (cvContourArea(result, CV_WHOLE_SEQ, 0) >= 1000)
		{
			//cvDrawContours(frame, contour, CV_RGB(0,0,255), CV_RGB(0,0,255), 2, 1, 8, cvPoint(0, 0));
			frame2 = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
			cvCopy(frame, frame2);
			cvRectangle(frame2, cvPoint(rect.x, rect.y),
				cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(0, 0, 255), 2, 8, 0);
		}
	}
	cvShowImage("Object Color Range", frame2);
}

#pragma region trackbar

void on_trackbar1(int position)
{
	lowerH = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar2(int position)
{
	upperH = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar3(int position)
{
	lowerS = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar4(int position)
{
	upperS = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar5(int position)
{
	lowerV = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar6(int position)
{
	upperV = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

#pragma endregion trackbar

int main()
{
	cvNamedWindow("Object Color Range", 1);
	cvNamedWindow("Object Detected", 1);

	cvCreateTrackbar("LowerH", "Object Detected", &lowerH, 256, on_trackbar1);
	cvCreateTrackbar("UpperH", "Object Detected", &upperH, 256, on_trackbar2);
	cvCreateTrackbar("LowerS", "Object Detected", &lowerS, 256, on_trackbar3);
	cvCreateTrackbar("UpperS", "Object Detected", &upperS, 256, on_trackbar4);
	cvCreateTrackbar("LowerV", "Object Detected", &lowerV, 256, on_trackbar5);
	cvCreateTrackbar("UpperV", "Object Detected", &upperV, 256, on_trackbar6);
	frame = cvLoadImage("stop.jpg", 1);

	imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, imgHSV, CV_BGR2HSV);
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);

	cvShowImage("Object Detected", imgThresh);
	cvShowImage("Object Color Range", frame);

	draw_conture(imgThresh);
	cvWaitKey(0);

	cvReleaseImage(&imgHSV);
	cvReleaseImage(&imgThresh);
	cvReleaseImage(&frame);


	cvDestroyAllWindows();
	return 0;
}