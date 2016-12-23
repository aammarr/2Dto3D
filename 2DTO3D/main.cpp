#include"EdgeDetection.h"
#include"PreProcessing.h"
#include"LineDetection.h"
#include"IntersectionPoints.h"
//#include "GLRendering.h"
#include<fstream>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>


cv::Mat imageInput(); 
void unsharpMask(cv::Mat& im);
void showImage(cv::Mat imgInput, std::string message);
std::vector<cv::Point2f> checkForIntersections(IntersectionPoints* intersections, std::vector<cv::Vec4i> lines);
cv::Vec4i findMinAndMaxValues(std::vector<cv::Vec4i> lines);
void writeToFile(std::vector<cv::Vec4i>);
void writeToFile(cv::Vec4i);
std :: string getFileName(std :: string filePath);

int main(int argc, char** argv)
{

	cv::Mat imgInput = imageInput();
	showImage(imgInput, "orignal image");

	PreProcessing *imagePreprocessing = new PreProcessing();
	cv::Mat imgI = imagePreprocessing->convertToBnW(imgInput);
	//imgI = imagePrepq																																																																																																																																																																																																																					rocessing->applyThreshold(imgI);
	//showImage(imgI, "bnw image");

	EdgeDetection *edgeDetection = new EdgeDetection();
	cv::Mat imgContours = edgeDetection->detectImageEdges(imgI);
	//imgContours = imagePreprocessing->applyThreshold(imgInput);
	//showImage(imgContours, "Contoured Image");

	std::vector<cv::Vec4i> linesSH, linesHP;
	//vector<Vec4f> linesLSD;
	cv::Mat image = cv::Mat::zeros(imgContours.rows, imgContours.cols, CV_8UC3);
	LineDetection *lineDetection = new LineDetection();
	cv::Mat imgLineDetect = lineDetection->Standard_Hough(0,0,imgContours,image);
	linesSH = lineDetection->getLinesSH();
	cv::Vec4i boundaryOfHome = findMinAndMaxValues(linesSH);
	imgLineDetect =lineDetection->detectImageLines(imgContours);
	linesHP = lineDetection->getLines();
	showImage(imgLineDetect, "detected lines");
	writeToFile(boundaryOfHome);
	writeToFile(linesHP);
	
	//std::cout << "lines: " << lines.size() << std::endl;
	//cv::Vec4i boundaryOfHome = findMinAndMaxValues(lines);
	
	/*for (int i = 0; i < lines.size(); i++)
	{
		
		std::cout << "line[: " <<i << "] "<< lines.at(i) << std::endl;
	}*/
	
	/*linesLSD = lineDetection->getLinesLSD();
	cout << "lines: " << linesLSD.size() << endl;
	for (int i = 0; i < linesLSD.size(); i++)
	{
		cout << "line[: " << i << "] " << linesLSD.at(i) << endl;
	}*/
	//IntersectionPoints *intersections = new IntersectionPoints();
	//vector<Point2f> points  = checkForIntersections(intersections, lines);

	//system("C://Users//ammar//Documents//Visual Studio 2013//Projects//OpenGL_Test//First//Debug//First.exe");
	//String^ FilePath = "C://Users//ammar//Documents//Visual Studio 2013//Projects//OpenGL_Test//First//Debug//First.exe";

	system("explorer C:\\Users\\ammar\\Documents\\Visual Studio 2013\\Projects\\OpenGL_Test\\First\\Debug\\First.exe\" ");

	 cv::waitKey(0);
	

	
	
	return(0);
	
		
}
/*
std:: string getFileName(std:: string filePath)
{
	std:: string line;
	std:: ifstream myFile;
	myFile.open(filePath);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			
		}
		myfile.close();
	}

	return line;
}
*/


cv::Mat imageInput()
{
	
	// read an image
	
	std::ifstream file("D:/aammarr.ahmed/uni/Sem-8/FYP II/FYP_2_hani/FYP_2/FYP2/FYP2/floorplanPath.txt");
	std::string floorplan;
	if (file.is_open())
	{
		while (std::getline(file, floorplan))
		{
			std::cout << floorplan << std::endl;
			
		}

		file.close();
	}
	else
		std::cout << "Unable to open file";

	//cv::Mat imgInput = cv::imread(floorplan);
	cv::Mat imgInput = cv::imread("floorplan1.png");
	if (imgInput.data == NULL)
	{
		std::printf("Hey! Can't read image\n");
		std::system("PAUSE");	
	}
	/*Mat image = Mat::zeros(600, 600, CV_8UC3);
	cv::Size s = imgInput.size(); 
	cv::Size s1 = image.size();
	cout << "size: " << s1 << endl;
	cout << "image size: " << s << endl;
	if (s.height > s1.height && s.width > s1.width)
	{
		resize(imgInput, imgInput, image.size(), 2, 1, INTER_LANCZOS4);
	}*/
	
	std::cout << "image size: " << imgInput.size() << std::endl;
	//showImage(imgInput, "Before sharpen");
	unsharpMask(imgInput);
	//showImage(imgInput, "After sharpen");
	return imgInput;
}

