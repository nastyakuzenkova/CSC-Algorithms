#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int const maxN = 1E2;
int const maxM = 1E3;
int const infty = 1E9;

struct Edge
{
	int a;
	int b;
	int u;
	int cost;
	int p;

	Edge() : a(0), b(0), u(0), cost(0), p(0) {}
	Edge(int ia, int ib, int iu, int icost, int ip) : a(ia), b(ib), u(iu), cost(icost), p(ip) {}	
};

vector<Edge> edges;
int n;
int m;
int from = 0;
int to;
int dist[maxN];
int previous[maxN];

ll result;

bool ford_bellman()
{
	for (int i = 0; i < n; ++i) {
		dist[i] = infty;
	}
	dist[from] = 0;
	bool improved = true;
	while (improved) {
		improved = false;
		for (int i = 0; i < edges.size(); ++i) {
			Edge edge = edges[i];
			if (dist[edge.a] != infty && edge.p < edge.u && dist[edge.b] > dist[edge.a] + edge.cost) {
				dist[edge.b] = dist[edge.a] + edge.cost;
				previous[edge.b] = i;
				improved = true;
			}
		}
	}

	return dist[to] != infty;
}

void relax()
{
	int f = infty;
	int v = to;
	while (v != from) {
		int cur = previous[v];
		int k = edges[cur].u - edges[cur].p;
		if (f > k) {
			f = k;
		}
		v = edges[cur].a;
		//printf("%d\n", v);
	}

	v = to;
	while (v != from) {
		int cur = previous[v];
		edges[cur].p += f;
		edges[cur ^ 1].p -= f;
		result = result + (ll)edges[cur].cost * f;

		v = edges[cur].a;
		//printf("%d\n", v);
	}
}

int main()
{
	freopen("mincost.in", "rt", stdin);
	freopen("mincost.out", "wt", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int a, b, u, cost;
		scanf("%d %d %d %d", &a, &b, &u, &cost);
		a--;
		b--;
		edges.push_back(Edge(a, b, u, cost, 0));
		edges.push_back(Edge(b, a, 0, -cost, 0));
	}

	to = n - 1;
	result = 0;
	while (ford_bellman()) {
		relax();
	}

	printf("%lld\n", result);

	return 0;
}