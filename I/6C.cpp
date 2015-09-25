#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

unsigned int n = 0;
unsigned int a = 0;
unsigned int b = 0;
unsigned long long dist = 0;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
  unsigned long long c;
  while ( a != 0 ) {
     c = a; 
     a = b % a;  
     b = c;
  }
  return b;
}

unsigned int cur = 0;
unsigned int nextRand24()
{
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32()
{
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

int main()
{
	cin >> n >> a >> b;
	unsigned int points[n];
	for (int i = 0; i < n; ++i) {
		points[i] = nextRand32();
		//cout << i << ":" << points[i] << endl;
	}
	nth_element(points, points + n / 2, points + n);
	dist = 0;
	for (int i = 0; i < n; ++i) {
		/*if (i == (n / 2)) {
			continue;
		}*/
		dist += points[i];
	}
	unsigned long long d = gcd(dist, (unsigned long long)n);
	cout << (dist / d) << "/" << (n / d) << endl;
	return 0;
}