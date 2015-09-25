#include <iostream>
#include <climits>
#include <queue>

using namespace std;

typedef unsigned long long ull;

ull const infty = 0;
ull const notSet = -1;

struct Node {
    ull sum;
    ull set;
    Node() : sum(0), set(notSet) {};
};


Node tree[4000000];

int nearest(int n) {
    int nLength = 1;
    while (nLength < n) {
        nLength *= 2;
    }
    return nLength;
}

ull findSumRec(int l, int r, int left, int right, int currentNode)
{
    if (l > r) {
        return infty;
    }
    if (l == left && r == right) {
        if (tree[currentNode].set != notSet) {
            return tree[currentNode].set * (r - l + 1);
        }
        return tree[currentNode].sum;
    }
    if (tree[currentNode].set != notSet) {
            
        tree[2 * currentNode].set = tree[currentNode].set;
        tree[2 * currentNode + 1].set = tree[currentNode].set;
        tree[2 * currentNode].sum = tree[currentNode].sum / 2;
        tree[2 * currentNode + 1].sum = tree[currentNode].sum / 2;
            
        tree[currentNode].set = notSet; 
    }
    int middle = (left + right) / 2;
    int newR = middle < r ? middle : r;
    int newL = (middle + 1) > l ? (middle + 1) : l;

    return findSumRec(l, newR, left, middle, 2 * currentNode) + 
           findSumRec(newL, r, middle + 1, right, 2 * currentNode + 1);
}

void update(int l, int r, int left, int right, int currentNode, ull set) 
{
    if (l > r)
        return;
    if (l == left && r == right) {
        tree[currentNode].set = set;
        tree[currentNode].sum = set * (r - l + 1);
        int index = currentNode;
        while(index / 2 != 0) {
        index = index / 2;
        tree[index].sum = tree[2 * index].sum + tree[2 * index + 1].sum;
        }
    }
    else {
        int middle = (left + right) / 2;
        int newR = middle < r ? middle : r;
        int newL = (middle + 1) > l ? (middle + 1) : l;
        if (tree[currentNode].set != notSet) {
            
            tree[2 * currentNode].set = tree[currentNode].set;
            tree[2 * currentNode + 1].set = tree[currentNode].set;
            tree[2 * currentNode].sum = tree[currentNode].sum / 2;
            tree[2 * currentNode + 1].sum = tree[currentNode].sum / 2;
            
            tree[currentNode].set = notSet; 
        }
        update(l, newR, left, middle, 2 * currentNode, set);
        update(newL, r, middle + 1, right, 2 * currentNode + 1, set);
    }
}

void printTree(int n, int current) {
    if (current > n) {
        return;
    }
    cout << current << ":" << tree[current].sum << " " << tree[current].set << endl;
    printTree(n, current * 2);
    printTree(n, current * 2 + 1);
}

int main()
{
    int n = 0;
    int q = 0;
    cin >> n >> q;
    int nLength = nearest(n);
    //printTree(2 * nLength, 1);
    queue<ull> answers;
    for (int i = 0; i < q; ++i) {
        char request;
        cin >> request;
        if (request == 'Q') {
            int l = 0;
            int r = 0;
            cin >> l >> r;
            ull result = findSumRec(l, r, 1, nLength, 1);
            answers.push(result);
        }
        else if (request == 'A') {
            int l, r;
            ull set;
            cin >> l >> r >> set;
            update(l, r, 1, nLength, 1, set);
            //printTree(2 * nLength, 1);
            //cout << "--------" << endl;
        }
    }
    while (!answers.empty()) {
        cout << answers.front() << endl;
        answers.pop();
    }
    return 0;
}