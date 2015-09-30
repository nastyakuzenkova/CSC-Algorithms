#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

long nastulik;
// const int N = 1742540;
const int N = 3000000;
const int p_max = pow(2, 17) - 1;
int p[N];
int p_n = 0;

void load_primes2(int num)
{
	bool *er = (bool *)calloc(num + 1, sizeof(bool));
	int i = 2;
	p_n = 0;
	int sq = sqrt(num) + 1;
	while (i < num)
	{
		if(!er[i]) {
			p[p_n++] = i;
			if (p_n == p_max) 	return;

			if(i > sq) {
				++i;
				continue;
			}
			for (int j = i * i; j < num + 1; j += i)
			{
				er[j] = true;
			}
		}
		++i;
	}
	free(er);
}

void read_input()
{
	freopen("unfair.in", "rt", stdin);
	scanf("%ld", &nastulik);
}

int main()
{
	freopen("unfair.out", "wt", stdout);
	read_input();

	// clock_t begin, end;
	// double time_spent;
	// begin = clock();

	load_primes2(N);
		
	// printf("%d\n", p_n);
	// printf("%d\n", p[p_n - 1]);

	int x = 0;
	for (int i = 0; i < p_n; ++i)
	{
		while (nastulik % p[i] == 0) {
			nastulik = nastulik / p[i];
			x = x ^ (i + 1);
		}
	}

	if (nastulik == 1) {
		if (x == 0) {
			printf("%s\n", "Vasya");
		}
		else {
			printf("%s\n", "David");
		}
	}
	else {
		printf("%s\n", "David");
	}

	// end = clock();
	// time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("TIME %f\n", time_spent);
	
	return 0;
}