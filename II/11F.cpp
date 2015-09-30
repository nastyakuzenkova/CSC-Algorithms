#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
int a, b, c;
int val[5001];
int vis[5001];

void read_input()
{
	freopen("karlsson.in", "rt", stdin);
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	int m = max(a, max(b, c));
	for (int i = 0; i <= m; ++i)
	{
		vis[m] = false;
	}

	val[1] = 0;
	vis[1] = true;
}

int vector_ex(int *v, int n)
{
	bool f[5001];
	for (int i = 0;i < 5001; ++i)
	{
		f[i] = false;
	}
	for (int i = 0; i < n; ++i)
	{
		f[v[i]] = true;
	}
	for (int i = 0;i < 5001; ++i)
	{
		if (!f[i])	return i;
	}
	return 0;
}

void custom_dfs(int k)
{
	if (vis[k])	 return;

	vis[k] = true;

	int mid = ceil(k / 2.0);
	int values[k - mid];
	for (int i = mid; i < k; ++i)
	{
		custom_dfs(i);
		values[i - mid] = val[i];
	}
	val[k] = vector_ex(values, k - mid);
}

int main()
{
	freopen("karlsson.out", "wt", stdout);
	read_input();

	// clock_t begin, end;
	// double time_spent;
	// begin = clock();

	custom_dfs(max(a, max(b , c)));

	// end = clock();
	// time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("TIME %f\n", time_spent);
	int xa = val[a], xb = val[b], xc = val[c];
	int x = (xa ^ xb) ^ xc;

	if (x == 0) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
		int t = xa ^ x;
		int r = -1;
		for (int i = ceil(a / 2.0); i < a; ++i)
		{
			if (val[i] == t) {
				r = i;
				break;
			}
		}
		if (r != -1) {
			printf("%d %d %d\n", r, b, c);
			return 0;
		}
		r = -1;

		t = xb ^ x;
		for (int i = ceil(b / 2.0); i < b; ++i)
		{
			if (val[i] == t) {
				r = i;
				break;
			}
		}
		if (r != -1) {
			printf("%d %d %d\n", a, r, c);
			return 0;
		}
		r = -1;

		t = xc ^ x;
		for (int i = ceil(c / 2.0); i < c; ++i)
		{
			if (val[i] == t) {
				r = i;
				break;
			}
		}
		if (r != -1) {
			printf("%d %d %d\n", a, b, r);
			return 0;
		}
	}
	return 0;
}