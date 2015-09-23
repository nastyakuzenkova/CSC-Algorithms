#include <iostream>

using namespace std;

int n = 0;
unsigned int m = 0;
unsigned int a = 0;
unsigned int b = 0;
unsigned int y[1000000];

unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

long merge(unsigned int x[], int l, int mid, int r)
{
	int b1 = l;
	int b2 = mid + 1;
	long inv = 0;
	int i = 0;
	while ((b1 <= mid) && (b2 <= r)) {
		if (x[b1] <= x[b2]) {
			y[i++] = x[b1++];
		}
		else {
			y[i++] = x[b2++];
			inv += (mid - b1 + 1);
		}
	}
	while(b1 <= mid)
		y[i++] = x[b1++];

	while(b2 <= r)
		y[i++] = x[b2++];

	for (int j = l; j <= r; ++j) {
		x[j] = y[j - l];
	}
	return inv;
}

long mergeSort(unsigned int x[], int l, int r)
{
	if (l >= r) {
		return 0;
	}
	int mid;
	long inv = 0;
		mid = (l + r) / 2;
		inv += mergeSort(x, l, mid);
		inv += mergeSort(x, mid + 1, r);
		inv += merge(x, l, mid, r);
	return inv;
}

int main()
{
	cin >> n >> m >> a >> b;
	unsigned int elements[n];
	for (int i = 0; i < n; ++i) {
		elements[i] = nextRand24() % m;
	}
	cout << mergeSort(elements, 0 , n - 1) << endl;
	return 0;
}