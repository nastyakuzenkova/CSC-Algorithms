#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int const maxN  = 250;

vector<int> edges[maxN + 1];
int matched[maxN + 1];
bool used[maxN + 1];
int maxP = 0;
int n = 0;
int m = 0;

void init()
{
	for (int i = 0; i <= maxN; ++i) {
		used[i] = false;
		matched[i] = -1;
	}
}

void resetUsed()
{
	for (int i = 1; i <= n; ++i) {
		used[i] = false;
	}
}

bool tryFind(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (unsigned i = 0; i < edges[v].size(); ++i) {
		int to = edges[v].at(i);
		if (matched[to] == -1 || tryFind(matched[to])) {
			matched[to] = v;
			return true;
		}
	}
	return false;
}

int main()
{
	init();
	freopen("pairs.in", "rt", stdin);
	freopen("pairs.out", "wt", stdout);

	cin >> n >> m;
	int temp = 0;
	for (int i = 1; i <= n; ++i) {
		do {
			cin >> temp;
			if (temp != 0)
				edges[i].push_back(temp);
			else
				break;
		}
		while (true);
	}

	for (int i = 1; i <= n; ++i) {
		resetUsed();
		if (tryFind(i))
			maxP++;
	}

	cout << maxP << "\n";

	for (int i = 1; i <= m; ++i) {
		if (matched[i] != -1) {
			cout << matched[i] << " " << i << "\n";
		}
	}

	return 0;
}

