// Scott Wiedemann
// 10/06/2010
// TugOfWar.cpp

#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 450*100;

// holds the weights of at-most 100 people for each case
int weights[100];

int main() {
	int NCases;
	scanf("%d", &NCases);

	for(int c = 0; c < NCases; c++) {
		// number of people in this tug-of-war
		int N;
		scanf("%d", &N);

		// integer division, round up
		int centerPerson = (N + 1) / 2;

		// total weight of all the people in this tug-of-war
		int totalWeight = 0;
		for(int i = 0; i < N; i++) {
			scanf("%d", &weights[i]);
			totalWeight += weights[i];
		}

		int H = N + 1;
		int W = totalWeight + 1;

		bool subsumExist[H][W];
		int subsumCache[H][15000];

		// set array to false
		for(int i=0; i<H; i++) {
			for(int j=0; j<W; j++) {
				subsumExist[i][j] = false;
			}
			for(int j=0; j<15000; j++) {
				subsumCache[i][j] = 0;
			}
		}

		subsumCache[0][0] = 1;
		// 0 people, weight a total of 0.
		subsumCache[0][1] = 0;
		subsumExist[0][0] = true;

		for(int i = 0; i < N; i++) {
			// get a persons weight
			int iWeight = weights[i];
			for(int j = i; j >= 0; j--) {

				if(j>N/2) {
					j=(N/2);
				}

				// this is an optimization to break early, becauase we don't need to fill out the entire table!
				if(i > centerPerson && (N/2) - j > N - i) {
					break;
				}

				for(int indexAtJ=subsumCache[j][0]; indexAtJ>0; indexAtJ--) {
					int cachedWeight = subsumCache[j][indexAtJ];
					int tWeight = iWeight + cachedWeight;

					if(tWeight > W) {
						continue;
					}

					if(subsumExist[j][cachedWeight] == true) {
						if(subsumExist[j+1][tWeight] == false) {

							subsumExist[j+1][tWeight]=true;
							subsumCache[j+1][0]++;
							subsumCache[j+1][subsumCache[j+1][0]]=tWeight;

							// printf("subsumCache:\n");
							//
							// for (int ii = 0; ii < H; ++ii) {
							// 	for (int jj = subsumCache[ii][0]; jj > 0; jj--) {
							// 		printf("%d ", subsumCache[ii][jj]);
							// 	}
							// 	printf("\n");
							// }
							// printf("\n");
						}
					}
				}
			}
		}

		int team1Weight = 0;
		int weightDiff = INF;

		// get the answer
		for (int i = subsumCache[centerPerson][0]; i>0; i--) {
			int weight1 = subsumCache[centerPerson][i];
			if(subsumExist[centerPerson][weight1]) {
				int weight2 = totalWeight - weight1;
				int tWeightDiff = abs(weight1 - weight2);
				if(tWeightDiff < weightDiff) {
					weightDiff = tWeightDiff;
					team1Weight = min(weight1, weight2);
				}
			}
		}

		printf("%d %d\n", team1Weight, totalWeight - team1Weight);

		if(c < NCases - 1) {
			printf("\n");
		}

	}
	return 0;
}
