#include <cstdio>
#include <algorithm>

using namespace std;

class Elephant {
	public:
		int index;
		int size;
		int iq;

		Elephant() {
		}

		Elephant(int _index, int _size, int _iq) {
			index = _index;
			size = _size;
			iq = _iq;
		}

		bool operator < (Elephant o) const {
			if (size != o.size) {
				return size < o.size;
			}
			return iq > o.iq;
		}
};

int main(int argc, const char *argv[]) {
	Elephant elephants[1000];

	int n=0;
	int size, iq;
	while (scanf("%d %d", &size, &iq) == 2) {
		elephants[n] = Elephant(++n, size, iq);
	}
	sort(elephants, elephants + n);

	int dp[n],next[n],ans=0,start;

	for (int i = n-1; i >= 0; i--) {
		dp[i] = 1;
		next[i] = -1;

		for (int j = i+1; j < n; j++){
			if (elephants[i].size < elephants[j].size && elephants[i].iq > elephants[j].iq && 1 + dp[j] > dp[i]){
				dp[i] = 1 + dp[j];
				next[i] = j;
			}
		}

		if (dp[i] > ans){
			ans = dp[i];
			start = i;
		}
	}

	printf("%d\n",ans);
	for (int i=start; i!=-1; i=next[i]) {
		printf("%d\n", elephants[i].index);
	}

	return 0;
}
