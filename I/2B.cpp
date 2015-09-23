#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

struct Team {
	int i;
	int s;
	int t;
	
	Team() {};
	Team(int i_i, int i_s, int i_t): i(i_i), s(i_s), t(i_t) {};

	bool operator < (const Team& team) const { 
    	return (s < team.s || (s == team.s && t > team.t) || (s == team.s && t == team.t && i > team.i)); 
    }
};

Team teams[100000];

int main()
{
	int n = 100000;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int s = 0;
		int t = 0;
		scanf("%d %d", &s, &t);
		teams[i] = Team(i + 1, s, t);
	}
	sort(teams, teams + n);
	for (int i = n - 1; i >= 0; --i) {
		printf("%d ", teams[i].i);
	}
	return 0;
}