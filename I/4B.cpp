#include <iostream>
#include <string>

using namespace std;

string kids[100000];
int l[100000];
int r[100000];

void screamNames(int i) {
	cout << (kids[l[i]]) << " " << kids[r[i]] << endl;
	l[r[i]] = l[i];
	r[l[i]] = r[i];
}

int main()
{
	int n = 0;
	cin >> n;
	
	for (int i = 0; i < n; ++i) {
		cin >> kids[i];
	}
	l[0] = n - 1;
	r[0] = 1;

	l[n - 1] = n - 2;
	r[n - 1] = 0;
	
	for (int i = 1; i < (n - 1); ++i) {
		l[i] = i - 1;
		r[i] = i + 1;
	}

	for (int i = 0; i < (n - 3); ++i) {
		int num = 0;
		cin >> num;
		screamNames(num - 1);
	}

	return 0;
}