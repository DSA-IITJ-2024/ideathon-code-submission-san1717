#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize a new trie node
TrieNode *createNode()
{
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->isEndOfWord = 0;
    for (int i = 0; i < 128; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Insert a keyword into the keyword trie
void insertKeyword(TrieNode *root, const char *keyword)
{
    TrieNode *current = root;
    for (int i = 0; keyword[i] != '\0'; i++)
    {
        int index = (int)keyword[i];
        if (!current->children[index])
        {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

// Insert an operator into the operator trie
void insertOperator(TrieNode *root, const char *operatorStr)
{
    TrieNode *current = root;
    for (int i = 0; operatorStr[i] != '\0'; i++)
    {
        int index = (int)operatorStr[i];
        if (!current->children[index])
        {
            current->children[index] = createNode();
            if (current->children[index] == NULL)
            {
                printf("Memory allocation failed\n");
                return;
            }
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

// Check if a token exists in the trie
int searchToken(TrieNode *root, const char *token)
{
    TrieNode *current = root;
    for (int i = 0; token[i] != '\0'; i++)
    {
        int index = (int)token[i];
        if (!current->children[index])
        {
            return 0;
        }
        current = current->children[index];
    }
    return (current != NULL && current->isEndOfWord);
}

// Free memory allocated for the trie
void freeTrie(TrieNode *root)
{
    if (root)
    {
        for (int i = 0; i < 128; i++)
        {
            if (root->children[i])
            {
                freeTrie(root->children[i]);
            }
        }
        free(root);
    }
}