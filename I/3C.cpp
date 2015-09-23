#include <cstdio>
#include <algorithm>

using namespace std;

int n = 0;
int k = 0;
long a[10001];

bool canCut(const long &currentLength) {
	long count = 0;
	for (int i = 0; i < n; ++i) {
		count += a[i] / currentLength;
	}
	return (count >= (long)k);
}

long max_length(const long &bound) {
	if (canCut(bound)) {
		return bound;
	}
	long l = 1;
	long r = bound;
	while (l < r) {
		long mid = l + (r - l) / 2;
		if (canCut(mid)) {
			l = mid + 1;
		}
		else {
			r = mid;
		}		
	}
	return l - 1;
}

int main()
{
	scanf("%d %d", &n, &k);
	long sum = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%ld", &a[i]);
		//a[i] = 10000000;
		sum += a[i];
	}	
	long max_possible_length = sum / k;
	if (max_possible_length < 1) {
		printf("%d\n", 0);
		return 0;
	}
	sort(a, a + n);
	printf("%ld\n", max_length(max_possible_length));
	return 0;
}