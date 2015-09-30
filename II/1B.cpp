#include <iostream>
#include <math.h>
#include <cstdio>

using namespace std;

int const maxN = 50000;
int const maxM = 50000;
int const maxK = 16;
int const ROOT = 1;

static int parent[maxN + 1];
static int n, m;
static int up[maxN + 1][maxK + 1];
static int dep[maxM + 1];

int equalize(int v, int difDep) 
{
	int h = difDep;
	int upA = v;

	for (int k = (maxK - 1); k >= 0; k--)
		if (h >= (1 << k)) {
			upA = up[upA][k];
			h -= (1 << k);
		}
	return upA;
}

int lca(int x, int y)
{
	int a = x;
	int b = y;

	if (a == b)
		return a;

	if (dep[a] < dep[b]) {
		b = equalize(b, dep[b] - dep[a]);
	} else {
		a = equalize(a, dep[a] - dep[b]);
	}

	if (a == b)
		return a;

	for (int k = (maxK - 1); k >= 0; --k) {
		int a1 = up[a][k];
		int b1 = up[b][k];
		if (a1 != b1) {
			a = a1;
			b = b1;
		}
	}
	int answer = 0;
	if (a != b)
		answer = up[a][0];
	else
		answer = a;
	return answer;
}

int main()
{
	freopen("lca.in", "rt", stdin);
	freopen("lca.out", "wt", stdout);

	scanf("%d", &n);
	parent[ROOT] = ROOT;
	dep[ROOT] = 0;
	int temp = 0;
	for (int i = 2; i <= n; ++i) {
		scanf("%d", &temp);
		parent[i] = temp;
	}

	for (int a = 1; a <= n; ++a)
		up[a][0] = parent[a];

	for (int k = 1; k <= maxK; ++k)
		for (int a = 1; a <= n; ++a)
			up[a][k] = up[up[a][k - 1]][k - 1];

	for (int a = 2; a <= n; ++a)
		dep[a] = dep[parent[a]] + 1;

	scanf("%d", &m);

	int a = 0;
	int b = 0;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		cout << lca(a, b) << "\n";
	}

	return 0;
}

