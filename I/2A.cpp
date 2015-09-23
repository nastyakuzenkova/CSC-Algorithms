#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

stack<int> num[1001];

int main()
{
	int n = 0;
	int m = 0;
	cin >> n >> m;
	int a[m];
	for (int i = 0; i < m; ++i) {
		cin >> a[i];
		num[a[i]].push(i + 1);
	}
	sort(a, a + m);
	int sum = 0;
	int k = 0;
	bool found = false;
	for (int i = m - 1; i >= 0; --i) {
		sum += a[i];
		if (sum >= n) {
			k++;
			found = true;
			break;
		}
		k++;
	}
	if (!found) {
		cout << -1;
		return 0;
	}
	cout << k << endl;
	for (int i = m - 1; i >= m - k; --i) {
		cout << num[a[i]].top() << " ";
		num[a[i]].pop();
	}
	return 0;
}