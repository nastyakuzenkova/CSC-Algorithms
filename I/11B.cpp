#include <cstdio>
#include <iostream>
#include <cassert>
#include <climits>
#include <cstdlib>

using namespace std;

struct Treap 
{
	int value;
	int prior;
	int count;
	Treap *left;
	Treap *right;
	Treap() : left(NULL), right(NULL), count(1) {}
};

Treap *root;

int count(Treap *&treap) {
	if (treap)
		return treap->count;
	return 0;
}

void updateCount(Treap *&treap) {
	if (treap)
		treap->count = 1 + count(treap->left) + count(treap->right);
}

int kth(Treap *t, int k)
{
	if (!t) {
		return -1;
	}
	if (k == count(t->left)) {
		return t->value;
	}
	else if (k < count(t->left)) {
		return kth(t->left, k);
	}
	else {
		//cout << "kth:" << ((t->right) ? t->right->value : 0) << endl;
		return kth(t->right, k - count(t->left) - 1);
	}
}

Treap *createTreap(int value, int prior, Treap *l, Treap *r) {
	Treap *treap = new Treap();
	treap->value = value;
	treap->prior = prior;
	treap->left = l;
	treap->right = r;
	treap->count = 1 + count(l) + count(r);
	return treap;
}

void merge(Treap *&t, Treap *l, Treap *r) {
	if(!l || !r) {
		t = l ? l : r;
	}
	else if (l->prior > r->prior) {
		merge(l->right, l->right, r);
		//updateCount(l);
		t = l;		
	}
	else {
		merge(r->left, l, r->left);
		//updateCount(r);
		t = r;
	}
	updateCount(t);
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
		updateCount(t);
	}
}

void print(Treap *&t) {
	if(!t)
		return;
	print(t->left);
	cout << count(t) <<' ';
	print(t->right);
}

void insert(int val) {
	Treap *q = createTreap(val, rand()<<15|rand(), NULL, NULL);
	Treap *tl;
	Treap *tr;
	split(root, val, tl, tr);
	merge(tl, tl, q);
	merge(root, tl, tr);
	updateCount(root);
}

void remove(Treap *&t, int val) {
	if (t->value == val) {
		merge(t, t->left, t->right);
	}
	else
		remove(((val > t->value) ? t->left : t->right), val);
	updateCount(t);
}

void remove(int val) {
	remove(root, val);
}

int main()
{
	srand(2097593);
  	#define NAME "kthmax"
  	assert(freopen(NAME ".in", "r", stdin));
  	assert(freopen(NAME ".out", "w", stdout));
  	int n0;
  	cin >> n0;
  	for (int i = 0; i < n0; ++i) {
  		int command;
  		cin >> command;
  		if (command == 1) {
  			int elem;
  			cin >> elem;
  			insert(elem);
  			//print(root);
  			//cout << endl;
  		}
  		else if (command == -1) {
  			int key;
  			cin >> key;
  			remove(key);
  			//print(root);
  			//cout << endl;
  		}
  		else {
  			int k;
  			cin >> k;
  			cout << kth(root, k - 1) << endl;
  		}
  		//cout << "n=" << n << endl;
  	}

  	return 0;
}