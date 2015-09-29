#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

bool isAllow(char c)
{
  return c != 'w';
}

int isGrass(char c)
{
  return c == '"';
}

int main()
{
	#define NAME "lepus"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  int n = 0;
  scanf("%d", &n);
  char path[n + 1];
  scanf("%s", path);
  if (!isAllow(path[0])) {
    printf("-1\n");
    return 0;
  }

  int f[n];
  for (int i = 0; i < n; ++i) {
    f[i] = -1;
  }
  f[0] = isGrass(path[0]);

  for (int i = 1; i < n; ++i) {
    if (!isAllow(path[i])) {
      f[i] = -1;
      continue;
    }
    int grass = isGrass(path[i]);
    if (i - 5 >= 0) {
      if (f[i - 5] != -1
        && f[i - 3] != -1
        && f[i - 1] != -1) {
        f[i] = max(f[i - 5], max(f[i - 3], f[i - 1])) + grass;
      }
      else if (f[i - 5] != -1
        && f[i - 3] != -1) {
          f[i] = max(f[i - 5], f[i - 3]) + grass;
      }
      else if (f[i - 5] != -1
        && f[i - 1] != -1) {
          f[i] = max(f[i - 5], f[i - 1]) + grass;
      }
      else if (f[i - 3] != -1
        && f[i - 1] != -1) {
          f[i] = max(f[i - 3], f[i - 1]) + grass;
      }
      else if (f[i - 5] != -1) {
        f[i] = f[i - 5] + grass;
      }
      else if (f[i - 3] != -1) {
        f[i] = f[i - 3] + grass;
      }
      else if (f[i - 1] != -1) {
        f[i] = f[i - 1] + grass;
      }
    }
    else if (i - 3 >= 0) {
      if (f[i - 3] != -1
        && f[i - 1] != -1) {
          f[i] = max(f[i - 3], f[i - 1]) + grass;
      }
      else if (f[i - 3] != -1) {
        f[i] = f[i - 3] + grass;
      }
      else if (f[i - 1] != -1) {
        f[i] = f[i - 1] + grass;
      }            
    }
    else if (i - 1 >= 0) {
      if (f[i - 1] != -1) {
        f[i] = f[i - 1] + grass;
      }          
    }
  }
  n--;
  printf("%d\n", f[n]);
  return 0;
}