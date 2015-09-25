#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using std::vector;
using std::nth_element;
using std::cin;
using std::cout;
using std::ios_base;

const double eps = 1E-7;

struct Jewel
{
    int index;
    double value;
    double weight;

    double jewelParameter(double x) const {
        return value - x * weight;
    }
};

class JewelCompare {
  double value;
public:
  explicit JewelCompare(double value): value(value) {}
  bool operator() (const Jewel &first, const Jewel &second) const {
     return first.jewelParameter(value) > second.jewelParameter(value);
  }
};

double getUpperBound(vector <Jewel> const &jewels) {
    double maxValue = 0;
    for (int i = 0; i < jewels.size(); ++i) {
        maxValue += jewels[i].value;
    }
    return maxValue;
}

vector <int> getInitialAnswer(vector <Jewel> const &jewels, int resultSize) {
    vector <int> initialAnswer;
    for (int i = 0; i < resultSize; ++i) {
        initialAnswer.push_back(jewels[i].index);
    }
    return initialAnswer;
}

bool canGet(vector <Jewel> &jewels, int resultSize, double
currentValue, vector <int> &answer) {

    nth_element(jewels.begin(), jewels.begin() + resultSize, jewels.end(), JewelCompare(currentValue));
    
    double sum = 0;
    for (int i = 0; i < resultSize; ++i) {
        sum += jewels[i].jewelParameter(currentValue);
    }

    if (sum >= eps) {
        answer.clear();
        for (int i = 0; i < resultSize; ++i) {
            answer.push_back(jewels[i].index);
        }

        return true;
    }

    return false;
}

vector <int> getBestJewels(vector <Jewel> jewels, int resultSize) {
    double upperBound = getUpperBound(jewels);
    vector<int> answer = getInitialAnswer(jewels, resultSize);
    
    if (canGet(jewels, resultSize, upperBound, answer)) {
        return answer;
    }
    double l = 0;
    double r = upperBound;
    while (r - l > eps) {
        double mid = l + (r - l) / 2.0;
        if (canGet(jewels, resultSize, mid, answer)) {
            l = mid + eps;
        }
        else {
            r = mid;
        }
    }
    return answer;
}

int main()
{
    ios_base::sync_with_stdio(false);
#define NAME "kbest"
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
    int inputSize = 0;
    int resultSize = 0;
    cin >> inputSize >> resultSize;

    vector <Jewel> jewels = vector <Jewel>(inputSize);
    for (int i = 0; i < inputSize; ++i) {
        cin >> jewels[i].value >> jewels[i].weight;
        jewels[i].index = i + 1;
    }

    vector <int> answer = getBestJewels(jewels, resultSize);
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] << " ";
    }

#undef NAME
    return 0;
}