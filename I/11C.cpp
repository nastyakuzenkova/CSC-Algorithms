#include <cstdio>
#include <iostream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <math.h>

using namespace std;

typedef unsigned long long ull;

struct Treap 
{
	int value;
	int prior;
	Treap *left;
	Treap *right;
	ull sum;
	Treap() : left(NULL), right(NULL), sum(0) {}
};

Treap *root;

ull sum(Treap *&treap) {
	if (treap)
		return treap->sum;
	return 0;
}

void updateSum(Treap *&treap) {
	if (treap)
		treap->sum = treap->value + sum(treap->left) + sum(treap->right);
}

bool hasVal(Treap *t, int val) {
	if (!t) {
		return false;
	}
	if (t->value == val) {
		return true;
	}
	if (t->value < val) {
		return hasVal(t->left, val);
	}
	else {
		return hasVal(t->right, val);
	}
}

Treap *createTreap(int value, int prior, Treap *l, Treap *r) {
	Treap *treap = new Treap();
	treap->value = value;
	treap->prior = prior;
	treap->left = l;
	treap->right = r;
	treap->sum = value + sum(l) + sum(r);
	return treap;
}

void merge(Treap *&t, Treap *l, Treap *r) {
	if(!l || !r) {
		t = l ? l : r;
	}
	else if (l->prior > r->prior) {
		merge(l->right, l->right, r);
		t = l;		
	}
	else {
		merge(r->left, l, r->left);
		t = r;
	}
	updateSum(t);
}

void split(Treap *t, int val, Treap *&l, Treap *&r) {
	if(!t)
		l = r = NULL;
	else {
		if (t->value <= val) {
			split(t->left, val, l, t->left);
			r = t;
		}
		else {
			split(t->right, val, t->right, r);
			l = t;
		}
	updateSum(t);
	}
}

void print(Treap *&t) {
	if(!t)
		return;
	print(t->left);
	cout << t->value <<' ';
	print(t->right);
}

void insert(int val) {
	if (hasVal(root, val)) {
		return;
	}
	Treap *q = createTreap(val, rand()<<15|rand(), NULL, NULL);
	Treap *tl;
	Treap *tr;
	split(root, val, tl, tr);
	merge(tl, tl, q);
	merge(root, tl, tr);
	updateSum(root);
}


ull sum(Treap *&t, int l, int r)
{
	Treap *tl;
	Treap *tr;
	split(t, r, tr, t);
	split(t, l - 1, t, tl);
	//print(t);
	//cout << endl;
  	ull result = sum(t);
  	merge(t, t, tl);
  	merge(t, tr, t);

  	return result;
}

int main()
{
	srand(2097593);
  	#define NAME "sum2"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	int n0;
  	cin >> n0;
  	bool prevQ = false;
  	ull prevQResult = 0;
  	for (int i = 0; i < n0; ++i) {
  		char command;
  		cin >> command;
  		if (command == '+') {
  			int elem;
  			cin >> elem;
  			if (prevQ)
  			{
  				insert((elem + prevQResult) % (int)1E9);
  			}
  			else {
  				insert(elem);
  			}
  			prevQ = false;
  		}
  		else if (command == '?') {
  			int l, r;
  			cin >> l >> r;
  			prevQResult = sum(root, l, r);
  			cout << prevQResult << endl;
  			prevQ = true;
  		}
  	}

  	return 0;
}