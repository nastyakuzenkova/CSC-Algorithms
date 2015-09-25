#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

int const N = 100;
vector<int> graph[N];
bool visited[N];
int previous[N];
int c = 0;

bool dfs(const int &v)
{
	if (visited[v]) {
		return false;
	}
	visited[v] = true;
	c++;
	for (int i = 0; i < graph[v].size(); ++i) {
		int curV = graph[v].at(i);
		if (curV == previous[v]) {
			continue;
		}
		previous[curV] = v;
		if (!dfs(curV)) {
			return false;
		}
	}
	return true;
}

int main()
{
	#define NAME "tree"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		visited[i] = false;
		previous[i] = -1;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	if (dfs(0) && c >= n) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}