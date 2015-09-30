#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() 
{
    freopen("palindrome.in", "rt", stdin);
    freopen("palindrome.out", "wt", stdout);
    string s; 
    cin >> s;
    if (s.empty()) {
        return 0;
    }

    int n = s.size();

    int s1[n];
    int s2[n];
    int left = 0;
    int right = -1;

    for (int i = 0; i < n; ++i) {
        int j = 1;
        if (i <= right) {
            j = min(s1[left + right - i], right - i);
        }
        while (i + j < n && i - j >= 0 && s[i - j] == s[i + j]) {
            ++j;
        }
        s1[i] = j--;
        if (i + j > right) {
            left = i - j;
            right = i + j;
        }
    }

    left = 0;
    right = -1;

    for (int i = 0; i < n; ++i) {
        int j = 1;
        if (i <= right) {
            j = min(s2[left + right - i + 1], right - i + 1) + 1;
        }
        while (i + j - 1 < n && i - j >= 0 && s[i - j] == s[i + j - 1]) {
            ++j;
        }

        s2[i] = --j;
        if (i + j - 1 > right) {
            left = i - j;
            right = i + j - 1;
        }
    }

    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        if (s1[i] <= 0) {
            answer += s2[i];
        }
        else {
            answer += s1[i] + s2[i] - 1;
        }
    }

    cout << answer;

    return 0;
}