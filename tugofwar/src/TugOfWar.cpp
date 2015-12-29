// Scott Wiedemann
// 10/06/2010
// TugOfWar.cpp

#include <stdio.h>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

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
		// array of hash sets
		unordered_set<int> *subsumCache = new unordered_set<int>[H];
		for(int i = 0; i < H; i++) {
			unordered_set<int> temp;
			subsumCache[i] = temp;
		}

		// 0 people, weight a total of 0.
		subsumCache[0].insert(0);

		for(int i = 0; i < N; i++) {
			// get a persons weight
			int iWeight = weights[i];
			for(int j = i; j >= 0; j--) {
				unordered_set<int>::iterator it;
				for (it = subsumCache[j].begin(); it != subsumCache[j].end(); it++) {
					int cachedWeight = *it;
					int tWeight = iWeight + cachedWeight;

					if(tWeight > W) {
						continue;
					}

					// this is an optimization to break early, becauase we don't need to fill out the entire table!
					if(i > centerPerson + 1 && (N/2) - j > N - i) {
						break;
					}

					if(subsumCache[j].count(cachedWeight)) {
						if(!subsumCache[j+1].count(tWeight)) {
							subsumCache[j+1].insert(tWeight);

							// printf("subsumCache:\n");
							// unordered_set<int>::iterator iit;
							// for (int ii = 0; ii < H; ++ii) {
							// 	for (iit = subsumCache[ii].begin(); iit != subsumCache[ii].end(); iit++) {
							// 		printf("%d ", *iit);
							// 	}
							// 	printf("\n");
							// }
							// printf("\n");
						}
					}
				}
			}
		}

		int team1Weight;
		int team2Weight;
		int weightDiff = INF;

		// get the answer
		unordered_set<int>::iterator it;
		for (it = subsumCache[centerPerson].begin(); it != subsumCache[centerPerson].end(); it++) {
			int weight1 = *it;
			int weight2 = totalWeight - weight1;
			int tWeightDiff = abs(weight1 - weight2);
			if(tWeightDiff < weightDiff) {
				weightDiff = tWeightDiff;
				team1Weight = min(weight1, weight2);
				team2Weight = max(weight1, weight2);
			}
		}

		printf("%d %d\n", team1Weight, team2Weight);

		if(c < NCases - 1) {
			printf("\n");
		}

		delete [] subsumCache;
	}
	return 0;
}
