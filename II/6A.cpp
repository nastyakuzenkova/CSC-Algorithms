#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstring>

using namespace std;

int const maxN = 1E5;
char *str;

int n, s;
int suffarray[maxN + 1];
int pos[maxN + 1];
int lcp[maxN + 1];
int buffer[maxN + 1];

bool comp(int x, int y)
{
	if (pos[x] != pos[y]) {
		return pos[x] < pos[y];
	}
	x += s;
	y += s;
	if (x < n && y < n) {
		return pos[x] < pos[y];
	}

	return x > y;
}

int main()
{
	freopen("suffarray.in", "rt", stdin);
	freopen("suffarray.out", "wt", stdout);
	string temp;
	getline(cin, temp);
	str = (char*)temp.c_str();
	n = strlen(str);
	for (int i = 0; i < n; ++i) {
		suffarray[i] = i;
		pos[i] = str[i];
	}

	for (s = 1;;s *= 2) {
		sort(suffarray, suffarray + n, comp);
		for (int i = 0; i < n - 1; ++i) {
			buffer[i + 1] = buffer[i] + comp(suffarray[i], suffarray[i + 1]);
		}

		for (int i = 0; i < n; ++i) {
			pos[suffarray[i]] = buffer[i];
		}

		if (buffer[n - 1] == n - 1) {
			break;
		}
	}

	for (int i = 0; i < n; ++i) {
		printf("%d ", suffarray[i] + 1);
	}

	return 0;
}