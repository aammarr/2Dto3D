#include "PreProcessing.h"


PreProcessing::PreProcessing()
{
	
}


cv::Mat PreProcessing::convertToBnW(cv::Mat imgInput)
{

	
	if (imgInput.channels() == 3)
	{
		cv::cvtColor(imgInput, imgInput, CV_BGR2GRAY);
	}
	
	return imgInput;
	

}

cv::Mat PreProcessing::applyThreshold(cv::Mat imgInput)
{
	cv::Mat binaryMat = cv::Mat(imgInput.size(), CV_8U);
	std::cout << binaryMat.type() << std::endl;
	//Apply thresholding
	cv::threshold(imgInput, binaryMat, 185, 255, cv::THRESH_BINARY);
	std::cout << binaryMat.rows << " , " << binaryMat.cols << std::endl;
	return binaryMat;
}

PreProcessing::~PreProcessing()
{

}
