// Scott Wiedemann
// 10/06/2010
// tourist.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

using namespace std;


/*

function Dijkstra(Graph, source):
	for each vertex v in Graph:		   // Initializations
		dist[v] := infinity;			  // Unknown distance function from source to v
		previous[v] := undefined;		 // Previous node in optimal path from source
	end for;
	dist[source] := 0;					// Distance from source to source
	Q := the set of all nodes in Graph;
	// All nodes in the graph are unoptimized - thus are in Q
	while Q is not empty:				 // The main loop
		u := vertex in Q with smallest dist[];
		if dist[u] = infinity:
			break;	// all remaining vertices are inaccessible from source
		fi;
		remove u from Q;
		for each neighbor v of u:		 // where v has not yet been removed from Q.
			alt := dist[u] + dist_between(u, v);
			if alt < dist[v]:			 // Relax (u,v,a)
				dist[v] := alt;
				previous[v] := u;
			fi ;
		end for;
	end while;
	return dist[];
end Dijkstra.

*/

class Graph
{
	public:
		int g[100][100];
		int source;
		int dest;
		int pass;

		Graph()
		{
			for(int i=0; i<100; i++)
			{
				for(int j=0; j<100; j++)
				{
					g[i][j]=0;
				}
			}
		}
};

int main()
{
	int scenario=1;
	while(true)
	{
		int nodes=0;
		int edges=0;
		cin >> nodes >> edges;
		if(!nodes)
		{
			break;
		}

		Graph G;

		int n1, n2, p;

		for(int e=0; e<edges; e++)
		{
			cin >> n1 >> n2 >> p;
			G.g[n1-1][n2-1]=p;
		}

		cin >> n1 >> n2 >> G.pass;

		G.source=n1-1;
		G.dest=n2-1;

		for(int k=0; k<nodes; k++)
		{
			for(int i=0; i<nodes; i++)
			{
				for(int j=0; j<nodes; j++)
				{
					G.g[j][i]=G.g[i][j]=max(G.g[i][j], min(G.g[i][k], G.g[k][j]));
				}
			}
		}

		cout << "Scenario #" << scenario << endl;
		cout << "Minimum Number of Trips = " << ceil(double(G.pass)/double(G.g[G.source][G.dest]-1)) << endl << endl;

		scenario++;
	}
	return 0;
} 

