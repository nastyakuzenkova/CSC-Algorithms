#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>
#include <queue>
#include <stack>

using namespace std;

int main()
{
  #define NAME "number"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int n;
  cin >> n;
  pair<int, int> **result = new pair<int, int>*[n + 1];
  for (int i = 0; i <= n; ++i) {
    result[i] = new pair<int, int>[n + 1];
  }

  bool marked[n + 1][n + 1];
  memset(marked, false, sizeof(marked));
  queue<pair<int, int> > num;
  num.push(make_pair(0, 0));
  while (!marked[0][n] && !num.empty()) {
    pair<int, int> cur = num.front();
    num.pop();
    int curm = cur.first;
    int cursum = cur.second;
    for (int dig = 0; dig < 10; ++dig) {
      int ncurm = (curm * 10 + dig) % n;
      int ncursum = cursum + dig;
      pair<int, int> ncur = make_pair(ncurm, ncursum);
      if (ncursum <= n && !marked[ncurm][ncursum]) {
        result[ncurm][ncursum] = cur;
        num.push(ncur);
        marked[ncurm][ncursum] = true;
      }
    }   
  }

  stack<pair<int, int> > answer;
  int tm = 0;
  int tsum = n;

  while (tm != 0 || tsum != 0) { 
    answer.push(make_pair(tsum, result[tm][tsum].second));
    pair<int, int> cur = result[tm][tsum];
    tm = cur.first;
    tsum = cur.second;
  }

  while (!answer.empty()) {
    pair<int, int> cur = answer.top();
    answer.pop();
    cout << (cur.first - cur.second);
  }
  cout << endl;

  for (int i = 0; i <= n; ++i) {
    delete [] result[i];
  }
  delete []result;
  return 0;
}