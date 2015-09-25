#include <cstdio>
#include <iostream>
#include <string.h>

using namespace std;
int const maxN = 262144;

static int a[maxN + 1];
static int b[maxN + 1];
static int a_inv[maxN + 1];
static int b_inv[maxN + 1];
static int n = 0;

static int fenwickTree[maxN + 1];
bool used[maxN + 1];
void add(int i, int x)
{
	int j = i;
	while (j < n) {
		fenwickTree[j] += x;
		j |= (j + 1);
	}
}
void init()
{
	for (int i = 0; i < n; ++i) {
		fenwickTree[i] = 0;
		a[i] = b[i] = b_inv[i] = 0;
		used[i] = false;
	}
	for (int i = 0; i <= n; ++i) {
		add(i, 1);
	}
}
int f(int i)
{
	return (i & (i + 1));
}
int getPrefixSum(int x)
{
	int result = 0;
	int R = x;
	while (R >= 0) {
		result += fenwickTree[R];
		R = f(R) - 1;
	}
	return result;
}
int sum(int l, int r) {
	return getPrefixSum(r) - getPrefixSum(l-1);
}
void fill_a1()
{
	for (int i = 0; i < n; ++i) {
		 int r = n - 1; // a_inv[i] > 0 ? a_inv[i] - 1 : 0;
		 int l = 0;
		 while (l < r) {
			 int mid = r - (r - l) / 2;
			 int sm = sum(0, mid - 1);
			 if (a_inv[i] >= sm) {
				 l = mid;
			 } else {
				 r = mid - 1;
			 }
		 }
		 a[l] = i + 1;
		 add(l, -1);
	 }
	 for (int i = 0; i <= n; ++i) {
		 fenwickTree[i] = 0;
	 }
}
void fill_a2() {
	int current = 1;
	for (int k = 0; k < n; k++) {
		int j = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] == 0) {
				if (j == a_inv[k]) {
					a[i] = current;
					break;
				} else {
					j++;
				}
			}
		}
		current++;
	}
}
void fill_b()
{
	for (int i = 0; i < n; ++i)
		b[a[i] - 1] = i + 1;
}
void fill_b_inv()
{
	for (int i = 0; i < n; ++i) {
		b_inv[b[i] - 1] = sum(b[i] - 1, n - 1);
		add(b[i] - 1, 1);
	}
}
int main()
{
	FILE *in = fopen("invers2.in", "r");
	freopen("invers2.out", "wt", stdout);
	int temp = 0;
	while (!feof(in))
	{
		fscanf(in, "%d ", &temp);
		a_inv[n] = temp;
		n++;
	}
	init();
	fill_a1();
	fill_b();
	fill_b_inv();
	for (int i = 0; i < n; ++i)
		cout << b_inv[i] << " ";
	fclose(in);
	return 0;
}