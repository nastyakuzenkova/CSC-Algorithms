#include <cstdio>
#include <cassert>

using namespace std;

int main()
{
	#define NAME "e2m"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	int a[n][n];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a[i][j] = 0;
		}
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		a[from][to] = a[to][from] = 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}