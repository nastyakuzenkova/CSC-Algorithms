#include <cstdio>
#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

const int maxSize = 100;

struct HTree
{
    char c;
    HTree *left;
    HTree *right;
};

HTree *create(char c)
{
    HTree *tree = new HTree;
    tree->c = c;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void addToTree(HTree *root, char c, char *code)
{
    int i = 0;
    HTree *currentNode = root;
    while (i < maxSize && code[i] != '\0')
    {
        int currentCode = code[i] - '0';
        if (currentCode == 0)
        {
            if (!currentNode->left)
                currentNode->left = create(c);
            currentNode = currentNode->left;
        }
        else if (currentCode == 1)
        {
            if (!currentNode->right)
                currentNode->right = create(c);
            currentNode = currentNode->right;
        }
        i++;
    }
}

char getChar(HTree *root, char *inputCode, int &i)
{
    HTree *temp = root;
    while (temp->left || temp->right)
    {
        if (inputCode[i] == '0')
            temp = temp->left;
        else if (inputCode[i] == '1')
            temp = temp->right;
        i++;
    }
    return temp->c;
}

int main()
{
#define NAME "decoding"
    assert(freopen(NAME ".in", "r", stdin));
    assert(freopen(NAME ".out", "w", stdout));

    int k = 0;
    int l = 0;
    scanf("%d %d\n", &k, &l);

    HTree *root = create(' ');

    char code[maxSize] = {'\0'};

    for (int i = 0; i < k; ++i) {
        char c = 0;
        memset(code, '\0', maxSize);
        scanf("%c: %s\n", &c, code);

        addToTree(root, c, code);
    }

    char *inputCode = new char[l + 1];
    memset(inputCode, '\0', l + 1);
    scanf("%s\n", inputCode);
    int i = 0;
    while (i < l && inputCode[i])
    {
        char c = getChar(root, inputCode, i);
        printf("%c", c);
    }


    return 0;
}

