#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;
const int maxM = 500;
int m;
int beginTime[maxM + 1], endTime[maxM + 1], a[maxM + 1], b[maxM + 1], c[maxM + 1], d[maxM + 1];
static vector<int> vertexes[maxM + 1];
static bool usedVertexes[maxM + 1];
static int chain[maxM + 1];

bool dfs(int vertex) 
{
	if(usedVertexes[vertex]) {
		return false;
	}

	usedVertexes[vertex] = true;
	vector<int> neigbours = vertexes[vertex];
	for (int i = 0; i < (int)neigbours.size(); ++i) {
		int neigbour = neigbours[i];
		if(chain[neigbour] == -1 || dfs(chain[neigbour])) {
			chain[neigbour] = vertex;
			return true;
		}
	}
	return false;
}

void doDfs()
{
	for (int i = 0; i <= m; ++i) {
		usedVertexes[i] = false;
		chain[i] = -1;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			usedVertexes[j] = false;
		}
		dfs(i);
	}
}

void read()
{
	for (int i = 1; i <= m; ++i) {
		int hh, mm, ak, bk, ck, dk;
		scanf("%d:%d %d %d %d %d", &hh, &mm, &ak, &bk, &ck, &dk);
		a[i] = ak;
		b[i] = bk;
		c[i] = ck;
		d[i] = dk;
		beginTime[i] = hh * 60 + mm;
		endTime[i] = abs(a[i] - c[i]) + abs(b[i] - d[i]) + beginTime[i];
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {
			if (endTime[i] + abs(c[i] - a[j]) + abs(d[i] - b[j]) < beginTime[j]) {
				vertexes[i].push_back(j);
			}
		}
	}
}

int solve()
{
	int cars = 0;
	for (int i = 1; i <= m; ++i) {
		if (chain[i] != -1) {
			int j = chain[i];

			if (usedVertexes[j]) {
				usedVertexes[i] = true;

			} else {
				usedVertexes[i] = true;
				usedVertexes[j] = true;
				cars++;
			}
		}
	}

	for (int i = 1; i <= m; ++i) {
		if (!usedVertexes[i]) {
			cars++;
		}
	}
	return cars;
}

int main()
{
	freopen("taxi.in", "rt", stdin);
	freopen("taxi.out", "wt", stdout);
	scanf("%i", &m);

	read();
	doDfs();
	for (int i = 1; i <= m; ++i) {
		usedVertexes[i] = false;
	}

	printf("%i", solve());
	return 0;
}

