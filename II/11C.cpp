#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cost[8][8];
int res[8][8][2];
bool vis[8][8][2];

const int maxRes = 15000;

int minmax(int t1, int t2, bool isMax)
{
	if (isMax) {
		return max(t1, t2);
	}
	else {
		return min(t1, t2);
	}
}

void custom_dfs(int x, int y, bool turn) 
{
	if (vis[x][y][turn])	return;

	vis[x][y][turn] = true;
	bool right = (7 - x > 0);
	bool top = (7 - y > 0);
	if (!right && !top) {
		res[x][y][turn] = cost[7][7] * (!turn ? 1 : -1);
	}
	else {
		int c = turn ? -maxRes : maxRes;
		if (right) {
			custom_dfs(x + 1, y, !turn);
			c = minmax(c, res[x + 1][y][!turn], turn);
		}
		if (top) {
			custom_dfs(x, y + 1, !turn);
			c = minmax(c, res[x][y + 1][!turn], turn);
		}
		if (top && right) {
			custom_dfs(x + 1, y + 1, !turn);
			c = minmax(c, res[x + 1][y + 1][!turn], turn);
		}
		c += (cost[x][y] * (!turn ? 1 : -1));
		res[x][y][turn] = c;
	}
}

void read_input()
{
	freopen("king3.in", "rt", stdin);
	for (int i = 7; i >= 0; --i)
	{
		for (int j = 0; j < 8; ++j)
		{
			int t;
			scanf("%d", &t);
			cost[i][j] = t;

			vis[i][j][0] = false;
			vis[i][j][1] = false; 
		}
	}
	cost[0][0] = 0;
}

int main()
{
	freopen("king3.out", "wt", stdout);
	read_input();
	custom_dfs(0, 0, true);
	printf("%d\n", res[0][0][true]);
	return 0;
}