#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> segment_tree[300000];

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

bool hasX(const int &current, const int &left, const int &right, 
	const int &cur_left, const int &cur_right, const int &x)
{
	if (cur_left > cur_right) {
		return false;
	}
	if (left == cur_left && right == cur_right) {
		return binary_search(segment_tree[current].begin(),
								segment_tree[current].end(),
								x);
	}
	int mid = (left + right) / 2;
	int r = (cur_right < mid) ? cur_right : mid;
	int l = (cur_left > (mid + 1)) ? cur_left : (mid + 1);
	//printf("%d %d %d\n", mid, r, l);
	return hasX(2 * current, left, mid, cur_left, r, x)
			|| hasX (2 * current + 1, mid + 1, right, l, cur_right, x);
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	init(a, 1, 0, n - 1);
	int m = 0;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int l = 0;
		int r = 0;
		int x = 0;
		scanf("%d %d %d", &l, &r, &x);
		if (hasX(1, 0, n - 1, l - 1, r - 1, x)) {
			printf("%c", '1');
		}
		else {
			printf("%c", '0');
		}
	}
	return 0;
}