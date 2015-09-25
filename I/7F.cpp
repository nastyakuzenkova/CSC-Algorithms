#include <cstdio>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

int const not_marked = 0;
int const marking = 1;
int const marked = 2;

int const N = 100000;
vector<int> graph[N];
int visited[N];
stack<int> topSort;

bool dfs(const int &v)
{
	if (visited[v] == marked) {
		return true;
	}
	if (visited[v] == marking) {
		return false;
	}
	visited[v] = marking;
	int size = graph[v].size();
	for (int i = 0; i < size; ++i) {
		if (!dfs(graph[v].at(i))) {
			return false;
		}
	}
	topSort.push(v);
	visited[v] = marked;
	return true;
}

int main()
{
	#define NAME "topsort"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		visited[i] = not_marked;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
	}
	bool possibleTopSort = true;
	for (int i = 0; i < n; ++i) {
		if (visited[i] == not_marked) {
			possibleTopSort = dfs(i);
		}
		if (!possibleTopSort) {
			break;
		}
	}
	if (!possibleTopSort) {
		printf("-1");
	}
	else {
		while (!topSort.empty()) {
			printf("%d ", topSort.top() + 1);
			topSort.pop();
		}
	}
	printf("\n");
	return 0;
}