// Scott Wiedemann
// 02/16/2014
// giftwrapping.cpp

#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
	public:	
		double x,y;
	
		Point()
		{ }

		Point(const double& A, const double& B)
		{
			x=A;
			y=B;
		}

		Point operator+ (const Point& a) const
		{
			Point result;
			result.x = x+a.x;
			result.y = y+a.y;
			return result;
		}

		Point operator+ (const double& a) const
		{
			Point result;
			result.x = x+a;
			result.y = y+a;
			return result;
		}

		Point operator- (const Point& a) const
		{
			Point result;
			result.x = x-a.x;
			result.y = y-a.y;
			return result;
		}

		Point operator- (const double& a) const
		{
			Point result;
			result.x = x-a;
			result.y = y-a;
			return result;
		}

		Point operator* (const Point& a) const
		{
			Point result;
			result.x = x*a.x;
			result.y = y*a.y;
			return result;
		}

		Point operator* (const double& a) const
		{
			Point result;
			result.x = x*a;
			result.y = y*a;
			return result;
		}

		Point operator/ (const Point& a) const
		{
			Point result;
			result.x = x/a.x;
			result.y = y/a.y;
			return result;
		}

		Point operator/ (const double& a) const
		{
			Point result;
			result.x = x/a;
			result.y = y/a;
			return result;
		}

		bool operator== (const Point& a) const
		{
			return (x == a.x && y == a.y);
		}

		double magnitude()
		{
			return sqrt((x*x)+(y*y));
		}

		double cross(const Point& P)
		{
			return x*P.y - y*P.x;
		}

		double dist(const Point& P) {
			return sqrt(((P.x-x)*(P.x-x))+((P.y-y)*(P.y-y)));
		}
};

//is point 3 a left turn or right turn with respect to point 1 and 2?
double ccw(Point p1, Point p2, Point p3) {
	return (p1 - p2).cross(p3 - p2);
}

vector<int> giftWrapping(Point* points, int length) {
	vector<int> convexHullIndices;

	int pointOnHullIndex = 0;
	int endPointIndex = 0;
	do {
		convexHullIndices.push_back(pointOnHullIndex);
		endPointIndex = 0;
		for(int i=1; i<length; i++) {
			if((points[pointOnHullIndex] == points[endPointIndex]) || ccw(points[pointOnHullIndex], points[endPointIndex], points[i]) > 0) {
				endPointIndex = i;
			}
		}
		pointOnHullIndex = endPointIndex;
	} while(endPointIndex != convexHullIndices.at(0));

	return convexHullIndices;
}

int main() {
	int readReturn;
	int cases = 0;
	readReturn = scanf("%d", &cases);
	//printf("cases: %i\n", cases);

	// array of all the Points
	int lenPoints;
	for(int i = 0; i < cases; i++) {
		readReturn = scanf("%d", &lenPoints);
		// add the phone pole at 0,0
		lenPoints++;
		Point* allPoints = new Point[lenPoints];
		allPoints[0] = Point(0.0, 0.0);

		//printf("%i points in case %i\n", lenPoints, i+1);
		for(int j=1; j<lenPoints; j++) {
			readReturn = scanf("%lf", &allPoints[j].x);
			readReturn = scanf("%lf", &allPoints[j].y);
		}
		
		// find min x index
		int minXIndex = 0;
		for(int j=1; j<lenPoints; j++) {
			if(allPoints[j].x < allPoints[minXIndex].x) {
				minXIndex = j;
			} else if(allPoints[j].x == allPoints[minXIndex].x) {
				// break ties with y-coordinate
				if(allPoints[j].y < allPoints[minXIndex].y) {
					minXIndex = j;
				}
			}
		}
		// swap min x index with 0 index
		Point temp = allPoints[0];
		allPoints[0] = allPoints[minXIndex];
		allPoints[minXIndex] = temp;
		
		// find the hull
		vector<int> convexHullIndices = giftWrapping(allPoints, lenPoints);		

		int convexHullSize = convexHullIndices.size();
		//printf("Hull size: %i\n", convexHullSize);

		sort(convexHullIndices.begin(), convexHullIndices.end());

		int k = 0;
		for(int j=0; j<lenPoints; j++) {
			if(k < convexHullSize && convexHullIndices.at(k) == j) {
				printf("%.2lf, %.2lf, [%i]\n", allPoints[convexHullIndices.at(k)].x, allPoints[convexHullIndices.at(k)].y, convexHullIndices.at(k)+1);
				k++;
			} else {
				printf("%.2lf, %.2lf, %i\n", allPoints[j].x, allPoints[j].y, j+1);
			}
		}
	}
	return 0;
}
