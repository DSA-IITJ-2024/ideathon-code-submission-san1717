#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode
{
    struct TrieNode *children[128]; // Assuming ASCII characters
    int isEndOfWord;
} TrieNode;

TrieNode *createNode();
void insertKeyword(TrieNode *root, const char *keyword);
void insertOperator(TrieNode *root, const char *operatorStr);
int searchToken(TrieNode *root, const char *token);
void freeTrie(TrieNode *root);

#endif