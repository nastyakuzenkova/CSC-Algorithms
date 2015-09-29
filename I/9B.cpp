#include <cstdio>
#include <cassert>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{
	#define NAME "calcul"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  int n = 0;
  scanf("%d", &n);
  int f[n + 1];
  int previous[n + 1];
  f[0] = f[1] = 0;

  for (int i = 2; i <= n; ++i) {
    if (i % 2 == 0 && i % 3 == 0) {
      if (f[i / 2] < f[i / 3]) {
        if (f[i / 2] < f[i - 1]) {
          f[i] = f[i / 2] + 1;
          previous[i] = i / 2;
        }
        else {
           f[i] = f[i - 1] + 1;
           previous[i] = i - 1;         
        }
      }
      else {
        if (f[i / 3] < f[i - 1]) {
          f[i] = f[i / 3] + 1;
          previous[i] = i / 3;
        }
        else {
           f[i] = f[i - 1] + 1;
           previous[i] = i - 1;         
        }
      }
    }
    else if (i % 2 == 0) {
        if (f[i / 2] < f[i - 1]) {
          f[i] = f[i / 2] + 1;
          previous[i] = i / 2;
        }
        else {
           f[i] = f[i - 1] + 1;
           previous[i] = i - 1;         
        }
    }
    else if (i % 3 == 0) {
        if (f[i / 3] < f[i - 1]) {
          f[i] = f[i / 3] + 1;
          previous[i] = i / 3;
        }
        else {
           f[i] = f[i - 1] + 1;
           previous[i] = i - 1;         
        }       
    }
    else {
      f[i] = f[i - 1] + 1;
      previous[i] = i - 1; 
    } 
  }
  stack<int> answer;
  int p = n;
  while (p != 1) {
    answer.push(p);
    p = previous[p];
  }
  answer.push(1);
  printf("%d\n", f[n]);
  while (!answer.empty()) {
    printf("%d ", answer.top());
    answer.pop();    
  }
  return 0;
}