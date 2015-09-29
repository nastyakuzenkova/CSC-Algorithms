#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int const deskSize = 8;
int const N = deskSize * deskSize;
bool visited[N];
int previous[N];
int const movesx[8] = {-1, 1, -2, -2, -1, 1, 2, 2};
int const movesy[8] = {-2, -2, -1, 1, 2, 2, -1, 1};
int const minV = 0;
int const maxV = 7;
int startPoint;
int endPoint;

vector<int> connected(const int &v)
{
	vector<int> result;
	int vx = v % deskSize;
	int vy = v / deskSize;
	for (int i = 0; i < deskSize; ++i) {
		int curVx = vx + movesx[i];
		int curVy = vy + movesy[i];
		if (curVx >= minV && curVx <= maxV
			&& curVy >= minV && curVy <= maxV) {
			int curV = deskSize * curVy + curVx;
			result.push_back(curV);
		}
	}
	return result;
}

void bfs(const int &v)
{
	queue<int> vertices;
	vertices.push(v);
	visited[v] = true;
	
	while (!vertices.empty()) {
		int curV = vertices.front();
		vertices.pop();
		vector<int> neibours = connected(curV);
		int size = neibours.size();
		for (int i = 0; i < size; ++i) {
			int j = neibours.at(i);
			if (!visited[j]) {
				vertices.push(j);
				visited[j] = true;
				previous[j] = curV;
			}
		}
	}
}

int main()
{
	#define NAME "knight1"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));

	char start[3];
	char end[3];
	scanf("%s%s", start, end);
	int y1 = start[0] - 'a';
	int x1 = start[1] - '1';

	int y2 = end[0] - 'a';
	int x2 = end[1] - '1';
	
	startPoint = deskSize * y1 + x1;
	endPoint = deskSize * y2 + x2;
	//printf("%d %d\n", startPoint, endPoint);

	bfs(startPoint);
	stack<int> path;
	int curV = endPoint;
	while (curV != startPoint) {
		path.push(curV);
		curV = previous[curV];
	}
	path.push(startPoint);

	while (!path.empty()) {
		char c = 'a' + path.top() / deskSize;
		int pos = path.top() % deskSize + 1;
		printf("%c%d\n", c, pos);
		path.pop();
	}
	return 0;
}