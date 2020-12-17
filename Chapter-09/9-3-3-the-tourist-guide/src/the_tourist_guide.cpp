#include <iostream>
#include <math.h>

using namespace std;

class Graph {
	public:
		int g[100][100];
		int source;
		int dest;
		int pass;

		Graph() {
			for (int i=0; i<100; i++) {
				for (int j=0; j<100; j++) {
					g[i][j] = 0;
				}
			}
		}
};

int main(int argc, const char *argv[]) {
	for (int scenario = 1; ; scenario++) {
		int numberOfNodes = 0;
		int numberOfEdges = 0;
		cin >> numberOfNodes >> numberOfEdges;
		if (numberOfNodes == 0) {
			break;
		}

		Graph* graph = new Graph();

		int n1, n2, p;

		for (int e = 0; e < numberOfEdges; e++) {
			cin >> n1 >> n2 >> p;
			graph -> g[n1 - 1][n2 - 1] = p;
		}

		cin >> n1 >> n2 >> graph->pass;

		graph->source = n1-1;
		graph->dest = n2-1;

		for (int k = 0; k < numberOfNodes; k++) {
			for (int i = 0; i < numberOfNodes; i++) {
				for (int j = 0; j < numberOfNodes; j++) {
					graph->g[j][i] = graph->g[i][j] = max(graph->g[i][j], min(graph->g[i][k], graph->g[k][j]));
				}
			}
		}

		cout << "Scenario #" << scenario << endl;
		const int numberOfTrips = ceil(double(graph->pass) / double(graph->g[graph->source][graph->dest]-1));
		cout << "Minimum Number of Trips = " << numberOfTrips << endl << endl;
	}
	return 0;
}
