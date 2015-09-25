#include <cstdio>

typedef long long ll;

ll n;
ll m;
ll a_temp;
ll asum[(ll)10000000];
ll b[(ll)20000000];
ll amod = (ll)(65536);
ll bmod = (ll)(1073741824);


int main() {
	ll x, y, a0;
	scanf("%lld %lld %lld %lld", &n, &x, &y, &a0);
	ll sum;
	a_temp = a0 % amod;
	asum[0] = sum = a_temp;
	for (ll i = 1; i < n; ++i) {
		a_temp = (x * a_temp + y) % amod;
		sum += a_temp;
		asum[i] = sum;
	}
	ll z, t, b0;
	scanf("%lld %lld %lld %lld", &m, &z, &t, &b0);
	b[0] = b0 % bmod;
	m *= 2;
	for (ll i = 1; i < m; ++i) {
		ll temp = (z * b[i - 1] + t);
		while (temp < 0) {
			temp += bmod;
		}
		b[i] = temp % bmod;
	}

	ll result = 0;
	for (int i = 0; i < m; i+=2) {
		ll c1 = b[i] % n;
		ll c2 = b[i + 1] % n;
		if (c1 > c2) {
			ll temp = c1;
			c1 = c2;
			c2 = temp;
		}
		if (c1 <= 0) {
			result += asum[c2];
		}
		else {
			result += asum[c2] - asum[c1 - 1];
		}
	}
	printf("%lld\n", result);
	return 0;
}