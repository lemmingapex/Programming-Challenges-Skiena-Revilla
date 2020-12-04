// Scott Wiedemann
// 10/06/2010
// firestation.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <fstream>
#include <vector>

using namespace std;

class Road
{
	public:
		int intersection1;
		int intersection2;

		int distance;

		Road()
		{ }

		Road(int I1, int I2, int D)
		{
			intersection1=I1;
			intersection2=I2;

			distance=D;
		}
};

class Intersection
{
	public:
		vector<Road> roads;
		int fsDist;

		Intersection()
		{
			fsDist=0;
		}
};

int NIntersections, NFirestations;
int firestations[100];
Intersection intersections[501];
Intersection tempIntersections[501];

void updateFsDistance(int Inter, int distance)
{
	tempIntersections[Inter].fsDist = distance;
	for(int i=0; i < tempIntersections[Inter].roads.size(); i++)
	{
		Road CurrnetInter = tempIntersections[Inter].roads[i];
		if(distance + CurrnetInter.distance < tempIntersections[CurrnetInter.intersection1].fsDist)
		{
			updateFsDistance(CurrnetInter.intersection1,distance + CurrnetInter.distance);
		}
	}
}

int biggestDistance()
{
	int biggest=0;
	for(int i=0; i < NIntersections; i++)
	{
		if (tempIntersections[i].fsDist > biggest)
		{
			biggest = tempIntersections[i].fsDist;
		}
	}
	return biggest;
}

void clearStructs()
{
	for(int i=1; i<NIntersections; i++)
	{
		intersections[i].fsDist = tempIntersections[i].fsDist = 999999;
		intersections[i].roads.clear();
		tempIntersections[i].roads.clear();
	}

	for(int i=1; i<NFirestations; i++)
	{
		firestations[i] = 0;
	}
}


void parseInput()
{
	scanf("%d",&NFirestations);
	scanf("%d",&NIntersections);
	NIntersections += 1;

	clearStructs();

	int fires;
	for(int i=0; i<NFirestations; i++)
	{
		scanf("%d",&fires);
		firestations[i] = fires;
	}
}


void findDistance()
{
	if(NIntersections<3)
	{
		printf("1\n");
		return;
	}

	int firstInter, secondInter, dist;
	char line[1024];
	gets(line);
	while(gets(line) && *line)
	{
		sscanf(line, "%d %d %d", &firstInter, &secondInter, &dist);

		Road Road1=Road(firstInter,secondInter,dist);
		Road Road2=Road(secondInter,firstInter,dist);

		tempIntersections[firstInter].roads.push_back(Road2);
		tempIntersections[secondInter].roads.push_back(Road1);
	}

	for(int i=0; i<NFirestations; i++)
	{
		updateFsDistance(firestations[i], 0);
	}
	
	for(int i=1; i<NIntersections; i++)
	{
		intersections[i] = tempIntersections[i];
	}
	
	int smallestDistance = 99999;
	int smallestInter, tempd;
	for(int i=1; i<NIntersections; i++)
	{
		updateFsDistance(i, 0);
		tempd=biggestDistance();
		if(tempd < smallestDistance)
		{
			smallestDistance = tempd;
			smallestInter = i;
		}

		for(int i=1; i < NIntersections; i++)
		{
			tempIntersections[i] = intersections[i];
		}
	}
        printf("%d\n", smallestInter);
	return;
}

int main(int argc, char **argv)
{
	int NCases;
	scanf("%d",&NCases);
	for(int i=0; i<NCases; i++)
	{
		parseInput();
		findDistance();
		if(i<NCases-1)
		{
			printf("\n");
		}
	}
	return 0;
}
