#include <iostream>
#include <stack>
#include <map>

using namespace std;

stack<char> psp;
map<char, char> pairs;

bool isOpen(char c) {
	return (c == '(' || c == '[' || c == '{');
}
bool isClose(char c) {
	return (c == ')' || c == ']' || c == '}');
}

int main()
{
	ios_base::sync_with_stdio(false);
	pairs['['] = ']';
	pairs['{'] = '}';
	pairs['('] = ')';
	char c;
	while (cin >> c) {
		if (isOpen(c)) {
			psp.push(c);
		}
		else if (isClose(c)) {
			if (psp.empty()) {
				cout << "NO\n";
				return 0;
			}
			char b = psp.top();
			if (pairs[b] == c) {
				psp.pop();
			}
			else {
				cout << "NO\n";
				return 0;
			}
		}
	}
	if (psp.empty()) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	return 0;
}