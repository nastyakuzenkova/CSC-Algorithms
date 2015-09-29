#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

int const N = 3E6 + 1;
int const M = 150;
int pyramid[M];
int result[N];

void solve(int m)
{
	for (int i = 1; i <= m; ++i) {
		if (result[i] != 0) {
			continue;
		}
		int curMin = N;
		int j = 1;
		while (pyramid[j] <= i) {
			int cur = result[i - pyramid[j]] + 1;
			//printf("cur=%d\n", cur);
			if (cur < curMin) {
				curMin = cur;
			}
			++j;
		}
		result[i] = curMin;
	}
}

int main()
{
	#define NAME "balls"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	int index = 1;
  	int current = 1;
  	int sum = current; 
  	while (sum <= N) {
  		pyramid[index] = sum;
  		index++;
  		current += index;
  		sum += current;
  	}

  	memset(result, 0, sizeof(result));

  	for (int i = 1; i < index; ++i) {
  		result[pyramid[i]] = 1;
  	}

  	int t = 0;
  	scanf("%d", &t);
  	for (int i = 0; i < t; ++i) {
  		int m;
  		scanf("%d", &m);

  		//printf("m=%d\n", m);
  		if (m == 0) {
  			printf("0\n");
  		}
  		else if (result[m] != 0) {
  			printf("%d\n", result[m]);
  		}
  		else {
  			solve(m);
  			printf("%d\n", result[m]); 			
  		}
  	}
	return 0;
}