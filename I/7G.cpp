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
int previous[N];
int v_cycle_start;
int v_cycle_end;

bool dfs(const int &v)
{
	visited[v] = marking;
	int size = graph[v].size();
	for (int i = 0; i < size; ++i) {
		int curV = graph[v].at(i);
		if (visited[curV] == marked) {
			continue;
		}
		if (visited[curV] == marking) {
			v_cycle_end = v;
			v_cycle_start = curV;
			return true;
		}
		previous[curV] = v;
		if (dfs(curV)) {
			return true;
		}
	}
	visited[v] = marked;
	return false;
}

int main()
{
	#define NAME "cycle"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		visited[i] = not_marked;
		previous[i] = -1;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
	}
	bool hasCycle = false;
	for (int i = 0; i < n; ++i) {
		if (visited[i] == marked) {
			continue;
		}
		if (dfs(i)) {
			hasCycle = true;
			break;
		}
	}
//	printf("%d %d\n", v_cycle_start, v_cycle_end);
	if (!hasCycle) {
		printf("NO");
	}
	else {
		printf("YES\n");
		stack<int> cycle;
		cycle.push(v_cycle_end);
		int curV = previous[v_cycle_end];
		while (curV != v_cycle_start) {
			cycle.push(curV);
			curV = previous[curV];
		}
		cycle.push(v_cycle_start);
		while (!cycle.empty()) {
			printf("%d ", cycle.top() + 1);
			cycle.pop();
		}
	}
	printf("\n");
	return 0;
}