#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;
typedef unsigned long long ull;

int const maxN = 50;

ull result[maxN + 1][maxN + 1];

int main()
{
	#define NAME "knight"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	
  	memset(result, 0, sizeof(result));

    int n, m;
    scanf("%d %d", &n, &m);

    result[1][1] = 1;

    for (int i = 2; i <= n; ++i) {
      for (int j = 2; j <= m; ++j) {
        result[i][j] = result[i - 2][j - 1] + result[i - 1][j - 2];
      }
    }

    printf("%lld\n", result[n][m]);
	return 0;
}