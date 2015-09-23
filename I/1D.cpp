#include <iostream>
 using namespace std;

int sum[40];
int N = 0;

void generateSum(int &n)
{
	int min = sum[n];
	int i = 0;
	bool found = false;
	int bound = 0;
	for (i = n - 1; i >= 0; --i) {
		if (sum[i] > min) {
			found = true;
			break;
		}
	}
	if (found) {
		for (int j = i + 1; j > 0; --j) {
			if ((sum[j - 1] <= sum[j]) || j == n) {
				continue;
			}
			sum[j]++;
			int res = 0;
			for (int t = 0; t <= j; ++t) {
				res += sum[t];
			}
			for (int k = j + 1; k <= (j + N - res); ++k) {
				sum[k] = 1;
			}
			n = N - res + j;
			return;
		}
	}
	sum[0]++;
	int max = sum[0];
	for (int j = 1; j <= (N - max); ++j) {
		sum[j] = 1;
	}
	n = N - max;
}

 int main()
 {
 	cin >> N;
 	for (int i = 0; i < N; ++i) {
 		sum[i] = 1;
 		cout << sum[i] << " ";
 	}
 	cout << endl;
 	int maxIndex = N - 1;
 	while (maxIndex > 0) {
 		generateSum(maxIndex);
 		for (int i = 0; i <= maxIndex; ++i) {
 			cout << sum[i] << " ";
 		}
 		cout << endl;
 	}
 	return 0;
 }