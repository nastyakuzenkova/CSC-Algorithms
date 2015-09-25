#include <cstdio>

typedef unsigned int ui;
typedef	unsigned long long ull;

ui m, q, a, b;
ui n = 16777216;
ull mod = 4294967296;
ull c[16777216];

ui cur = 0;
ui nextRand() {
	cur = cur * a + b;
	return cur >> 8;
}

int main() {
	scanf("%d %d %d %d", &m, &q, &a, &b);
	for (ui i = 0; i < n; ++i) {
		c[i] = 0;
	}
	for (ui i = 0; i < m; ++i) {
		ui add = nextRand();
		ui l = nextRand();
		ui r = nextRand();
		if (l > r) {
			ui temp = l;
			l = r;
			r = temp;
		}
		if (c[l] > mod) {
			c[l] %= mod;
		}
		c[l] = (c[l] + add) % mod;
		r++;
		if (r < n) {
			if (c[r] > mod) {
				c[r] %= mod;
			}
			c[r] = (c[r] + mod - add) % mod;
		}
	}
	for (ui i = 1; i < n; ++i) {
		c[i - 1] %= mod;
		c[i] += c[i - 1];
	}
	for (ui i = 1; i < n; ++i) {
		c[i - 1] %= mod;
		c[i] += c[i - 1];
	}
 	ull sum = 0;
	for (ui i = 0; i < q; ++i) {
		ui l = nextRand();
		ui r = nextRand();
		if (l > r) {
			ui temp = l;
			l = r;
			r = temp;
		}
		if (sum > mod) {
			sum %= mod;
		}
		if (l <= 0) {
			sum = (sum + c[r]) % mod;
		}
		else {
			sum = (sum + (c[r] - c[l - 1])) % mod;
		}
	}
	printf("%lld\n", (sum % mod));
	return 0;
}