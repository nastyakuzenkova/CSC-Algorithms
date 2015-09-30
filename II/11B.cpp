#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = -1;
int m = -1;

const int maxn = 300000;
vector<int> *vrgs;
vector<int> *vrgs_t;
int wss[maxn];
bool used[maxn];

//0-draw, 1-win, 2-lose
int sts[maxn];

bool check_instant_looser(int v)
{
	return vrgs[v].size() == 0;
}

vector<int> fill_loosers()
{
	vector<int> ls;
	for (int i = 0; i < n; ++i)
	{
		bool isLooser = check_instant_looser(i);
		sts[i] = isLooser ? 2 : 0;
		if (isLooser) {
			ls.push_back(i);
		}
	}
	return ls;
}

void custom_dfs(int v) 
{
	used[v] = true;
	for (int i = 0; i < vrgs_t[v].size(); ++i)
	{
		int next = vrgs_t[v][i];
		if (used[next])	continue;

		if (sts[v] == 2) {
			sts[next] = 1;
		}
		else if (sts[v] == 1 && (++(wss[next])) == vrgs[next].size()) {
			sts[next] = 2;
		}
		if (sts[next] != 0) {
			custom_dfs(next);
		}
	}
}

string stringifyStatus(int s)
{
	if (s == 1) {
		return "FIRST";
	}
	else if (s == 2) {
		return "SECOND";
	}
	else {
		return "DRAW";
	}
}
void printTestResult()
{
	for (int i = 0; i < n; ++i)
	{
		printf("%s\n", stringifyStatus(sts[i]).c_str());
	}
	printf("\n");
}

void read_input()
{
	freopen("retro.in", "rt", stdin);

	vrgs = (vector<int> *)malloc(maxn * sizeof(vector<int>));
	vrgs_t = (vector<int> *)malloc(maxn * sizeof(vector<int>));
	for (int i = 0; i < maxn; ++i)
	{
		vector<int> v;
		vrgs[i] = v;
		vrgs_t[i] = v;
	}

	while (scanf("%d", &n) != EOF) 
	{
		scanf("%d", &m);
		for (int i = 0; i < n; ++i) 
		{
			wss[i] = 0;
			used[i] = false;
			sts[i] = 0;
			vrgs[i].clear();
			vrgs_t[i].clear();
		}

		for (int i = 0; i < m; ++i)
		{
			int v, w;
			scanf("%d", &v);
			scanf("%d", &w);
			--w; --v;
			vrgs[v].push_back(w);
			vrgs_t[w].push_back(v);
		}

		vector<int> ls = fill_loosers();
		if (ls.size() > 0) {
			for (int i = 0; i < ls.size(); ++i)
			{
				custom_dfs(ls[i]);
			}
		}
		printTestResult();
	}
	free(vrgs);
	free(vrgs_t);
}

int main()
{
	freopen("retro.out", "wt", stdout);
	read_input();
	return 0;
}