#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int const maxN = 1E6;
int const c = 37;

char str[maxN];
char substr[maxN];

int main()
{
	freopen("search.in", "rt", stdin);
	freopen("search.out", "wt", stdout);

	gets(str);
	gets(substr);

	int n = strlen(str);
	int m = strlen(substr);
	if (m > n || n == 0 || m == 0) {
		printf("0\n");
		return 0;
	}

	long long hash_pow[n];
	hash_pow[0] = 1;
	for (int i = 1; i < n; ++i) {
		hash_pow[i] = c * hash_pow[i - 1];
	}

	long long hash[n];
	hash[0] = str[0] - 'a' + 1;
	for (int i = 1; i < n; ++i) {
		hash[i] = hash[i - 1] + (str[i] - 'a' + 1) * hash_pow[i];
	}

	queue<int> answer;

	long long hash_substr = 0;
	for (int i = 0; i < m; ++i) {
		hash_substr += (substr[i] - 'a' + 1) * hash_pow[i];
	}

	for (int i = 0; i < n - m + 1; ++i) {
		long long h = hash[i + m - 1];
		if (i > 0) {
			h = h - hash[i - 1];
		}

		if (h == hash_substr * hash_pow[i]) {
			answer.push(i + 1);
		}
	}

	printf("%lu\n", answer.size());
	while (!answer.empty()) {
		printf("%d ", answer.front());
		answer.pop();
	}

	return 0;
}