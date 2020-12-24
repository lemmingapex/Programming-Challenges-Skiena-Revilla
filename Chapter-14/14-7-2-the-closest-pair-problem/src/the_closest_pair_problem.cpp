#include <iostream>
#include <math.h>
#include <stdio.h>
#define SIZE 10000

using namespace std;

struct point {
	double x, y;
};

double inline distSq(const point& a, const point& b) {
	return ((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y));
}

double fast_atof(const char *c) {
	double fval =0;
	double tfval = 0;
	double pof10 = 10.0;
	char shift = '0';

	while (*c=='\t' || *c==' ')
		++c;

	fval = 0;
	while ('0' <= *c && *c <= '9') {
		fval *= 10.0;
		tfval = *c - shift;
		fval += tfval;
		++c;
	}

	if (*c == '.') {
		++c;

		while ('0' <= *c && *c <= '9') {
			tfval = (*c - shift)/pof10;
			pof10 *= 10.0;
			fval += tfval;
			++c;
		}
	}

	return fval;
}

double fast_atoi(const char *c) {
	int ival = 0;
	int tival = 0;
	char shift = '0';

	while (*c=='\t' || *c==' ')
		++c;

	ival = 0;
	while ('0' <= *c && *c <= '9') {
		ival *= 10;
		tival = *c - shift;
		ival += tival;
		++c;
	}

	return ival;
}

// array of all the points
point points[SIZE];
int lenPoints;
// current minimum distance
double delta = SIZE;
double temp = SIZE;

void sortPointsX(int L, int R) {
	int i = L, j = R;
	point tmp;
	point pivot = points[(L+R)/2];
	while (i <= j) {
		while (points[i].x < pivot.x) {
			i++;
		}

		while (points[j].x > pivot.x) {
			j--;
		}

		if (i <= j) {
			tmp = points[i];
			points[i] = points[j];
			points[j] = tmp;
			i++;
			j--;
		}
	};

	if (L < j) {
		sortPointsX(L, j);
	}
	if (i < R) {
		sortPointsX(i, R);
	}
}

void solve() {
	if (lenPoints<2)
		return;

	// sort point by x coord
	sortPointsX(0, lenPoints-1);

	double deltaSquared = distSq(points[0], points[1]);
	delta = sqrt(deltaSquared);

	for (int right=1; right<lenPoints; right++) {
		for (int l=right-1; l>=0 && points[l].x > points[right].x-delta; l--) {
			if (points[l].y < points[right].y+delta && points[l].y > points[right].y-delta) {
				temp = distSq(points[right], points[l]);
				if (temp < deltaSquared) {
					deltaSquared = temp;
					delta = sqrt(temp);
				}
			}
		}
	}
}

int main(int argc, const char *argv[]) {
	int length;
	char* buffer;

	// should never seekg on cin! this is unreliable on many operating systems.  This is a big hack to speed things up.  Good thing you use linux, right?
	cin.seekg(0, cin.end);
	length = cin.tellg();
	cin.seekg(0, cin.beg);

	// printf("%i\n", length);

	buffer = new char [length];
	cin.read(buffer, length);

	int j = 0;
	lenPoints = atoi(&buffer[j++]);
	while (lenPoints != 0) {
		delta = SIZE;
		for(int i=0; i<lenPoints; ++i) {
			while(buffer[j] != '\n')
				++j;
			++j;
			points[i].x = fast_atof((char*) &buffer[j]);
			// printf("%f  ", points[i].x);
			while(buffer[j] != ' ')
				++j;
			++j;
			points[i].y = fast_atof((char*) &buffer[j]);
			// printf("%f\n", points[i].y);
		}
		while(buffer[j] != '\n')
			++j;
		++j;

		solve();

		if (delta >= SIZE) {
			printf("%s", "INFINITY\n");
		} else {
			printf("%.4lf\n", delta);
		}
		lenPoints = atoi(&buffer[j++]);
	}
	return 0;
}
