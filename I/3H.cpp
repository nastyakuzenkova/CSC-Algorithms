#include <cstdio>
#include <algorithm>

using namespace std;

struct Dream {
	int i;
	long a;
	long b;
};


bool compareDreams (const Dream &dream1, const Dream &dream2) {
		return ((dream1.a + dream1.b) > (dream2.a + dream2.b));
	}

Dream dreams[100000];

int main()
{
	int n = 0;
	scanf("%d", &n);
	long sum = 0;
	for (int i = 0; i < n; ++i) {
		long a = 0;
		scanf("%ld", &a);
		sum += a;
		dreams[i].i = i + 1;
		dreams[i].a = a;
	}

	for (int i = 0; i < n; ++i) {
		long b = 0;
		scanf("%ld", &b);
		dreams[i].b = b;
	}

	sort(dreams, dreams + n, compareDreams);
	for (int i = 0; i < n; ++i) {
		if ((dreams[i].a + dreams[i].b) <= sum) {
			printf("-1\n");
			return 0;
		}
		sum -= dreams[i].a;
	}
	for (int i = 0; i < n; ++i) {
		printf("%d ", dreams[i].i);
	}
	return 0;
}