#include <cstdio>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> segment_tree[400000];

void init(const int *a, const int &current, const int &left, const int &right)
{
	if (left == right) {
		segment_tree[current] = vector<int>(1, a[right]);
		return;
	}

	int mid = (left + right) / 2;
	int r = 2 * current;
	int l = 2 * current + 1;
	init(a, r, left, mid);
	init(a, l, mid + 1, right);
	merge(segment_tree[r].begin(), segment_tree[r].end(), 
		segment_tree[l].begin(), segment_tree[l].end(),
		back_inserter(segment_tree[current]));
}

int howMany(const int &current, const int &left, const int &right, 
	const int &cur_left, const int &cur_right, const int &x, const int &y)
{
	if (cur_left > cur_right) {
		return 0;
	}
	if (left == cur_left && right == cur_right) {
		return upper_bound(segment_tree[current].begin(),
								segment_tree[current].end(),
								y)
				- lower_bound(segment_tree[current].begin(),
								segment_tree[current].end(),
								x);
	}
	int mid = (left + right) / 2;
	int r = (cur_right < mid) ? cur_right : mid;
	int l = (cur_left > (mid + 1)) ? cur_left : (mid + 1);
	return howMany(2 * current, left, mid, cur_left, r, x, y)
			+ howMany (2 * current + 1, mid + 1, right, l, cur_right, x, y);
}

int main()
{
	ios_base::sync_with_stdio(false);
	#define NAME "permutation"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	cin >> n >> m;
	int a[n];
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		a[i] = x;
	}
	init(a, 1, 0, n - 1);
	for (int i = 0; i < m; ++i) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		cout << howMany(1, 0, n - 1, l - 1, r - 1, x, y) << endl;
	}
	return 0;
}