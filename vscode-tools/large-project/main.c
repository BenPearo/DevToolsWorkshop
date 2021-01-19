#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[])
{
    treeNode *root = NULL;

    word *wordList = malloc(sizeof(word) * 2045);

    char *contents = parseFile("data_7.txt");
    fixNewLines(contents);

    char *token;
    token = strtok(contents, " ");

    int i = 1;
    int foundIt = 0; // 0 for false, 1 for true
    while (token != NULL)
    {
        for (int j = 1; j < i; j++)
        {
            if (strcmp(wordList[j].item, token) == 0)
            {
                wordList[j].count++;
                foundIt = 1;
            }
        }
        if (foundIt == 0)
        {
            wordList[i].item = malloc(strlen(token));
            strcpy(wordList[i].item, token);
            wordList[i].count = 1;
            i++;
        }
        foundIt = 0;
        token = strtok(NULL, " ");
    }

    insertionSortArray(wordList, N + 1);

    double P[i];

    for (int j = 1; j <= i; j++)
    {
        P[j] = ((double)wordList[j].count / 2045);
    }

    char searchString[20];
    printf("Enter a key: ");
    scanf("%s", searchString);

    dynamic(&root, P, wordList, N);
    search(root, searchString);

    return 0;
}

void fixNewLines(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
        {
            str[i] = ' ';
        }
    }
}

char *parseFile(char *fileName)
{

    FILE *file;
    char *buffer, c;
    int fileSize, index;

    if (fileName == NULL || strcmp(fileName, "") == 0)
    {
        printf("Not a valid file name\n");
        return NULL;
    }

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Could not open file %s\n", fileName);
        return NULL;
    }

    // finding size of file for malloc
    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    // +1 for null terminator
    buffer = malloc((fileSize + 1) * sizeof(char));

    index = 0;
    while ((c = fgetc(file)) != EOF)
    {
        buffer[index++] = c;
    }
    buffer[index] = '\0';

    fclose(file);
    return buffer;
}

void insertionSortArray(word *toSort, int n)
{
    int i, j;
    word key;
    for (i = 2; i < n; i++)
    {
        key = toSort[i];
        j = i - 1;

        while (j >= 1 && strcmp(key.item, toSort[j].item) < 0)
        {
            toSort[j + 1] = toSort[j];
            j = j - 1;
        }
        toSort[j + 1] = key;
    }
}