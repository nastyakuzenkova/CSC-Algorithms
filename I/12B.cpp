#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

typedef unsigned long long ull;

struct Snowman
{
	int prev;
	int m;
	ull sum;
};

int const maxN = 2E6;

Snowman s[maxN + 1];

void pop(int i, int t)
{
	int copy = s[t].prev;
	s[i].prev = s[copy].prev;
	s[i].m = s[copy].m;
	s[i].sum = s[copy].sum;
}

void push(int i, int t, int m)
{
	s[i].prev = t;
	s[i].m = m;
	s[i].sum = s[t].sum + m;
}

int main()
{
  	#define NAME "snowmen"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));

	s[0].prev = 0;
	s[0].m = 0;
	s[0].sum = 0;

  	int n;
  	scanf("%d", &n);
  	for (int i = 0; i < n; ++i) {
  		int t, m;
  		scanf("%d%d", &t, &m);
  		if (m == 0) {
  			pop(i + 1, t);
  		}
  		else {
  			push(i + 1, t, m);
  		}
  	}

  	ull res = 0;

  	for (int i = 1; i <= n; ++i)
  	{
  		res += s[i].sum;
  	}

  	printf("%lld\n", res);
  	return 0;
}