#include <deque>
#include <cstdio>

using namespace std;

long n = 0;
long k = 0;
long long mod = (1 << 30);

int main() {
	scanf("%ld %ld", &n, &k);
	deque<long long> numbers;
	for (long i = 0; i < n; ++i) {
		long long x = 0;
		scanf("%lld", &x);
		numbers.push_back(x);
	}
	for (long i = 0; i < k; ++i) {
		long long x = numbers.front();
		long long y = numbers.back();
		if (x < y) {
			numbers.pop_front();
			long long result = x + y;
			if (result >= mod) {
				result %= mod;
			}
			numbers.push_back(result);
		}
		else {
			numbers.pop_back();
			long long result;
			if (y == x) {
				result = y - x;
			}
			else {
				result = y - x + mod;
			}
			numbers.push_front(result);
		}
	}
	while (!numbers.empty()) {
		printf("%lld ", numbers.front());
		numbers.pop_front();
	}
	return 0;
}