#include <cstdio>
#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int const N = 100000;
vector<int> graph[N];
bool visited[N];
stack<int> topSort;

void dfs(const int &v)
{
	if (visited[v]) {
		return;
	}
	visited[v] = true;
	int size = graph[v].size();
	for (int i = 0; i < size; ++i) {
		dfs(graph[v].at(i));
	}
	topSort.push(v);
}

int main()
{
	#define NAME "unitopsort"
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
	}
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			dfs(i);
		}
	}
	bool isUnique = true;
	int uniTopSort[n];
	int v = 0;
	while (!topSort.empty()) {
		int curV = topSort.top();
		uniTopSort[v] = curV;
		v++;
		topSort.pop();
	}
	for (int i = 1; i < n; ++i) {
		int from = uniTopSort[i - 1];
		int to = uniTopSort[i];
		if (find(graph[from].begin(), graph[from].end(), to) == graph[from].end()) {
			isUnique = false;
			break;
		}
	}
	if (!isUnique) {
		printf("NO");
	}
	else {
		printf("YES\n");
		for (int i = 0; i < n; ++i) {
			printf("%d ", uniTopSort[i] + 1);
		}
	}
	printf("\n");
	return 0;
}