// Scott Wiedemann
// 10/06/2010
// tugofwar.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int weight[101];

void quicksort(int L, int R)
{
	int i = L, j = R;
	int tmp;
	int pivot = weight[(L+R)/2];
	while(i <= j)
	{
		while(weight[i] < pivot)
		{
			i++;
		}

		while(weight[j] > pivot)
		{
			j--;
		}

		if(i <= j)
		{
			tmp = weight[i];
			weight[i] = weight[j];
			weight[j] = tmp;
			i++;
			j--;
		}
	};

	if(L < j)
	{
		quicksort(L, j);
	}
	if(i < R)
	{
		quicksort(i, R);
	}
}

int main()
{
	int cases=0;
	scanf("%d", &cases);

	int sum;
	int n;

	for(int c=0; c<cases; c++)
	{
		scanf("%d", &n);
		sum=0;
		for(int i=0; i<n; i++)
		{
			scanf("%d", &weight[i]);
			sum += weight[i];
		}
		quicksort(0, n-1);
		int tx=(n/2)+2;
		int ty=(sum/2)+1;
		bool t[tx][ty];
		int exist[tx][sum];

		// set array to false
		for(int i=0; i<tx; i++)
		{
			for(int j=0; j<ty; j++)
			{
				t[i][j]=false;
			}
			exist[i][0] = 0;
		}

		exist[0][0] = 1;
		exist[0][1] = 0;
		t[0][0] = true;

		for(int i=0; i<n; i++)
		{
			for(int j=i; j>=0; j--)
			{
				if(j>n/2)
				{
					j=(n/2);
				}

				if(i>tx && (n/2)-j>n-i)
				{
					break;
				}

				int k;

				for(int e=exist[j][0]; e>0; e--)
				{
					k=exist[j][e];

					if(k+weight[i]>=ty)
					{
						continue;
					}

					if(t[j][k]==true)
					{
						if(t[j+1][k+weight[i]]==false)
						{
							// update subsum existance
							t[j+1][k+weight[i]]=true;
							exist[j+1][0]++;
							exist[j+1][exist[j+1][0]]=k+weight[i];
						}
					}
				}
			}
		}

		int m = 0;

		// retrieve the answer
		// is n even or odd?
		if(n%2==1)
		{
			for(int k=sum/2; k>=0; k--)
			{
				if(t[(n/2)+1][k]==true)
				{
					m=k;
					break;
				}
			}
		}
		else
		{
			for(int k=sum/2; k>=0; k--)
			{
				if(t[(n/2)][k]==true)
				{
					m=k;
					break;
				}
			}
		}

		printf("%d %d\n",m,sum-m);

		if(c<cases-1)
		{
			printf("\n");
			//cout << endl;
		}
	}
	return 0;
} 

