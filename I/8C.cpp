#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

int const N = 1e5;
vector<int> graph[N];
bool visited[N];
int dist[N];

void bfs(const int &v)
{
	queue<int> vertices;
	vertices.push(v);
	visited[v] = true;
	
	while (!vertices.empty()) {
		int curV = vertices.front();
		vertices.pop();
		int size = graph[curV].size();
		for (int i = 0; i < size; ++i) {
			int j = graph[curV].at(i);
			if (!visited[j]) {
				dist[j] = dist[curV] + 1;
				vertices.push(j);
				visited[j] = true;
			}
		}
	}
}

int main()
{
	#define NAME "bfsrev"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m, s;
	scanf("%d%d%d", &n, &s, &m);
	s--;
	for (int i = 0; i < n; ++i) {
		visited[i] = false;
		dist[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[to].push_back(from);
	}
	bfs(s);
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			printf("-1 ");
		}
		else {
			printf("%d ", dist[i]);
		}
	}
	printf("\n");
	return 0;
}