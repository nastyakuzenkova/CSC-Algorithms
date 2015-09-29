#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	#define NAME "ladder"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  int n = 0;
  scanf("%d", &n);
  int ladder[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", &ladder[i]);
  }
  int f[n + 1];
  f[0] = 0;
  f[1] = ladder[0];
  for (int i = 2; i <= n; ++i) {
    f[i] = max(f[i - 1], f[i - 2]) + ladder[i - 1];      
  }
  printf("%d\n", f[n]);
  return 0;
}