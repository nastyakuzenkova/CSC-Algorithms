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
Node *p[maxN + 1]; 
Node *size[maxN + 1];

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

int find(Node *v, int l, int r, int a) 
{
    int pa = get(v, a, l, r);
    if (pa != a) {
        return find(v, l, r, pa);
    }
    return pa;
}

Node *unite(Node *v, int l, int r, int a, int b, Node *&size)
{
  int pa = find(v, l, r, a);
  int pb = find(v, l, r, b);
  if (pa == pb) {
    return v;
  }
  int size_pa = get(size, pa, l, r);
  int size_pb = get(size, pb, l, r);
  Node *newV;
  if (size_pa > size_pb) {
      newV = newVesion(v, l, r, pb, pa);
      size = newVesion(size, l, r, pa, size_pa + size_pb);
    }
    else {
      newV = newVesion(v, l, r, pa, pb);
      size = newVesion(size, l, r, pb, size_pa + size_pb);
    }
    return newV;
}

int main()
{
    ios_base::sync_with_stdio(false);
  	#define NAME "snm"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      a[i] = i;
    }
    p[0] = init(0, n - 1);

    for (int i = 0; i < n; ++i) {
      a[i] = 1;
    }
    size[0] = init(0, n - 1);

    int curVersion = 1;
    for (int i = 0; i < m; ++i) {
      char c;
      int j, a, b;
      scanf(" %c%d%d%d", &c, &j, &a, &b);
      a--;
      b--;
      if (c == '+') {
        size[curVersion] = size[j];
        p[curVersion] = unite(p[j], 0, n - 1, a, b, size[curVersion]);
        curVersion++;
      }
      else if (c == '?') {
        bool result = find(p[j], 0, n - 1, a) == find(p[j], 0, n - 1, b);
        if (result) {
          printf("YES\n");
        }
        else {
          printf("NO\n");
        }
        p[curVersion] = p[j];
        size[curVersion] = size[j];
        curVersion++;
      }
    }
  	return 0;
}