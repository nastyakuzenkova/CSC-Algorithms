#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main()
{
	freopen("basis.in", "rt", stdin);
	freopen("basis.out", "wt", stdout);

	string str;
	cin >> str;
	int n = str.length();
	int prefix_function[n];

	for (int i = 0; i < n; ++i) {
		prefix_function[i] = 0;
	}

	for (int i = 1; i < n; ++i) {
		int j = prefix_function[i - 1];
		while(j > 0 && str[i] != str[j]) {
			j = prefix_function[j - 1];
		}
		if (str[i] == str[j]) {
			++j;
		}
		prefix_function[i] = j;
	}

	long long result = n - prefix_function[n - 1];
	cout << result;

	return 0;
}