#include <cstdio>

int main()
{
	int n = 0;
	int k = 0;
	scanf("%d %d", &n, &k);
	int a[n];
	for (int i = 0; i < n; ++i) {
		a[i] = i;
		scanf("%d", &a[i]);
	}
	int b[k];
	for (int i = 0; i < k; ++i) {
		b[i] = 1;
		scanf("%d", &b[i]);
	}

	int index = 0;
	int current = 0;
	int count = 0;
	while (current < n && count < k) {
		int current_a = a[current];
		int current_b = b[index];
		if (current_b < current_a) {
			printf("%s\n", "NO");
			count++;
			index++;
		}
		else if (current_b == current_a) {
			printf("%s\n", "YES");
			count++;
			index++;
		}
		else {
			current++;
		}
	}
	for (int i = index; i < k; ++i) {
		printf("%s\n", "NO");
	}
}