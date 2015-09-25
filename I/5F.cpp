#include <iostream>
#include <stack>
#include <climits>

using namespace std;

typedef long long ll;

struct Number
{
    int i;
    ll value;

    bool operator < (Number const &num) const
    {
        return value < num.value;
    }  
};

int n;
Number a[100000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n;
    int nextj[n];
    int previousj[n];
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        a[i].value = x;
        a[i].i = i;
        nextj[i] = previousj[i] = -1;
    }

    stack<Number> numbers;
    for (int i = 0; i < n; ++i) {
        if (numbers.empty() || numbers.top().value <= a[i].value) {
            numbers.push(a[i]);
        }
        else {
            while (!numbers.empty() && (numbers.top().value > a[i].value)) {
                nextj[numbers.top().i] = i - 1;
                numbers.pop();
            }
            numbers.push(a[i]);
        }
    }
    while (!numbers.empty()) {
        numbers.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        if (numbers.empty() || numbers.top().value < a[i].value) {
            numbers.push(a[i]);
        }
        else {
            while (!numbers.empty() && numbers.top().value >= a[i].value) {
                previousj[numbers.top().i] = i + 1;
                numbers.pop();
            }
            numbers.push(a[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (previousj[i] == -1) {
            previousj[i] = 0;
        }
        if (nextj[i] == -1) {
            nextj[i] = n - 1;
        }
    }
    ll curSum = 0;
    for (int i = 0; i < n; ++i) {
        ll currentMin = a[i].value;
        int l = previousj[i];
        int r = nextj[i];
        curSum += currentMin * (i - l + 1) * (r - i + 1);
    }
    cout << curSum << endl;
    return 0;
}