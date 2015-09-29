#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

int const N = 1000;
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
	#define NAME "sumdist"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		visited[i] = false;
		dist[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		from--;
		to--;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	long sumdist = 0;
	for (int i = 0; i < n; ++i) {
		
		bfs(i);

		for (int j = 0; j < n; ++j) {
			sumdist += dist[j];
		}
		for (int j = 0; j < n; ++j) {
			dist[j] = 0;
			visited[j] = false;
		}
	}
	printf("%ld\n", sumdist / 2);
}