#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int t, n;
int a[101];

void read_input()
{
	freopen("varnim.in", "rt", stdin);
	scanf("%d", &t);

	for (int i = 0; i < t; ++i)
	{
		scanf("%d", &n);
		int r = 0;
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &a[j]);
			int  val;
			if (a[j] % 4 == 0) {
				val = a[j] - 1;
			}
			else if (a[j] % 4 == 3){
				val = a[j] + 1;
			}
			else {
				val = a[j];
			}
			r = r ^ val;
		}
		if (r != 0) {
			printf("FIRST\n");
		}
		else {
			printf("SECOND\n");
		}

	}
}

int main()
{
	freopen("varnim.out", "wt", stdout);
	read_input();

	// clock_t begin, end;
	// double time_spent;
	// begin = clock();


	// end = clock();
	// time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("TIME %f\n", time_spent);
	
	return 0;
}