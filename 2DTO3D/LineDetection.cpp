#include "LineDetection.h"


LineDetection::LineDetection()
{
	
}

void LineDetection::detectLSD(cv::Mat image)
{
	std::vector<cv::Vec4f> lines_std;
	bool a = false;
	cv::Vec4i tempEven, tempOdd;
	cv::Mat image_1 = cv::Mat::zeros(800, 800, CV_8UC3);
	cv::Ptr<cv::LineSegmentDetector> ls = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
	
	// Detect the lines
	ls->detect(image, lines_std);
	
	//ls->drawSegments(drawnLines, lines_std);
	for (size_t i = 0; i < lines_std.size(); i++)
	{
		cv::Vec4i l = lines_std[i];			//l=point
		l[0] = ceilf(l[0]);
		l[1] = ceilf(l[1]);
		l[2] = ceilf(l[2]);
		l[3] = ceilf(l[3]);
		lines_std[i] = l;
		if (l[0] == l[2] || l[1] == l[3])
		{
			std::cout << "line_lsd[" << i << "] = " << lines_std[i] << std::endl;
			//cout << "line_lsd[" << i << "] = " << l[0] << l[1] << l[2] << l[3] << endl;
			linesLSD.push_back(l);
		}	

	}

	//cout << "LSD: " << lines_std.size() << endl;
	//cout << "LSD: "<< lines.size() << endl;
	cv::Mat drawnLines(image_1);
	ls->drawSegments(drawnLines, linesLSD);
	cv::imshow("LSD", drawnLines);
	//waitKey();

}


cv::Mat LineDetection::detectImageLines(cv::Mat imgContours/*, std::vector<cv::Vec4i> lines_i*/)
{
	//this->lines = lines_i;
	cv::Mat image = cv::Mat::zeros(imgContours.rows, imgContours.cols, CV_8UC3);
	//bool a = false;
	cv::HoughLinesP(imgContours, lines, 1, CV_PI / 180, 100, 80, 20);
	std::cout << "lines " << lines.size() << std::endl;
	//std::vector<int> labels;

	//int numberOfLines = cv::partition(lines, labels, );

	for (size_t i = 0; i < lines.size(); i++)
	{
		cv::Vec4i l = lines[i];			//l=point
		std::cout << "line[" << i << "] = " << lines[i] << std::endl;
		line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
		/*if (l[0] == l[2] || l[1] == l[3])
		{
			cv::line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 255, 255), 1, CV_AA);
			lines.push_back(l);
		}*/
			
	}
	//line(image, Point(9, 540), Point(589, 540), Scalar(0, 0, 255), 1, CV_AA);
	//line(image, Point(201, 62), Point(201, 19), Scalar(255, 0, 255), 1, CV_AA);
	/*line(image, Point(62, 417), Point(62, 417), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(193, 417), Point(193,47), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(354, 312), Point(354, 312), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(354, 314), Point(354,314), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(354, 298), Point(354,298), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(193, 419), Point(193,419), Scalar(100, 2, 55), 5, CV_AA);
	line(image, Point(193, 421), Point(193,421), Scalar(100, 2, 55), 5, CV_AA);*/
	return image;
}

bool LineDetection::intersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2,
	cv::Point2f &r)
{
	//cout << "entered" <<endl;
	cv::Point2f x = o2 - o1;
	cv::Point2f d1 = p1 - o1;
	cv::Point2f d2 = p2 - o2;

	float cross = d1.x*d2.y - d1.y*d2.x;
	if (abs(cross) < /*EPS*/1e-8 )
		return false;

	double t1 = (x.x * d2.y - x.y * d2.x) / cross;
	r = o1 + d1 * t1;
	return true;

}

bool LineDetection::isEqual(const cv::Vec4i& _l1, const cv::Vec4i& _l2)
{
	cv::Vec4i l1(_l1), l2(_l2);

	float length1 = sqrtf((l1[2] - l1[0])*(l1[2] - l1[0]) + (l1[3] - l1[1])*(l1[3] - l1[1]));
	float length2 = sqrtf((l2[2] - l2[0])*(l2[2] - l2[0]) + (l2[3] - l2[1])*(l2[3] - l2[1]));

	float product = (l1[2] - l1[0])*(l2[2] - l2[0]) + (l1[3] - l1[1])*(l2[3] - l2[1]);

	if (fabs(product / (length1 * length2)) < cos(CV_PI / 30))
		return false;

	float mx1 = (l1[0] + l1[2]) * 0.5f;
	float mx2 = (l2[0] + l2[2]) * 0.5f;

	float my1 = (l1[1] + l1[3]) * 0.5f;
	float my2 = (l2[1] + l2[3]) * 0.5f;
	float dist = sqrtf((mx1 - mx2)*(mx1 - mx2) + (my1 - my2)*(my1 - my2));

	if (dist > std::max(length1, length2) * 0.5f)
		return false;

	return true;
}

