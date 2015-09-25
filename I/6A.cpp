#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

typedef unsigned long long ull;

template <const int N>
struct HashTable
{
	ull hash[N];
	int value[N];

	int & operator [](ull const &h)
	{
		int index = h % N;
		while (hash[index] && hash[index] != h)	{
			index = (index + 1) % N;
		}
		if (!hash[index]) {
			hash[index] = h;
			value[index] = 0;
		}
		return value[index];		
	}
};

int const size = 1e5 + 1;
char s[size];
ull prime_powers[size];
int x = 0;
HashTable<(int)2e6 + 3> ht;


int main()
{
	prime_powers[0] = 31;
	for (int i = 1; i < size; ++i) {
		prime_powers[i] = prime_powers[i - 1] * 31;
	}
	#define NAME "incrementator"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
    while (scanf("%s%d", s, &x) == 2)
    {
      ull h = 5;
      for (int i = 0; s[i]; ++i) {
        h += (s[i] - 'a' + 1) * prime_powers[i];
      }
      printf("%d\n", ht[h] += x);
    }
	return 0;
}