#include <cstdio>
#include <algorithm>

using namespace std;

int n = 0;
int a[100000];

int less_then(const int &bound) {
	if (a[0] >= bound) {
		return 0;
	}
	if (a[n - 1] < bound) {
		return n;
	}
	int result = 0;
	int l = 0;
	int r = n - 1;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (a[mid] < bound) {
			result += mid - l + 1;
			l = mid + 1;
		}
		else {
			r = mid;
		}		
	}
	return result;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		a[i] = i;
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	int k = 0;
	scanf ("%d", &k);
	for (int i = 0; i < k; ++i) {
		int l = 0;
		int r = 0;
		scanf("%d %d", &l, &r);
		int result = less_then(r + 1) - less_then(l);
		printf("%d ", result);
	}
}