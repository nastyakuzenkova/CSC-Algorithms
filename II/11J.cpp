#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

int N;
int *val;
int *ex;
bool *f;
const int start_period_index = 52;
const int period = 34; 
const int predefined_N = start_period_index + period * 2;
//const int predefined_N = 10000;

void read_input()
{
	freopen("pawns.in", "rt", stdin);
	scanf("%d", &N);

	val = new int[predefined_N + 1];
	ex = new int[predefined_N + 1];
	f = new bool[predefined_N + 1];
	for (int i = 0; i < predefined_N + 1; ++i)
	{
		val[i] = -1;
	}
	val[0] = 0;
	val[1] = 1;
	val[2] = 1;
}

int vector_ex(int *v, int n)
{
	for (int i = 0; i < predefined_N; ++i)
	{
		f[i] = false;
	}
	for (int i = 0; i < n; ++i)
	{
		f[v[i]] = true;
	}
	for (int i = 0; i < predefined_N; ++i)
	{
		if (!f[i])	return i;
	}
	return 0;
}

void custom_dfs(int n)
{
	if (val[n] != -1)	return;

	custom_dfs(n - 2);
	
	int mid = ceil(n / 2.0) + 1;
	for (int i = 3; i <= mid; ++i)
	{
		custom_dfs(i - 3);
		custom_dfs(n - i);
	}

	ex[0] = val[n - 2];
	for (int i = 3; i <= mid; ++i)
	{
		ex[i - 2] = val[i - 3] ^ val[n - i];
	}
	val[n] = vector_ex(ex, mid - 1);
}

int main()
{
	freopen("pawns.out", "wt", stdout);
	read_input();


	// clock_t begin, end;
	// double time_spent;
	// begin = clock();

	custom_dfs(predefined_N);
	// for (int i = 0; i < predefined_N; ++i)
	// {
	// 	printf("%d : %d\n", i, val[i]);
	// }
	// for (int i = start_period_index; i < predefined_N - period - 1; ++i)
	// {
	// 	if (val[i] != val[i + period]) printf("%d\n", i);
	// }
	int def_index = N > start_period_index ? (N - start_period_index) % period + start_period_index : N;

	if (val[def_index] == 0) {
		printf("Black\n");
	}
	else {
		printf("White\n");
	}

	// end = clock();
	// time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("TIME %f\n", time_spent);
	
	return 0;
}