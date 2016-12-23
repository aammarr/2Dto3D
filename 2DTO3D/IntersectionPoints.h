#include <iostream>
#include <math.h>

class IntersectionPoints
{
	public:
		IntersectionPoints();
		~IntersectionPoints();

		int IsPointInBoundingBox(float x1, float y1, float x2, float y2, float px, float py);

		int LineSegmentIntersection(float l1x1, float l1y1, float l1x2, float l1y2,
			float l2x1, float l2y1, float l2x2, float l2y2,
			float *m1, float *c1, float *m2, float *c2,
			float* intersection_X, float* intersection_Y);



};

