#include <iostream>
#include <map>

using namespace std;

typedef unsigned long ul;

ul mod = 4294967296;

map<ul, ul> f;

ul f_rec(ul n) {
	if (f.find(n) != f.end()) {
		if (f[n] > mod) {
			f[n] -= mod;
		}
		return f[n];
	}

	if (n % 2 == 0) {
		return f[n] = f_rec(n - 1) + f_rec(n - 3); 
	}
	return f[n] = f_rec(6 * n / 7) + f_rec(2 * n / 3);
}
int main()
{
	ul n = 0;
	cin >> n;
	if (n <= 2) {
		cout << 1;
		return 0;
	}
	f[0] = 1;
	f[1] = 1;
	f[2] = 1;

	ul answer = (f_rec(n)) % mod;
	cout << answer << endl;
	return 0;
}