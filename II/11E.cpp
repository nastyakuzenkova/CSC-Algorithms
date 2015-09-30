#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool vis[5001];
int val[5001];
int N;
vector<int> shots;

int vector_ex(vector<int> v)
{
	sort(v.begin(), v.end());

	if (v[0] != 0) 	return 0;

	for (int i = 1; i < v.size(); ++i)
	{
		if (v[i] - v[i - 1] > 1)	return v[i - 1] + 1;
	}
	return v[v.size() - 1] + 1;
}

void custom_dfs(int k) 
{
	if (vis[k])	 return;

	vis[k] = true;

	custom_dfs(k - 1);
	custom_dfs(k - 2);
	int mid = ceil(k / 2.0);
	for (int i = 3; i <= mid; ++i)
	{
			custom_dfs(k - i);
			custom_dfs(i - 1);
	}

	if (k == N) {
		if (val[k - 1] == 0)	shots.push_back(1);
		if (val[k - 2] == 0)	shots.push_back(2);
		for (int i = 3; i <= mid; ++i)
		{
			if ((val[k - i] ^ val[i - 1]) == 0) 	shots.push_back(i);
		}

		int size = shots.size();
		for (int i = size - 1; i >= 0; --i)
		{
			if (shots[i] != mid) 	shots.push_back(k - shots[i] + 1);
		}
	}
	else {
		vector<int> values;
		values.push_back(val[k - 1]);
		values.push_back(val[k - 2]);
		for (int i = 3; i <= mid; ++i)
		{
			values.push_back(val[k - i] ^ val[i - 1]);
		}
		val[k] = vector_ex(values);
	}
}

void read_input()
{
	freopen("cruel.in", "rt", stdin);
	scanf("%d", &N);

	vis[2] = true;
	vis[3] = true;

	val[2] = 1;
	val[3] = 2;

	if (N == 3) {
		shots.push_back(2);
	}
	else if (N ==2 ) {
		shots.push_back(1);
		shots.push_back(2);
	}
}

int main()
{
	freopen("cruel.out", "wt", stdout);
	read_input();
	custom_dfs(N);
	
	if (shots.size() == 0) {
		printf("%s\n", "Mueller");
	}
	else {
		printf("%s\n", "Schtirlitz");
		for (int i = 0; i < shots.size(); ++i)
		{
			printf("%d\n", shots[i]);
		}
	}
	return 0;
}