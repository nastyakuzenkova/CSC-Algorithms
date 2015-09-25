#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

int const N = 100;
vector<int> graph[N];
bool visited[N];

int dfs(const int &v)
{
	int count = 0;
	if (visited[v]) {
		return count;
	}
	visited[v] = true;
	count++;
	for (int i = 0; i < graph[v].size(); ++i) {
		count += dfs(graph[v].at(i));
	}
	return count;
}

int main()
{
	#define NAME "connect"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		visited[i] = false;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	int count = dfs(0);
	if (count < n) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
	}
	return 0;
}