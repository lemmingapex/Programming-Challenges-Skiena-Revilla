#include <iostream>
#include <math.h>

using namespace std;

double a[20][20],d[20][20],tmp;
double val = log(1.01);
int n,j,k,l,tr[20][20],mini,path[20];

int main()
{
	while (cin >> n)
	{
		for (int i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i == j) {
					a[i][i] = 0.0;
				} else {
					cin >> tmp;
					if (tmp == 0.0) {
						a[i][j] = -1e20;
					}
					else {
						a[i][j] = log(tmp);
					}
				}
			}
		}
		mini = n + 1;
		for (k = 0; k < n; k++)
		{
			for (int i = 0; i < n; i++)
			{
				d[0][i] = a[k][i];
				tr[0][i] = k;
			}
			for (int i = 1; i < n; i++)
			{
				if (i >= mini) {
					break;
				}
				for (j = 0; j < n; j++) { 
					d[i][j] = -1e20;
				}
				for (j = 0; j < n; j++) {
					for (l = 0; l < n; l++) {
						if (d[i][j] < d[i-1][l] + a[l][j])
						{
							d[i][j] = d[i-1][l] + a[l][j];
							tr[i][j] = l;
						}
					}
				}
				if (d[i][k] > val) {
					mini = i;
					j = k;
					l = i;
					while (l >= 0)
					{
						path[l + 1] = j;
						j = tr[l][j];
						l--;
					}
					path[0] = k;
					break;
				}
			}
		}
		if (mini == n + 1) {
			cout << "no arbitrage sequence exists" << endl;
		} else {
			for (int i = 0; i <= mini; i++) {
				cout << path[i] + 1 << ' ';
			}
			cout << path[mini + 1] + 1 << endl;
		}
	}
	return 0;
}
