#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	#define NAME "lcs"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  int n = 0;
  scanf("%d", &n);
  int s1[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", &s1[i]);
  }

  int m = 0;
  scanf("%d", &m);
  int s2[m];
  for (int i = 0; i < m; ++i) {
    scanf("%d", &s2[i]);
  }

  int f[n + 1][m + 1];
  for (int i = 0; i <= n; ++i) {
    f[i][m] = 0;
  }
  for (int i = 0; i <= m; ++i) {
    f[n][i] = 0;
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      f[i][j] = (s1[i] == s2[j]) 
      ? (f[i + 1][j + 1] + 1)
      : (max(f[i + 1][j], f[i][j + 1]));
    }
  }
  printf("%d\n", f[0][0]);
  return 0;
}