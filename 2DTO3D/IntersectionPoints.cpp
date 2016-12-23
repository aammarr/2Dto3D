#include "IntersectionPoints.h"

IntersectionPoints::IntersectionPoints()
{

}

IntersectionPoints::~IntersectionPoints()
{

}

int IntersectionPoints::IsPointInBoundingBox(float x1, float y1, float x2, float y2, float px, float py)
{
	float left, top, right, bottom; // Bounding Box For Line Segment
	// For Bounding Box
	if (x1 < x2)
	{
		left = x1;
		right = x2;
	}
	else
	{
		left = x2;
		right = x1;
	}
	if (y1 < y2)
	{
		top = y1;
		bottom = y2;
	}
	else
	{
		top = y1;
		bottom = y2;
	}

	if ((px + 1.01) >= left && (px - 1.01) <= right &&
		(py + 1.01) >= top && (py - 1.01) <= bottom)
	{
		return 1;
	}
	else
		return 0;
}

int IntersectionPoints::LineSegmentIntersection(float l1x1, float l1y1, float l1x2, float l1y2,
	float l2x1, float l2y1, float l2x2, float l2y2,
	float *m1, float *c1, float *m2, float *c2,
	float* intersection_X, float* intersection_Y)
{
	//cout << "entered" << l1x1 << "\t" << l1y1 << "\t" << l1x2 << "\t" << l1y2 << endl;
	//cout  << l2x1 << "\t" << l2y1 << "\t" << l2x2 << "\t" << l2y2 << endl;
	float dx, dy;

	dx = l1x2 - l1x1;
	dy = l1y2 - l1y1;
	//cout << "X: " << dx << "\t Y: "<< dy <<endl;
	(dx == 0 ? dx = 0.0001 : dy = 0.0001);
	*m1 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	*c1 = l1y1 - *m1 * l1x1; // which is same as y2 - slope * x2

	dx = l2x2 - l2x1;
	dy = l2y2 - l2y1;
	(dx == 0 ? dx = 0.0001 : dy = 0.0001);
	*m2 = dy / dx;
	//cout << "m2" << *m2 << endl;
	// y = mx + c
	// intercept c = y - mx
	*c2 = l2y1 - *m2 * l2x1; // which is same as y2 - slope * x2

	if ((*m1 - *m2) == 0)
	{
		return 0;
	}	
	else
	{

		*intersection_X = (*c2 - *c1) / (*m1 - *m2);
		//cout << "X AXIS "<<*intersection_X << endl;
		*intersection_Y = *m1 * *intersection_X + *c1;
		//cout << "Y AXIS" <<*intersection_Y << endl;
		return 1;
		/*if (IsPointInBoundingBox(l1x1, l1y1, l1x2, l1y2, *intersection_X, *intersection_Y) == 1 &&
			IsPointInBoundingBox(l2x1, l2y1, l2x2, l2y2, *intersection_X, *intersection_Y) == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}*/
			
	}
	

}