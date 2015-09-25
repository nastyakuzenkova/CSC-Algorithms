#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;

int n = 0;
int k = 0;
long a[10001];

bool canAllocate(const long &currentLength) {
	int count = 1;
	int cur = a[0];
	for (int i = 1; i < n; ++i) {
		if (a[i] - cur >= currentLength) {
			count++;
			cur = a[i];
		}
	}
	return (count >= k);
}

int max_dist(const int &bound) {
	if (canAllocate(bound)) {
		return bound;
	}
	int l = 1;
	int r = bound;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (canAllocate(mid)) {
			l = mid + 1;
		}
		else {
			r = mid;
		}		
	}
	return l - 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	#define NAME "cows"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		int x = 0;
		cin >> x;
		a[i] = x;
	}
	int max_possible_length = 1E9 + 1;	
	cout << max_dist(max_possible_length) << endl;
	return 0;
}