#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

int const maxN = 2E5;
int z[maxN];
int p[maxN];

int main()
{	
	freopen("trans.in","rt",stdin);
	freopen("trans.out","wt",stdout);

	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int temp = 0;
		scanf("%d", &temp);
		z[i] = temp;
	}

	int pi = 1;
	for (int i = 0; i < N; ++i) {
		while (pi < i - z[pi] + 1) {
			++pi;
		}
		p[i] = i - pi + 1;
	}

	for (int i = 0; i < N; ++i) {
		printf("%d ", p[i]);
	}

	return 0;
}

