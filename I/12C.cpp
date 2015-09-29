#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    int value;
    Node() : left(NULL), right(NULL), value(0) {}
    Node(int v) : left(NULL), right(NULL), value(v) {}
    Node(Node *l, Node *r) : left(l), right(r), value(0) {}
    ~Node() {
      if(left) { 
        delete left;
      } 
      if(right) {
        delete right;
      }
    }
};

int const maxN = 1E5;
int a[maxN];
Node *versions[maxN + 1]; 

Node *init(int l, int r)
{
  if (l == r) {
    return new Node(a[r]);
  }

  int m = (l + r) / 2;
  return new Node(init(l, m), init(m + 1, r));
}

int get(Node *v, int i, int l, int r)
{
    if (l == r) {
      return v->value;
    }    
    int m = (l + r) / 2;
    if (i <= m) {
        return get(v->left, i, l, m);      
    }
    return get(v->right, i, m + 1, r);
}

Node *newVesion(Node *v, int l, int r, int i, int value)
{
    if (l == r) {
      return new Node(value);
    }    
    int m = (l + r) / 2;
    if (i <= m) {
        return new Node(newVesion(v->left, l, m, i, value), v->right);      
    }
    return new Node(v->left, newVesion(v->right, m + 1, r, i, value));
}

int main()
{
  	#define NAME "parray"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }

    int m;
    scanf("%d", &m);
    versions[0] = init(0, n - 1);

    int curVersion = 1;
    for (int i = 0; i < m; ++i) {
      string command;
      cin >> command;
      if (command[0] == 'c') {
        int v, j, val;
        scanf("%d%d%d", &v, &j, &val);
        v--;
        j--;
        versions[curVersion] = newVesion(versions[v], 0, n - 1, j, val);
        curVersion++;
      }
      else if (command[0] == 'g') {
        int v, j;
        scanf("%d %d", &v, &j);
        v--;
        j--;
        printf("%d\n", get(versions[v], j, 0, n - 1));
      }
    }
  	return 0;
}