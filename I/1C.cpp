#include <iostream>
 using namespace std;

int const R = 15000;
bool hasStemp[R + 1];

 int main()
 {
 	for (int i = 0; i <= R; ++i) {
 		hasStemp[i] = false;
 	}
 	int n = 0;
 	cin >> n;
 	for (int i = 0; i < n; ++i) {
 		int current = 0;
 		cin >> current;
 		hasStemp[current] = true;
 	}
 	int rest = 0;
 	for (int i = 1; i <= R; ++i) {
 		if (!hasStemp[i]) {
 			rest++;
 		}
 	}
 	cout << rest << endl;
 	return 0;
 }