#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

int const notSet = 1E9;

bool isAny(char c)
{
  return c == '?';
}

bool isAll(char c)
{
  return c == '*';
}

bool isSymbol(char c)
{
  return !isAny(c) && !isAll(c);
}

int main()
{
  #define NAME "patterns"
    assert(freopen(NAME ".in", "r", stdin));
    assert(freopen(NAME ".out", "w", stdout));

    string s1, s2;
    cin >> s1 >> s2;
    if (s1.empty() && s2.empty()) {
      cout << "YES" << endl;
      return 0;
    }

    if (s2.empty() && !s1.empty() && s1 == "*") {
      cout << "YES" << endl;
      return 0;
    }

    if (s1.empty() || s2.empty()) {
      cout << "NO" << endl;
      return 0;
    }

    int n = s1.size();
    int m = s2.size();

    bool result[m + 1];
    bool previous[m + 1];

    for (int i = 0; i <= m; ++i)
    {
      previous[i] = false;
      result[i] = false;
    }

    previous[0] = true;

    int firstTrueIndex = 0;
    bool prev = true;

    for (int i = 1; i <= n; ++i) {
      int curIndex = notSet;
      bool ok = false;
      for (int j = 0; j <= m; ++j) {
        if (j < firstTrueIndex) {
          result[j] = false;
          continue;
        }

        if (j == 0) {
          result[j] = prev && isAll(s1[i - 1]);
          if (result[j]) {
            curIndex = 0;
          }
          continue;          
        }

        char cur1 = s1[i - 1];
        char cur2 = s2[j - 1];
        
        if (isSymbol(cur1)) {
          if (cur1 == cur2) {
            result[j] = previous[j - 1];
          }
          else {
            result[j] = false;
          }
        }
        else if (isAny(cur1)) {
          result[j] = previous[j - 1];          
        }
        else if (isAll(cur1)) {
          result[j] = prev;
        }
        if (result[j] && (curIndex == notSet)) {
          //cout << j << endl;
          curIndex = j;
        }
        ok |= result[j];       
      }
      firstTrueIndex = curIndex;
      prev = ok;
      for (int k = 0; k <= m; ++k)
      {
        //cout << previous[k] << " ";
        previous[k] = result[k];
        result[k] = false;
      }
      //cout << endl;       
    }

    if (previous[m]) {
      cout << "YES" << endl;
    } 
    else {
      cout << "NO" << endl;
    }     
  return 0;
}