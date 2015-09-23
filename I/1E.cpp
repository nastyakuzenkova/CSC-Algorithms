#include <iostream>
 using namespace std;

 int main()
 {
 	int n = 0;
 	long m = 1;
 	cin >> n >> m;
 	long c[n + 1];
 	c[0] = 1;
 	for (int i = 1; i <= n; ++i) {
 		c[i] = 0;
 		for (int j = 0; j <= i - 1; ++j) {
 			c[i] = (c[i] + c[j] * c[i - j - 1]);
 			if (c[i] >= 1E9)
 			{
 				c[i] %= m;
 			}
 		}
 	}
 	cout << (c[n] % m) << endl;
 	return 0;
 }