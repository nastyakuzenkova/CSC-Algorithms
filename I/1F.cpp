#include <stdio.h>
#include <climits>

int main() {
	long n = 1000000000000;
	scanf("%ld", &n);
	long minSum = LONG_MAX;
	long min_a = 0;
	long min_b = 0;
	long min_c = 0;
	for (long a = 1; a * a * a <= n; ++a) {
		if (n % a == 0) {
			long b_bound = n / a;
			for (long b = a;  b * b <= b_bound; ++b) {
				long c = n / a / b;
				if (a * b * c == n) {
					long currentSum = 2 * (a * b + b * c + c * a);
					if (currentSum < minSum) {
						minSum = currentSum;
						min_a = a;
						min_b = b;
						min_c = c;
					}
				}
			}
		}
	}
	printf("%ld %ld %ld %ld\n", minSum, min_a, min_b, min_c);
	return 0;
}