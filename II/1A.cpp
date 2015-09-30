#include <iostream>
#include <math.h>
#include "vector"
#include <cstdio>

using namespace std;

int const maxN = 1E5;
int const maxM = 1E5;
int const maxK = 16;
int const ROOT = 0;

static vector<int> tree[maxN + 1];
static int n, m, t, k;
static int up[maxN + 1][maxK + 1];
static int in_time[maxN + 1];
static int out_time[maxN + 1];

void dfs(int a, int parent) 
{
	++t;
	in_time[a] = t;

	up[a][0] = parent;
	for (int i = 1; i <= k; ++i) {
		up[a][i] = up[up[a][i - 1]][i - 1];
	}
	for (int i = 0; i < tree[a].size(); ++i) {
		if (tree[a][i] != parent) {
			dfs(tree[a][i], a);
		}
	}
	
	++t;
	out_time[a] = t;
}

bool isAncestor(int a, int b)
{
	return ((in_time[a] <= in_time[b])
	 		&& (out_time[a] >= out_time[b]));
}

int main()
{
	freopen("ancestor.in", "rt", stdin);
	freopen("ancestor.out", "wt", stdout);

	scanf("%d", &n);

	int temp = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &temp);
		tree[temp].push_back(i);
	}
	t = 0;
	dfs(ROOT, ROOT);

	scanf("%d", &m);

	int a = 0;
	int b = 0;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		cout << (isAncestor(a, b) ? 1 : 0) << "\n";
	}

	return 0;
}

