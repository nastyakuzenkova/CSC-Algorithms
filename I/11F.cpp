#include <cstdio>
#include <iostream>
#include <cassert>
#include <climits>
#include <cstdlib>

using namespace std;

typedef unsigned long long ull;

struct Treap 
{
	int value;
	int prior;
	int count;
	Treap *left;
	Treap *right;
	ull sum;
	bool rev;
	Treap() : left(NULL), right(NULL), count(0), sum(0), rev(false) {}
};

Treap *root;
int n = 0;

ull sum(Treap *&treap) {
	if (treap)
		return treap->sum;
	return 0;
}

void updateSum(Treap *&treap) {
	if (treap)
		treap->sum = treap->value + sum(treap->left) + sum(treap->right);
}

int count(Treap *&treap) {
	if (treap)
		return treap->count;
	return 0;
}

void updateCount(Treap *&treap) {
	if (treap)
		treap->count = 1 + count(treap->left) + count(treap->right);
}

Treap *createTreap(int value, int prior, Treap *l, Treap *r) {
	Treap *treap = new Treap();
	treap->value = value;
	treap->prior = prior;
	treap->left = l;
	treap->right = r;
	treap->count = 1 + count(l) + count(r);
	treap->sum = value + sum(l) + sum(r);
	treap->rev = false;
	return treap;
}

void push(Treap *&treap) {
	if(treap && treap->rev) {
		Treap *t = treap->left;
		treap->left = treap->right;
		treap->right = t;

		if(treap->left)
			treap->left->rev^=true;
		if(treap->right)
			treap->right->rev^=true;
		treap->rev = false;
	}
}

void merge(Treap *&t, Treap *l, Treap *r) {
	push(l);
	push(r);
	if(!l)
		t = r;
	else
		if(!r)
			t = l;
		else
			if(l->prior < r->prior) {
				t = l;
				merge(l->right, l->right, r);
			}
			else
			{
				t = r;
				merge(r->left, l, r->left);
			}
	updateCount(t);
	updateSum(t);
}

void split(Treap *t, int pos, Treap *&l, Treap *&r) {
	if(!t)
		l = r = NULL;
	else {
		push(t);
		if (pos <= count(t->left)) {
			split(t->left, pos, l, t->left);
			r = t;
		}
		else {
			split(t->right, pos - count(t->left) - 1, t->right, r);
			l = t;
		}
		updateCount(t);
		updateSum(t);
	}
}

void print(Treap *&t) {
	if(!t)
		return;
	print(t->left);
	printf("%d", t->value);
	print(t->right);
}

void insert(int pos, int val) {
	if(pos < 0 || pos > n)
		return;
	Treap *q = createTreap(val, rand()<<15|rand(), NULL, NULL);
	Treap *tl;
	Treap *tr;
	split(root, pos, tl, tr);
	merge(tl, tl, q);
	merge(root, tl, tr);
	++n;
}

ull sum(Treap *&t, int l, int r)
{
	Treap *tl;
	Treap *tr;
	split(t, r + 1, t, tr);
	split(t, l, tl, t);

  	ull result = sum(t);
  	
  	merge(t, tl, t);
  	merge(t, t, tr);
  	return result;
}

void reverse(Treap *&t, int l, int r) {
	if(l > r)
		return;
	Treap *tl, *tr;
	split(t, r + 1, t, tr);
	split(t, l, tl, t);
	
	t->rev^=true;
	
	merge(t, tl, t);
	merge(t, t, tr);
}

int main()
{
	srand(2097593);
  	#define NAME "reverse"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	int n0, m;
  	scanf("%d%d", &n0, &m);
  	for (int i = 0; i < n0; ++i) {
  		int cur;
  		scanf("%d", &cur);
  		insert(i, cur);
  	}
  	for (int i = 0; i < m; ++i) {
  		int q, l, r;
  		scanf("%d%d%d", &q, &l, &r);
  		l--;
  		r--;
  		if (q == 0) {
  			printf("%lld\n", sum(root, l, r));
  		}
  		else {
  			reverse(root, l, r);
  		}
  	}

  	return 0;
}