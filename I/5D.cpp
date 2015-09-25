#include <iostream>
#include <climits>
#include <queue>

using namespace std;

long const infty = LONG_MIN;
long a[1000000];
long const notSet = LONG_MIN;

struct Node {
    long m;
    long added;
    Node() : added(notSet) {};
};


Node tree[4000000];

int nearest(int n) {
    int nLength = 1;
    while (nLength < n) {
        nLength *= 2;
    }
    return nLength;
}

long findMaxRec(Node* tree, int l, int r, int left, int right, int currentNode)
{
    if (l > r) {
        return infty;
    }
    if (l == left && r == right) {
        return tree[currentNode].m;
    }
    int middle = (left + right) / 2;
    int newR = middle < r ? middle : r;
    int newL = (middle + 1) > l ? (middle + 1) : l;
    long rootAdd = (tree[currentNode].added == notSet) ? 0 : tree[currentNode].added;
    return rootAdd + max(findMaxRec(tree, l, newR, left, middle, 2 * currentNode)
               , findMaxRec(tree, newL, r, middle + 1, right, 2 * currentNode + 1));
}

void update(Node* tree, int l, int r, int left, int right, int currentNode, int add) 
{
    if (l > r)
        return;
    if (l == left && r == right) {
        tree[currentNode].added = (tree[currentNode].added == notSet)
        ? add : (tree[currentNode].added + add);
        tree[currentNode].m += add;
        int index = currentNode;
        while(index / 2 != 0) {
        index = index / 2;
        tree[index].m = max(tree[2 * index].m, tree[2 * index + 1].m);
        }
    }
    else {
        if (tree[currentNode].added != notSet) {
            tree[2 * currentNode].m += tree[currentNode].added;
            tree[2 * currentNode + 1].m += tree[currentNode].added;

            tree[2 * currentNode].added = (tree[2 * currentNode].added == notSet)
            ? (tree[currentNode].added) : (tree[2 * currentNode].added + tree[currentNode].added);
            tree[2 * currentNode + 1].added = (tree[2 * currentNode + 1].added == notSet)
            ? (tree[currentNode].added) : (tree[2 * currentNode + 1].added + tree[currentNode].added);

            tree[currentNode].added = notSet;
        }
        int middle = (left + right) / 2;
        int newR = middle < r ? middle : r;
        int newL = (middle + 1) > l ? (middle + 1) : l;
        update(tree, l, newR, left, middle, 2 * currentNode, add);
        update(tree, newL, r, middle + 1, right, 2 * currentNode + 1, add);
    }
}

void printTree(Node* tree, int n, int current) {
    if (current > n) {
        return;
    }
    cout << ((tree[current].m == notSet) ? 0 : tree[current].m) << " " << ((tree[current].added == notSet) ? 0 : tree[current].added) << endl;
    printTree(tree, n, current * 2);
    printTree(tree, n, current * 2 + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n = 0;
    int q = 0;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int nLength = nearest(n);
    for (int i = n; i < nLength; ++i) {
        a[i] = infty;
    }

    for (int i = nLength; i < 2 * nLength; ++i) {
        tree[i].m = a[i - nLength];
    }
    for (int i = nLength - 1; i > 0; --i) {
        tree[i].m = max(tree[2 * i].m, tree[2 * i + 1].m);
    }
    tree[0].m = infty;
    queue<long> answers;
    for (int i = 0; i < q; ++i) {
        string request;
        cin >> request;
        if (request == "max") {
            int l = 0;
            int r = 0;
            cin >> l >> r;
            long result = findMaxRec(tree, l, r, 1, nLength, 1);
            answers.push(result);
        }
        else if (request == "add") {
            int l, r, add;
            cin >> l >> r >> add;
            update(tree, l, r, 1, nLength, 1, add);
            //printTree(tree, 2 * nLength, 1);
            //cout << "-------------" << endl;
        }
    }
    while (!answers.empty()) {
        cout << answers.front() << endl;
        answers.pop();
    }
    return 0;
}