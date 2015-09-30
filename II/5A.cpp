#include <iostream>
#include <math.h>
#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;

int const maxTextLength = 1000000;
int const maxWordLength = 30;
int const maxAllWordLength = 100000;
int const notFilled = -1;
int const root = 0;

static int size;
static int M;
static char text[maxTextLength + 1];
static char word[maxAllWordLength + 1];

static int ne[maxAllWordLength + 1][maxWordLength + 1];
static int parent[maxAllWordLength + 1];
static char parentSymbol[maxAllWordLength + 1];
static int sufLink[maxAllWordLength + 1];
static int go[maxAllWordLength + 1][maxWordLength + 1];
static bool isLeaf[maxAllWordLength + 1];
static int closestLeaf[maxAllWordLength + 1];
static int id[maxAllWordLength + 1];

static bool wordIsInText[maxAllWordLength + 1];

void resetNextAndGo()
{
	for (int j = 0; j <= maxWordLength; ++j) {
		ne[size][j] = notFilled;
		go[size][j] = notFilled;
	}
}

void addWord (char* word, int idValue) {
	int v = root;
	int strLength = strlen(word);
	for (int i = 0; i < strLength; ++i) {
		int c = word[i]-'a';
		if (ne[v][c] == notFilled) {
			resetNextAndGo();
			sufLink[size] = notFilled;
			closestLeaf[size] = notFilled;
			parent[size] = v;
			parentSymbol[size] = c;
			ne[v][c] = size;
			size++;
		}
		v = ne[v][c];
	}
	isLeaf[v] = true;
	id[v] = idValue;
}


int getGo(int v, char c);

int getSufLink(int v)
{
	if (sufLink[v] == notFilled) {
		if (v == root || parent[v] == root)
			sufLink[v] = root;
		else
			sufLink[v] = getGo(getSufLink(parent[v]), parentSymbol[v]);
	}
	return sufLink[v];
}

int getGo(int v, char c)
{
	if (go[v][(int)c] == notFilled) {
		if (ne[v][(int)c] != notFilled) {
			go[v][(int)c] = ne[v][(int)c];
		}
		else {
			if (v == root)
				go[v][(int)c] = root;
			else
				go[v][(int)c] = getGo(getSufLink(v), c);
		}
	}
	return go[v][(int)c];
}


int getClosestLeaf(int v)
{
	if (closestLeaf[v] == notFilled) {
		if (isLeaf[getSufLink(v)]) {
			closestLeaf[v] = getSufLink(v);
		}
		else
			if (getSufLink(v) == root) {
				closestLeaf[v] = root;
			}
			else
			{
				closestLeaf[v] = getClosestLeaf(getSufLink(v));
			}
	}
	return closestLeaf[v];
}


int main()
{
	freopen("dictionary.in", "rt", stdin);
	freopen("dictionary.out", "wt", stdout);

	parent[root] = sufLink[root] = closestLeaf[root] = notFilled;

	for (int i = 0; i < maxWordLength; ++i) {
		ne[root][i] = go[root][i] = notFilled;
	}
	size = 1;

	scanf("%s", text);
	scanf("%d", &M);

	for (int i = 0; i < M; ++i) {
		scanf("%s", word);
		addWord(word, i);
	}

	int v = root;
	int textLength = strlen(text);
	for (int i = 0; i < textLength; ++i) {
		char c = text[i];
		v = getGo(v, c - 'a');
		int k = getClosestLeaf(v);
		while (k != root) {
			closestLeaf[k] = notFilled;
			wordIsInText[id[k]] = true;
			k = getClosestLeaf(k);
		}
		if (isLeaf[v])
			wordIsInText[id[v]] = true;
	}

	//	for (unsigned i = 0; i < strlen(text); ++i) {
	//		int symbol = text[i] - 'a';
	//		unsigned index = i + 1;
	//		int n = next[root][symbol];
	//		while (n != -1) {
	//			if (isLeaf[n]) {
	//				wordIsInText[id[n]] = true;
	//			}
	//			if (index == strlen(text)) {
	//				break;
	//			}
	//			symbol = text[index] - 'a';
	//			index++;
	//			n = next[n][symbol];
	//		}
	//	}
	for (int i = 0; i < M; ++i) {
		if (wordIsInText[i])
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}