void showImage(cv::Mat imgInput, std::string message)
{
	imshow(message, imgInput);
	cv::waitKey(1500);
}

void unsharpMask(cv::Mat& im)
{
	cv::Mat tmp;
	cv::GaussianBlur(im, tmp, cv::Size(0, 0), 3);
	cv::addWeighted(im, 1.5, tmp, -0.5, 0, im);
}

std::vector<cv::Point2f> checkForIntersections(IntersectionPoints* intersections, std::vector<cv::Vec4i> lines)
{
	std::cout << lines.size() << std::endl;
	std::vector<cv::Point2f> intPoints;
	int val = 0;
	float m1 = 0, c1 = 0, m2 = 0, c2 = 0;
	float intersection_X = 0, intersection_Y = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		
		cv::Vec4i l = lines[i];
		std::cout << "first: " << l << std::endl;
		
		for (int j = i + 1; j < lines.size(); j++)
		{
			
			
			cv::Vec4i lj = lines[j];
			std::cout << "second: " << lj << std::endl;
			val = intersections->LineSegmentIntersection(l[0], l[1], l[2], l[3], lj[0], lj[1], lj[2], lj[3],
				&m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
			if (val == 0)
			{
				//cout << " lines[ " << i << ","<< j << "] dont intersect eachother" << endl;
			}
			else
			{
				std::cout << " lines[ " << i << "," << j << "] " << "intersect" << std::endl;
				std::printf("The two line segments intersect each other at %.2f, %.2f\n", intersection_X, intersection_Y);
				intPoints.push_back(cv::Point(intersection_X, intersection_Y));
			}
			/*if (l[0] == l[2]) //vertical
			{
				//cout << l[0] << l[2] << endl;
				if (lj[1] == lj[3])
				{
					cout << " lines[ " << i << j << "] "<< "y: "<<lj[1] <<","<< lj[3] <<" x: "<< l[0] <<","<< l[2] << endl;
					val = intersections->LineSegmentIntersection(l[0], l[1], l[2], l[3], lj[0], lj[1], lj[2], lj[3],
						&m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
					if (val == 0)
					{
						//cout << " lines[ " << i << ","<< j << "] dont intersect eachother" << endl;
					}	
					else
					{
						cout << " lines[ " << i <<"," << j << "] " << "intersect" << endl;
						printf("The two line segments intersect each other at %.2f, %.2f\n", intersection_X, intersection_Y);
						intPoints.push_back(cv::Point(intersection_X, intersection_Y));
					}
						

				}
			}
			else if (l[1] == l[3]) // horizontal
			{
				if (lj[0] == lj[2])
				{
					//cout << " line " << lj[1] << lj[3] << l[0] << l[2] << endl;
					val = intersections->LineSegmentIntersection(l[0], l[1], l[2], l[3], lj[0], lj[1], lj[2], lj[3],
						&m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
					if (val == 0)
					{
						//printf("The two line segments do not intersect each other\n");
					}
					else
					{
						printf("The two line segments intersect each other at %.2f, %.2f\n", intersection_X, intersection_Y);
						intPoints.push_back(cv::Point(intersection_X, intersection_Y));
					}
				}
			}*/
		}

	}
	return intPoints;

}
cv::Vec4i findMinAndMaxValues(std::vector<cv::Vec4i> lines)
{
	int minX = lines[0][0], minY = lines[0][1], maxX = lines[0][2], maxY = lines[0][3];
	minX = maxX = lines[0][0];//xstart
	minY = maxY = lines[0][1];//ystart
	std::cout << lines.size() << std::endl;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i][0] < minX)
		{
			minX = lines[i][1];
		}
		if (lines[i][2] < minX)
		{
			minX = lines[i][2];
		}
		if (lines[i][0] > maxX)
		{
			maxX = lines[i][0];
		}
		if (lines[i][2] > maxX)
		{
			maxX = lines[i][2];
		}
		if (lines[i][1] < minY)
		{
			minY = lines[i][1];
		}
		if (lines[i][1] > maxY)
		{
			maxY = lines[i][1];
		}
		if (lines[i][3] < minY)
		{
			minY = lines[i][1];
		}
		if (lines[i][3] > maxY)
		{
			maxY = lines[i][1];
		}

		std::cout << "line[: " << i << "] " << lines.at(i) << std::endl;
	}
	std::cout << "Max X: " << maxX << "Max Y: " << maxY << "Min X: " << minX << "Min Y: " << minY << std::endl;
	return cv::Vec4i(minX, minY, maxX, maxY);
}
void writeToFile(std::vector<cv::Vec4i> lines)
{
	std::ofstream myfile;
	myfile.open("lines.txt");
	for (int i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		myfile << v[0] << ",";
		myfile << v[1] << ",";
		myfile << v[2] << ",";
		myfile << v[3] << std::endl;
	}
	myfile.close();
}

void writeToFile(cv::Vec4i v)
{
	std::ofstream myfile;
	myfile.open("minMax.txt");
	myfile << v[0] << std::endl;
	myfile << v[1] << std::endl;
	myfile << v[2] << std::endl;
	myfile << v[3] << std::endl;

	myfile.close();
}
