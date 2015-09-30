#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int const maxN = 100000;
int const c = 1;

vector<int> edges[maxN + 1];
vector<int> flow[maxN + 1];
vector<int> edgesBack[maxN + 1];
vector<int> flowBack[maxN + 1];
bool used[maxN + 1];
int n = 0;
int m = 0;
int s = 0;
int t = 0;


bool dfs(int v) {
	used[v] = true;
	if (v == t)
		return true;
	for (unsigned i = 0; i < edges[v].size(); ++i) {
		int x = edges[v].at(i);
		if (!used[x] && flow[v].at(i) < c && dfs(x)) {
			flow[v].at(i)++;
			int j = 0;
			while (edgesBack[x].at(j) != v)
				j++;
			flowBack[x].at(j)--;
			return true;
		}
	}
	for (unsigned i = 0; i < edgesBack[v].size(); ++i) {
		int x = edgesBack[v].at(i);
		if (!used[x] && flowBack[v].at(i) < 0 && dfs(x)) {
			flowBack[v].at(i)++;
			int index = 0;
			while (edges[x].at(index) != v)
				index++;
			flow[x].at(index)--;
			return true;
		}
	}
	return false;
}

void resetUsed()
{
	for (int i = 0; i < maxN; ++i) {
		used[i] = false;
	}
}

bool dfs()
{
	resetUsed();
	return dfs(s);
}

void path(int v) {
	printf("%d ", v);
	for (unsigned i = 0; i < edges[v].size(); ++i) {
		if (flow[v].at(i) == c) {
			flow[v].at(i)--;
			path(edges[v].at(i));
			return;
		}
	}
}

void path()
{
	path(s);
}

int main()
{
	freopen("snails.in", "rt", stdin);
	freopen("snails.out", "wt", stdout);

	scanf("%d %d %d %d", &n, &m, &s, &t);

	int start = 0;
	int end = 0;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &start, &end);
		edges[start].push_back(end);
		flow[start].push_back(0);
		edgesBack[end].push_back(start);
		flowBack[end].push_back(0);
	}

	if (dfs() && dfs()) {
		printf("YES\n");
		path();
		printf("\n");
		path();
	}
	else
		printf("NO");

	return 0;
}