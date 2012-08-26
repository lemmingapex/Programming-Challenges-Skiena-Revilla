// Scott Wiedemann
// 04/29/2012
// hearding.cpp

#include <math.h>
#include <stdio.h>
#include <vector>
#define SIZE 10000

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

// array of all the Points
Point allPoints[SIZE];
int lenPoints, right, l;

// modified quicksort based on sin of the angle
// faster to use cos, rather than the angle.
// can use cos(x) because it is monotonically decreasing function with respect to x
void sortPointsSin(int L, int R)
{
	int i = L, j = R;
	Point tmp;
	Point pivot = allPoints[(L+R)/2];
	while(i <= j)
	{
		while((allPoints[i].x - allPoints[0].x)/allPoints[i].dist(allPoints[0]) > (pivot.x - allPoints[0].x)/pivot.dist(allPoints[0]))
		{
			i++;
		}

		while((allPoints[j].x - allPoints[0].x)/allPoints[j].dist(allPoints[0]) < (pivot.x - allPoints[0].x)/pivot.dist(allPoints[0]))
		{
			j--;
		}

		if(i <= j)
		{
			tmp = allPoints[i];
			allPoints[i] = allPoints[j];
			allPoints[j] = tmp;
			i++;
			j--;
		}
	};

	if(L < j)
	{
		sortPointsSin(L, j);
	}
	if(i < R)
	{
		sortPointsSin(i, R);
	}
}


//is point 3 a left turn or right turn with respect to point 1 and 2?
double ccw(Point p1, Point p2, Point p3) {
	return (p1 - p2).cross(p3 - p2);
}

vector<int> findConvexHull() {
	vector<int> convexHullIndices;
	convexHullIndices.push_back(0);
	convexHullIndices.push_back(1);

	// number of points on the convex hull
	int i = 2;



	for (i=2; i < lenPoints; i++) {
		bool done_removing = false;
		while (!done_removing) {
			point &a = *(hull.end()-2), &b = *(hull.end()-1);
			done_removing = turn_direction(a,b,*i) &gt;= 0;
			if (!done_removing) {
				hull.pop_back();
			} else {
				hull.push_back(*i);
			}
		}
	}

















/*
	for(int j=2; j<lenPoints; j++) {
		// while left turns or co-linear?
		//printf("%f", ccw(allPoints[convexHullIndices.at(i-2)], allPoints[convexHullIndices.at(i-1)], allPoints[j]));
		while(ccw(allPoints[convexHullIndices.at(i-2)], allPoints[convexHullIndices.at(i-1)], allPoints[j]) <= 0 && j<lenPoints) {
			if(ccw(allPoints[convexHullIndices.at(i-2)], allPoints[convexHullIndices.at(i-1)], allPoints[j]) == 0 && j<lenPoints) {
				printf("co-linear\n");
				double d1 = allPoints[convexHullIndices.at(i-2)].dist(allPoints[convexHullIndices.at(i-1)]);
				double d2 = allPoints[convexHullIndices.at(i-2)].dist(allPoints[j]);
				//printf("%f", d1);
				//printf("%f", d2);
				if(d1 > d2) {
					int t = convexHullIndices.at(i-1);
					convexHullIndices.pop_back();
					convexHullIndices.push_back(j);
					convexHullIndices.push_back(t);
				} else {
					convexHullIndices.push_back(j);
				}
			} else {
				printf("left\n");
				convexHullIndices.push_back(j);
			}
			i++;
			j++;
		}
		// if it's a right turn
		if(ccw(allPoints[convexHullIndices.at(i-2)], allPoints[convexHullIndices.at(i-1)], allPoints[j]) > 0) {
			printf("right\n");
			// remove points until it's a left turn
			while(ccw(allPoints[convexHullIndices.at(i-2)], allPoints[convexHullIndices.at(i-1)], allPoints[j]) > 0) {
				//printf("pop\n");
				convexHullIndices.pop_back();
				i--;
			}
			// add the new point;
			//printf("push\n");
			convexHullIndices.push_back(j);
			i++;
		}
	}*/
	return convexHullIndices;
}

int main() {
	int readReturn;
	int i = 0;
	readReturn = scanf("%d", &lenPoints);
	while(lenPoints > 0) {
		if(i>0) {
			printf("\n");
		}
		i++;
		//printf("number of Points: %i\n", lenPoints);
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

		// sort the Points
		sortPointsSin(1, lenPoints - 1);

		for(int j=0; j<lenPoints; j++) {
			printf("%.2lf, %.2lf, %i\n", allPoints[j].x, allPoints[j].y, j+1);
		}

		// find the hull
		vector<int> convexHullIndices = findConvexHull();

		printf("%s%i\n", "Convex hull size:",convexHullIndices.size());

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
