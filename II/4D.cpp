#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

int const c = 37;

long long getHash(long long *hash, int l, int r) 
{
	long long result = hash[r];
	if (l > 0) {
		result -= hash[l - 1];
	}
	return result;
}

int main()
{	
	freopen("substrcmp.in","rt",stdin);
	freopen("substrcmp.out","wt",stdout);

	string str;
	getline(cin, str);

	int N;
	scanf("%d", &N);

	int n = str.length();
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

	int a, b, c, d;
	for(int i = 0; i < N; ++i) 
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		--a; 
		--b; 
		--c; 
		--d;
		if((b - a) != (d - c)) {
			printf("No\n");
		} else if(getHash(hash, a, b) * hash_pow[c] == getHash(hash, c, d) * hash_pow[a]) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
}

