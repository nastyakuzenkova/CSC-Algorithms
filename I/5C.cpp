#include <cstdio>
#include <stack>
#include <iostream>

using namespace std;

struct Request {
    string command;
    int a;
    int b;

    Request(string const &c, int const &ia, int const &ib)
    : command(c), a(ia), b(ib)
    {};
    Request(){};
};

stack<Request> requests;

int find(int* p, int a) {
    if (p[a] != a) {
        p[a] = find(p, p[a]);
    }
    return p[a];
}

void unite(int* p, int* rank, int a, int b) {
    int pa = find(p, a);
    int pb = find(p, b);
    if(pa == pb) {
        return;
    }
    if (rank[pa] > rank[pb]) {
        p[pb] = pa;
    }
    else {
        p[pa] = pb;
        if (rank[pa] == rank[pb]) {
            rank[pa] = rank[pa] + 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    int p[n + 1];
    int rank[n + 1];
    for (int i = 0; i <= n; ++i) {
        p[i] = i;
        rank[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
    }

    for (int i = 0; i < k; ++i) {
        string command;
        int a, b;
        cin >> command >> a >> b;
        requests.push(Request(command, a, b));
    }

    stack<bool> answers;

    while (!requests.empty()) {
        Request current = requests.top();
        if (current.command == "ask") {
            answers.push(find(p, current.a) == find(p, current.b));
        }
        else if (current.command == "cut") {
            unite(p, rank, current.a, current.b);
        }
        requests.pop();
    }
    while (!answers.empty()) {
        string result = (answers.top() ? "YES" : "NO");
        cout << result << endl;
        answers.pop();
    }
    return 0;
}