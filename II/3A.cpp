#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int const maxN = 1E5 + 1;
int const isElement = -1;
int fenwickTree[maxN];

struct Event {
	int index;
	int value;
	int lowerBound;
	int upperBound;

	Event() {};
	Event(const int &i, const int &v, const int &lb, const int &ub) 
	: index(i), value(v), lowerBound(lb), upperBound(ub) {};

	bool operator < (const Event& event) const { 
    	return (value < event.value || 
    		(value == event.value && index < event.index)); 
    }
};

Event events[maxN * 3];

void init()
{
	for (int i = 0; i < maxN; ++i) {
		fenwickTree[i] = 0;
	}
}

void add(int i, int x)
{
	int j = i;
	while (j < maxN) {
		fenwickTree[j] += x;
		j |= j + 1;
	}
}

int f(int i)
{
	return (i & (i + 1));
}

int getPrefixSum(int x)
{
	int result = 0;
	int R = x;
	while (R >= 0) {
		result += fenwickTree[R];
		R = f(R) - 1;
	}
	return result;
}

int sum(int l, int r) 
{
	return getPrefixSum(r) - getPrefixSum(l - 1);
}

int main()
{
	freopen("permutation.in", "rt", stdin);
	freopen("permutation.out", "wt", stdout);
	init();

	int n = 0;
	int m = 0;
	scanf("%d%d", &n, &m);

	int c = 0;

	int elem = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &elem);
		events[c] = Event(isElement, i, elem, elem);
		c++;
	}

	int x, y, k, l;
	bool isOpened[m];
	for (int i = 0; i < m; ++i) {
		isOpened[i] = false;
		scanf("%d%d%d%d", &x, &y, &k, &l);
		events[c] = Event(i, x - 1, k, l);
		c++;
		events[c] = Event(i, y, k, l);
		c++;
	}
	sort(events, events + c);

	/*for (int i = 0; i < c; ++i) {
		printf("%d %d %d %d\n", events[i].index, events[i].value, events[i].lowerBound, events[i].upperBound);
	}*/

	int result[m];
	for (int i = 0; i < m; ++i) {
		result[i] = 0;
	}
	for (int i = 0; i < c; ++i) {
		int cur = events[i].index;
		if (cur == isElement) {
			add(events[i].lowerBound, 1);
			continue;
		}
		if (!isOpened[cur]) {
			isOpened[cur] = true;
			result[cur] -= sum(events[i].lowerBound, events[i].upperBound);
		}
		else {
			result[cur] += sum(events[i].lowerBound, events[i].upperBound);
		}
	}
	for (int i = 0; i < m; ++i) {
		printf("%d\n", result[i]);
	}
	return 0;
}