#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int k = -1;
int a[20];
int m = -1;
int Ns[10000];

const int maxN = 1E6;
bool winners[maxN + 1];
int calcIndex = 0;

void read_input()
{
	freopen("heaps2.in", "rt", stdin);
	scanf("%d", &k);
	int t;
	for (int i = 0; i < k; ++i)
	{
		scanf("%d", &t);
		a[i] = t;
	}
	sort (a, a + k);
	scanf("%d", &m);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d", &t);
		Ns[i] = t;
	}
}

void printResult(bool first)
{
	printf("%s\n", (first ? "First" : "Second"));
}

void calculateWinners(int N)
{
	for (int i = calcIndex + 1; i < N + 1; ++i)
	{
		bool w = false;
		for (int j = 0; j < k; ++j)
		{
			if((i - a[j] < 0) || (w = w || !winners[i - a[j]]))	break;
		}
		winners[i] = w;
	}
	calcIndex = max(calcIndex, N);
	printResult(winners[N]);
}

int main()
{
	read_input();
	freopen("heaps2.out", "wt", stdout);
	winners[0] = false;
	for (int i = 0; i < m; ++i)
	{
		calculateWinners(Ns[i]);
	}
	return 0;
}