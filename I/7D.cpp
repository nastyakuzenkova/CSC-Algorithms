#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

int const N = 20000;
vector<int> graph[N];
bool visited[N];
int component[N];
int c = 1;

bool dfs(const int &v)
{
	if (visited[v]) {
		return false;
	}
	visited[v] = true;
	component[v] = c;
	for (int i = 0; i < graph[v].size(); ++i) {
		dfs(graph[v].at(i));
	}
	return true;
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
		component[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	for (int i = 0; i < n; ++i) {
		if (dfs(i)) {
			c++;
		}
	}
	c--;
	printf("%d\n", c);
	for (int i = 0; i < n; ++i) {
		printf("%d ", component[i]);
	}
	return 0;
}