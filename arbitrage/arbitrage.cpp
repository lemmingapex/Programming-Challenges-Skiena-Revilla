// Scott Wiedemann
// 10/06/2010
// tourist.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

class Node {
	public:
		double dist;
		vector <int> path;

		Node() {
			dist=0.0;
		}

		Node(double Dist) {
			dist=Dist;
		}
};

class Graph
{
	private:
		static const int SIZE = 20;
	
	public:
		Node g[SIZE][SIZE][SIZE];

		Graph() {
			for(int i=0; i<SIZE; i++) {
				for(int j=0; j<SIZE; j++) {
					for(int k=0; k<SIZE; k++) {
						g[i][j][k]=Node();
					}
				}
			}
		}
};

int main()
{
	while(true)
	{
		int nodes=0;
		int edges=0;
		cin >> nodes;
		if(!nodes) {
			break;
		}

		Graph G;

		double rate;

		for(int i=0; i<nodes; i++) {
			for(int j=0; j<nodes; j++) {
				if(i == j) {
					rate =1.0;
				} else {
					cin >> rate;
				}
				for(int k=0; k<nodes; k++) {
					G.g[i][j][k] = Node(rate);
				}
			}
		}

		for(int i=0; i<nodes; i++) {
			for(int j=0; j<nodes; j++) {
				cout << G.g[i][j][0].dist << " ";
			}
			cout << endl;
		}

		double tdistance;
		for(int s=1; s<nodes; s++) {
			for(int i=0; i<nodes; i++) {
				for(int j=0; j<nodes; j++) {
					for(int k=0; k<nodes; k++) {
						tdistance = G.g[i][k][s-1].dist*G.g[k][j][0].dist;
						if(G.g[i][j][s].dist > tdistance) {
							G.g[i][j][s].dist=tdistance;
							G.g[i][j][s].path.push_back(k);
						}
					}
				}
			}
		}

		cout << endl;

		for(int s=0; s<nodes; s++) {
			for(int i=0; i<nodes; i++) {
				//if(G.g[i][i][s].dist > 1.00) {
					cout << G.g[i][i][s].dist << endl;
				//}
			}
		}
		cout << endl << endl;
	}
	cout << "no arbitrage sequence exists" << endl;
	return 0;
} 

