// Scott Wiedemann
// 09/01/2010 - 09/07/2010
// cpp.cpp
// Closest Pairs Problem
// CSCI562-A Applied Algorithms and Data Structures

#include <math.h>
#include <stdio.h>
#define SIZE 10000

using namespace std;

struct point
{
	double x,y;
};

double distSq(const point& a, const point& b)
{
	return ((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y));
}


// array of all the points
point points[SIZE];
int lenPoints, right, l;
// current minimum distance
double delta = SIZE;
double temp = SIZE;

void sortPointsX(int L, int R)
{
	int i = L, j = R;
	point tmp;
	point pivot = points[(L+R)/2];
	while(i <= j)
	{
		while(points[i].x < pivot.x)
		{
			i++;
		}

		while(points[j].x > pivot.x)
		{
			j--;
		}

		if(i <= j)
		{
			tmp = points[i];
			points[i] = points[j];
			points[j] = tmp;
			i++;
			j--;
		}
	};

	if(L < j)
	{
		sortPointsX(L, j);
	}
	if(i < R)
	{
		sortPointsX(i, R);
	}
}

void solve()
{
	if(lenPoints<2)
		return;

	// sort point by x coord
	sortPointsX(0,lenPoints-1);

	// inital setup
	delta=sqrt(distSq(points[0],points[1]));

	for(right=1; right<lenPoints; right++)
	{
		for(l=right-1; l>=0 && points[l].x>points[right].x-delta; l--)
		{
			if(points[l].y<points[right].y+delta && points[l].y>points[right].y-delta)
			{
				temp=distSq(points[right],points[l]);
				if(temp<delta*delta)
				{
					delta=sqrt(temp);
				}
			}
		}
	}
}

int main()
{
	int i;
	while(true)
	{
		delta = SIZE;
		scanf("%d", &lenPoints);
		if(!lenPoints)
			break;

		for(i=0; i<lenPoints; i++)
		{
			scanf("%lf", &points[i].x);
			scanf("%lf", &points[i].y);
		}
		solve();

		if(delta>=SIZE)
		{
			printf("%s","INFINITY\n");
		}
		else
		{
			printf("%.4lf\n",delta);
		}
	}
	return 0;
}
