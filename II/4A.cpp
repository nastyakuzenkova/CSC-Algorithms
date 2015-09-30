#include <iostream>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

int main()
{
	freopen("unequal.in", "rt", stdin);
	freopen("unequal.out", "wt", stdout);

	string str;
	cin >> str;
	int str_len = str.size();

	set<string> str_set;

	for (int i = 0; i <= str_len; ++i) {
		for (int j = 0; j < i; ++j) {
			str_set.insert(str.substr(j, i - j));
		}
	}

	cout << str_set.size();

	return 0;
}