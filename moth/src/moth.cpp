// Scott Wiedemann
// 02/16/2014
// moth.cpp

#include <math.h>
#include <stdio.h>
#include <vector>

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
	int i = 0;
	int lenPoints = 0;
	readReturn = scanf("%d", &lenPoints);
	while(lenPoints > 0) {
		if(i>0) {
			printf("\n");
		}
		i++;
		Point* allPoints = new Point[lenPoints];
		//printf("%i points in case %i\n", lenPoints, i+1);
		for(int j=0; j<lenPoints; j++) {
			readReturn = scanf("%lf", &allPoints[j].x);
			readReturn = scanf("%lf", &allPoints[j].y);
		}

		// find min y index
		int minYIndex = 0;
		for(int j=0; j<lenPoints; j++) {
			if(allPoints[j].y < allPoints[minYIndex].y) {
				minYIndex = j;
			} else if(allPoints[j].y == allPoints[minYIndex].y) {
				// break ties with x-coordinate
				if(allPoints[j].x < allPoints[minYIndex].x) {
					minYIndex = j;
				}
			}
		}
		// swap min y index with 0 index
		Point temp = allPoints[0];
		allPoints[0] = allPoints[minYIndex];
		allPoints[minYIndex] = temp;

		// find the hull
		vector<int> convexHullIndices = giftWrapping(allPoints, lenPoints);	

		//printf("%s%i\n", "Convex hull size:",convexHullIndices.size());

		int chSize = convexHullIndices.size() -1;
		printf("%s%i%s","Region #",i,":\n");
		double perimeterLength = 0.0;
		printf("(%.1lf,%.1lf)%s", allPoints[convexHullIndices.at(0)].x, allPoints[convexHullIndices.at(0)].y, "-");
		int j=1;
		for(j=chSize; j>0; --j) {
			printf("(%.1lf,%.1lf)%s", allPoints[convexHullIndices.at(j)].x, allPoints[convexHullIndices.at(j)].y, "-");
			perimeterLength += allPoints[convexHullIndices.at(j)].dist(allPoints[convexHullIndices.at(j-1)]);
		}
		perimeterLength += allPoints[convexHullIndices.at(chSize)].dist(allPoints[convexHullIndices.at(0)]);
		printf("(%.1lf,%.1lf)\n", allPoints[convexHullIndices.at(0)].x, allPoints[convexHullIndices.at(0)].y);
		printf("Perimeter length = %.2lf\n", perimeterLength);

		readReturn = scanf("%d", &lenPoints);
	}
	return 0;
}
