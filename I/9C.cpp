#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	#define NAME "field"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  int m = 0;
  int n = 0;
  scanf("%d %d", &m, &n);
  int field[m][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &field[j][i]);
    }
  }
  int f[m][n];
  f[0][0] = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == 0 && j == 0) {
        continue;
      }
      if (i - 1 >= 0 && j - 1 >= 0) {
        int a = f[i][j - 1] + abs(field[i][j - 1] - field[i][j]);
        int b = f[i - 1][j] + abs(field[i - 1][j] - field[i][j]);
        f[i][j] = min(a, b);
      }
      else if (i - 1 >= 0) {
        f[i][j] = f[i - 1][j] + abs(field[i - 1][j] - field[i][j]);
      }
      else if (j - 1 >= 0) {
        f[i][j] = f[i][j - 1] + abs(field[i][j - 1] - field[i][j]);      
      }
      //printf("%d %d: %d\n", i, j, f[i][j]);
    }
    //printf("\n");
  }
  n--;
  m--;
  printf("%d\n", f[m][n]);
  return 0;
}