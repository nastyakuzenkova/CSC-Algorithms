#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

struct Number {
	string n;

	bool operator < (Number const &number) const {
		return (n + number.n < number.n + n);
	}

};

Number numbers[100];

int main()
{
	string str;
	int i = 0;
	while (cin >> numbers[i].n) {
		++i;
	}
	sort(numbers, numbers + i);
	for (int j = 0; j < i; ++j) {
		cout << numbers[i - j - 1].n;
	}
	return 0;
}