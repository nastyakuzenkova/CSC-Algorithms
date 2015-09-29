#include <cstdio>
#include <cassert>

using namespace std;
typedef unsigned long long ull;

int main()
{
	#define NAME "fiblong"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	int n = 0;
  	scanf("%d", &n);
  	if (n <= 1) {
  		printf("1\n");
  	}
  	else {
  		ull f[n + 1];
  		f[0] = f[1] = 1;
  		for (int i = 2; i <= n; ++i) {
  			f[i] = f[i - 1] + f[i - 2]; 
  		}
  		printf("%lld\n", f[n]);
  	}
	return 0;
}