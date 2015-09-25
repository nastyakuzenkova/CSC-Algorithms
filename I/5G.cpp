#include <iostream>
#include <stack>
#include <climits>

using namespace std;

typedef unsigned long long ull;

struct LifeMoment
{
	int i;
	ull value;	
};

int n;
LifeMoment a[100000];

int main()
{
	ios_base::sync_with_stdio(false);
	cin >> n;
	int nextj[n];
	int previousj[n];
	for (int i = 0; i < n; ++i) {
		ull x;
		cin >> x;
		a[i].value = x;
		a[i].i = i;
		nextj[i] = previousj[i] = -1;
	}
	ull s[n];
	s[0] = a[0].value;
	for (int i = 1; i < n; ++i) {
		s[i] = s[i - 1] + a[i].value;
	}

	stack<LifeMoment> moments;
	for (int i = 0; i < n; ++i) {
		if (moments.empty() || moments.top().value <= a[i].value) {
			moments.push(a[i]);
		}
		else {
			while (!moments.empty() && (moments.top().value > a[i].value)) {
				nextj[moments.top().i] = i - 1;
				moments.pop();
			}
			moments.push(a[i]);
		}
	}
	while (!moments.empty()) {
		moments.pop();
	}
	for (int i = n - 1; i >= 0; --i) {
		if (moments.empty() || moments.top().value <= a[i].value) {
			moments.push(a[i]);
		}
		else {
			while (!moments.empty() && moments.top().value > a[i].value) {
				previousj[moments.top().i] = i + 1;
				moments.pop();
			}
			moments.push(a[i]);
		}
	}
	for (int i = 0; i < n; ++i) {
		if (previousj[i] == -1) {
			previousj[i] = 0;
		}
		if (nextj[i] == -1) {
			nextj[i] = n - 1;
		}
	}
	ull currentMax = 0;
	int resultl = 0;
	int resultr = 0;
	for (int i = 0; i < n; ++i) {
		ull currentMin = a[i].value;
		int l = previousj[i];
		int r = nextj[i];
		ull currentSum;
		if (l <= 0) {
			currentSum = s[r];
		} 
		else {
			currentSum = s[r] - s[l - 1];
		}
		ull possibleMax = currentSum * currentMin;
		if (possibleMax > currentMax) {
			currentMax = possibleMax;
			resultr = r;
			resultl = l;
		}
	}
	cout << currentMax << endl; 
	cout << (resultl + 1) << " " << (resultr + 1) << endl;
	return 0;
}