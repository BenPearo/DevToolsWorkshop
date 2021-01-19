#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define N 600

// implements the the dynamic programming algorithm
int dynamic(treeNode **root, double *P, word *wordList, int n)
{
    double mainTable[N + 1][N];
    int rootTable[N][N];
    int index = 0;

    for (int i = 1; i <= n; i++)
    {
        mainTable[i][i - 1] = 0;
        mainTable[i][i] = P[i];
        rootTable[i][i] = i;
    }

    mainTable[N + 1][N] = 0;

    double min;
    int kmin;
    double sum = 0;

    for (int d = 1; d < N; d++)
    {
        for (int i = 1; i <= N - d; i++)
        {
            int j = i + d;
            min = 1000000;
            for (int k = i; k <= j; k++)
            {
                if (mainTable[i][k - 1] + mainTable[k + 1][j] < min)
                {
                    min = mainTable[i][k - 1] + mainTable[k + 1][j];
                    kmin = k;
                }
            }
            rootTable[i][j] = kmin;
            sum = P[i];
            for (int s = i + 1; s <= j; s++)
                sum += P[s];
            mainTable[i][j] = min + sum;
        }
    }

    *root = insert(*root, 1, N, rootTable, mainTable, wordList);

    return 0;
}

// searches through nodes for the key
treeNode *search(treeNode *root, char *key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL)
    {
        printf("Not found.\n");
        return NULL;
    }

    printf("Compared with %s (%.2f), ", root->key, root->prob);

    if (strcmp(key, root->key) < 0)
    {
        printf("go left subtree.\n");
        return search(root->left, key);
    }

    else if (strcmp(key, root->key) > 0)
    {
        printf("go right subtree.\n");
        return search(root->right, key);
    }

    else
    {
        printf("found.\n");
        return root;
    }
}

// creates a new node, incluting the probability
treeNode *newNode(char *key, int count, double prob)
{
    treeNode *newtreeNode = malloc(sizeof(treeNode));
    newtreeNode->key = malloc(sizeof(char) * strlen(key));
    strcpy(newtreeNode->key, key);
    newtreeNode->left = NULL;
    newtreeNode->right = NULL;
    newtreeNode->count = count;
    newtreeNode->prob = prob;

    return newtreeNode;
}

// builds a tree from the root table
treeNode *insert(treeNode *root, int i, int j, int rootTable[][N], double mainTable[][N], word *wordList)
{
    int rootIndex = rootTable[i][j];

    if (i == j)
    {
        return newNode(wordList[rootIndex].item, wordList[rootIndex].count, mainTable[i][j]);
    }
    else if (i > j)
    {
        return NULL;
    }

    treeNode *node = newNode(wordList[rootIndex].item, wordList[rootIndex].count, mainTable[i][j]);
    node->left = insert(root, i, rootIndex - 1, rootTable, mainTable, wordList);
    node->right = insert(root, rootIndex + 1, j, rootTable, mainTable, wordList);
    return node;

}