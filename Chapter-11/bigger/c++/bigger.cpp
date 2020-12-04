// Scott Wiedemann
// 10/06/2010
// tourist.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Elephant
{
	public:
		int id;
		int size;
		int iq;
	
		Elephant()
		{
			size=0;
			iq=0;
		}

		Elephant(int SIZE, int IQ, int ID)
		{
			size=SIZE;
			iq=IQ;
			id=ID;
		}
};

vector<Elephant> elephants;
vector<int> elephantids;

void Print()
{
	printf("%d\n", (int)elephantids.size());

	for(int i=elephantids.size()-1; i>=0; i--)
	{
		printf("%d\n", elephants[elephantids[i]].id);
	}
}

bool ElephantIq(Elephant e1, Elephant e2)
{
	if(e1.iq==e2.iq && e1.size==e2.size)
	{
		return (e1.id>e2.id);
	}
	else if(e1.size==e2.size)
	{
		return (e1.iq>e2.iq);
	}
	else
	{
		return (e1.size>e2.size);
	}
}

void lcs(vector<Elephant> &a, vector<int> &b)
{
	vector<int> p(a.size());
	int u, v;
 
	if (a.empty()) return;
 
	b.push_back(0);
 
	for(int i = 1; i < a.size(); i++)
	{
		if(a[b.back()].iq < a[i].iq)
		{
			p[i] = b.back();
			b.push_back(i);
			continue;
		}
 
		for (u = 0, v = b.size()-1; u < v;)
		{
			int c = (u + v) / 2;
			if (a[b[c]].iq < a[i].iq)
			{
				u=c+1;
			}
			else
			{
				v=c;
			}
		}
 
		if (a[i].iq < a[b[u]].iq)
		{
			if(u > 0)
			{
				p[i] = b[u-1];
			}
			b[u] = i;
		}	
	}
 
	for (u = b.size(), v = b.back(); u--; v = p[v])
	{
		b[u] = v;
	}
}

int main()
{
	int SIZE;
	int IQ;
	int ID=1;
	char line[1024];
	gets(line);
	while(gets(line) && *line)
	{
		ID++;
		sscanf(line, "%d %d", &SIZE, &IQ);
		elephants.push_back(Elephant(SIZE,IQ,ID));
	}

	sort(elephants.begin(), elephants.end(),ElephantIq);

	lcs(elephants,elephantids);

	Print();

	return 0;
}