std::vector<cv::Vec4i> LineDetection::getLines()
{
	//cout << lines.size() << endl;
	return lines;
}

std::vector<cv::Vec4f> LineDetection::getLinesLSD()
{
	//cout << lines.size() << endl;
	return linesLSD;
}

std::vector<cv::Vec4i> LineDetection::getLinesSH()
{
	//cout << lines.size() << endl;
	return linesSH;
}

cv::Mat LineDetection::Standard_Hough(int, void*, cv::Mat edges, cv::Mat imageLines)
{
	std::vector<cv::Vec2f> s_lines;
	//vector<Vec4i> a_lines;
	//cvtColor(edges, standard_hough, COLOR_GRAY2BGR);

	/// 1. Use Standard Hough Transform
	HoughLines(edges, s_lines, 1, CV_PI / 180, 50 + 150, 0, 0);

	/// Show the result
	for (size_t i = 0; i < s_lines.size(); i++)
	{
		float r = s_lines[i][0], 
		t = s_lines[i][1];
		double cos_t = cos(t), 
			sin_t = sin(t);
		double x0 = r*cos_t, 
			y0 = r*sin_t;
		double alpha = 1000;

		cv::Point pt1(cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t));
		cv::Point pt2(cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t));
		//cout << pt1 << pt2 << endl;
		line(imageLines, pt1, pt2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
		//line(imageLines, cv::Point(-1000, 289), cv::Point(1000, 289), cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
		//line(imageLines, cv::Point(-1000, 467), cv::Point(1000, 467), cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
		//line(imageLines, cv::Point(-1000, 277), cv::Point(1000, 277), cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
		//line(imageLines, cv::Point(-1000, 455), cv::Point(1000, 455), cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
		linesSH.push_back(cv::Vec4i(pt1.x, pt1.y, pt2.x, pt2.y));
	}

	imshow("", imageLines);
	return imageLines;
}

cv::Mat LineDetection::detectHorizontalLines(cv::Mat image, int value)
{
	cv::Scalar intensity1 = 0;
	cv::Mat src2 = image.clone();
	for (int i = 0; i < image.rows - value; i++)  
	{
		for (int j = 0; j < image.cols - value; j++) 
		{
			cv::Scalar intensity2 = 0;
			for (int p = 0; p<value; p++) 
			{
				for (int q = 0; q<value; q++)  
				{
					intensity1 = image.at<uchar>(i + p, j + q);
					if ((p == (value - 1) / 2))
					{
						intensity2.val[0] += (value - 1)*intensity1.val[0];
					}
					else
					{
						intensity2.val[0] += (-1)*intensity1.val[0];
					}
				}
			}
			src2.at<uchar>(i + (value - 1) / 2, j + (value - 1) / 2) = intensity2.val[0] / (value*value);
		}
	}
	imshow("Low Pass Filtered Image", src2);
	return src2;
	//Display the original image
	//namedWindow("Display Image");
	//imshow("Display Image", src1);

	//Display the Low Pass Filtered Image image
	//namedWindow("Low Pass Filtered Image");
	imshow("Low Pass Filtered Image", src2);
	
}

cv::Mat LineDetection::detectVerticalLines(cv::Mat image, int value)
{
	cv::Scalar intensity1 = 0;
	cv::Mat src2 = image.clone();
	for (int i = 0; i < image.rows - value; i++) 
	{
		for (int j = 0; j < image.cols - value; j++) 
		{
			cv::Scalar intensity2 = 0;
			for (int p = 0; p<value; p++) 
			{
				for (int q = 0; q<value; q++) 
				{
					intensity1 = image.at<uchar>(i + p, j + q);
					if ((q == (value - 1) / 2))
					{
						intensity2.val[0] += (value - 1)*intensity1.val[0];
					}
					else
					{
						intensity2.val[0] += (-1)*intensity1.val[0];
					}
				}
			}
			src2.at<uchar>(i + (value - 1) / 2, j + (value - 1) / 2) = intensity2.val[0] / (value*value);
		}
	}
	return src2;
}


LineDetection::~LineDetection()
{
}
