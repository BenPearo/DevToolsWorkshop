#ifndef MAIN_H
#define MAIN_H

#define N 600
typedef struct treeNode
{
    char *key;
    int count;
    double prob;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef struct word
{
    char *item;
    int count;
} word;

void fixNewLines(char *str);
char *parseFile(char *fileName);

int dynamic(treeNode **root, double *P, word *wordList, int n);
void printTable(int *table[], int size1, int size2);

int nodeCount(treeNode *node);
void initialize(treeNode **root, char *fileContents);
void traverse(treeNode *node, int *P, int *index);

treeNode *insert(treeNode *root, int i, int j, int rootTable[][N], double mainTable[][N], word *wordList);
treeNode *newNode(char *key, int count, double prob);
treeNode *search(treeNode *root, char *key);

void insertionSortArray(word *toSort, int n);

#endif