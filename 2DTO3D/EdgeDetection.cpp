#include "EdgeDetection.h"


EdgeDetection::EdgeDetection()
{
}


cv::Mat EdgeDetection::detectImageEdges(cv::Mat image)
{
	// Apply Canny edge detector
	cv::Mat imgContours;
	double thresh = 200; // try different values to see effect
	Canny(image, imgContours, 0.4*thresh, thresh); // low, high threshold

	
	return imgContours;

}

EdgeDetection::~EdgeDetection()
{
}

