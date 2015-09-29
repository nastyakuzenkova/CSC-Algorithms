#include <cstdio>
#include <cassert>
#include <climits>
#include <algorithm>

using namespace std;

int const N = 100;
int dist[N][N];
int diam = 0;
int r = INT_MAX;
int infty = 1001;

int main()
{
	#define NAME "diameter"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			scanf("%d", &x);
			if (x == -1) {
				dist[i][j] = infty;
			}
			else {
				dist[i][j] = x;
			}
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);					
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		int curR = 0;
		for (int j = 0; j < n; ++j) {
			if (dist[i][j] > diam) {
				diam = dist[i][j];
			}
			if (dist[i][j] > curR) {
				curR = dist[i][j];
			}
		}
		if (curR < r) {
			r = curR;
		}
	}
	printf("%d\n%d\n", diam, r);
}