#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"
#include "support.h"

#define MAX_BUFFER_LEN 1024

enum State
{
    DEFAULT,
    IN_COMMENT,
    IN_STRING,
    IN_OPERATOR,
    IN_DIRECTIVE,
    IN_STRING_CONSTANT
};

void handleToken(TrieNode *keywordRoot, TrieNode *operatorRoot, const char *token, FILE *outputFile);
void processBuffer(char *buffer, TrieNode *keywordRoot, TrieNode *operatorRoot, FILE *outputFile);
void populateTries(TrieNode *keywordRoot, TrieNode *operatorRoot);

int main(int argc, char *argv[])
{
    // Open input and output files{
    if (argc < 2)
    {
        printf("Please provide an input file as an argument.\n");
        return 1;
    }

    // Open input and output files
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Create keyword and operator tries
    TrieNode *keywordRoot = createNode();
    TrieNode *operatorRoot = createNode();
    if (!keywordRoot || !operatorRoot)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Populate the tries
    populateTries(keywordRoot, operatorRoot);

    // Read input from file
    char buffer[MAX_BUFFER_LEN];
    while (fgets(buffer, MAX_BUFFER_LEN, inputFile) != NULL)
    {
        processBuffer(buffer, keywordRoot, operatorRoot, outputFile);
    }

    // Close input and output files
    fclose(inputFile);
    fclose(outputFile);

    // Free memory used by keyword and operator tries
    freeTrie(keywordRoot);
    freeTrie(operatorRoot);

    return 0;
}


void populateTries(TrieNode *keywordRoot, TrieNode *operatorRoot)
{
    insertKeyword(keywordRoot, "int");
    insertKeyword(keywordRoot, "char");
    insertKeyword(keywordRoot, "float");
    insertKeyword(keywordRoot, "if");
    insertKeyword(keywordRoot, "else");
    insertKeyword(keywordRoot, "while");
    insertKeyword(keywordRoot, "for");
    insertKeyword(keywordRoot, "return");
    insertKeyword(keywordRoot, "printf");
    insertKeyword(keywordRoot, "main");

    insertOperator(operatorRoot, "+");
    insertOperator(operatorRoot, "-");
    insertOperator(operatorRoot, "*");
    insertOperator(operatorRoot, "/");
    insertOperator(operatorRoot, "<");
    insertOperator(operatorRoot, ">");
    insertOperator(operatorRoot, "<=");
    insertOperator(operatorRoot, ">=");
    insertOperator(operatorRoot, "==");
    insertOperator(operatorRoot, "!=");
    insertOperator(operatorRoot, "=");
    insertOperator(operatorRoot, "++");
    insertOperator(operatorRoot, "--");
}


// Handle token function
void handleToken(TrieNode *keywordRoot, TrieNode *operatorRoot, const char *token, FILE *outputFile)
{
    if (searchToken(keywordRoot, token))
    {
        fprintf(outputFile, "Keyword: %s\n", token);
    }
    else if (searchToken(operatorRoot, token))
    {
        fprintf(outputFile, "Operator: %s\n", token);
    }
    else if (isValidInteger(token))
    {
        fprintf(outputFile, "Integer: %s\n", token);
    }
    else if (isValidFloat(token))
    {
        fprintf(outputFile, "Float: %s\n", token);
    }
    else if (isCharConstant(token))
    {
        fprintf(outputFile, "Character Constant: %s\n", token);
    }
    else if (strcmp(token, "(") == 0 || strcmp(token, ")") == 0 ||
             strcmp(token, "{") == 0 || strcmp(token, "}") == 0 ||
             strcmp(token, "[") == 0 || strcmp(token, "]") == 0 ||
             strcmp(token, ";") == 0 || strcmp(token, ",") == 0)
    {
        fprintf(outputFile, "Special Character: %s\n", token);
    }
    else if (isValidIdentifier(token))
    {
        fprintf(outputFile, "Identifier: %s\n", token);
    }
    else
    {
        fprintf(outputFile, "Invalid Token: %s\n", token);
    }
}

void processBuffer(char *buffer, TrieNode *keywordRoot, TrieNode *operatorRoot, FILE *outputFile)
{
    char token[MAX_BUFFER_LEN];
    int tokenLen = 0;
    enum State state = DEFAULT;

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        char c = buffer[i];

        switch (state)
        {
        case DEFAULT:
            if (c == '#')
            {
                state = IN_DIRECTIVE;
                token[tokenLen++] = c;
            }
            else if (c == '"')
            {
                state = IN_STRING_CONSTANT;
                token[tokenLen++] = c;
            }
            else
            {
                if (isWhitespace(c))
                {
                    if (tokenLen > 0)
                    {
                        token[tokenLen] = '\0';
                        handleToken(keywordRoot, operatorRoot, token, outputFile);
                        tokenLen = 0;
                    }
                }
                else if (c == '/')
                {
                    state = IN_COMMENT;
                }
                else if (c == '"')
                {
                    state = IN_STRING_CONSTANT;
                    token[tokenLen++] = c;
                }
                else if (isOperatorChar(c))
                {
                    if (tokenLen > 0)
                    {
                        token[tokenLen] = '\0';
                        handleToken(keywordRoot, operatorRoot, token, outputFile);
                        tokenLen = 0;
                    }
                    token[tokenLen++] = c;
                    if (isOperatorChar(buffer[i + 1]))
                    {
                        token[tokenLen++] = buffer[++i];
                    }
                    token[tokenLen] = '\0';
                    handleToken(keywordRoot, operatorRoot, token, outputFile);
                    tokenLen = 0;
                }
                else if (isOperatorChar(c) || c == '(' || c == ')' || c == ',' || c == ';')
                {
                    if (tokenLen > 0)
                    {
                        token[tokenLen] = '\0';
                        handleToken(keywordRoot, operatorRoot, token, outputFile);
                        tokenLen = 0;
                    }
                    token[tokenLen++] = c;
                    token[tokenLen] = '\0';
                    handleToken(keywordRoot, operatorRoot, token, outputFile);
                    tokenLen = 0;
                }
                else
                {
                    token[tokenLen++] = c;
                }
            }
            break;
        case IN_DIRECTIVE:
            if (c == '\n')
            {
                state = DEFAULT;
                token[tokenLen] = '\0';
                fprintf(outputFile, "Preprocessor Directive: %s\n", token);
                tokenLen = 0;
            }
            else
            {
                token[tokenLen++] = c;
            }
            break;
        case IN_STRING_CONSTANT:
            token[tokenLen++] = c;
            if (c == '"')
            {
                state = DEFAULT;
                token[tokenLen] = '\0';
                fprintf(outputFile, "String Constant: %s\n", token);
                tokenLen = 0;
            }
            break;
        case IN_COMMENT:
            if (c == '\n')
            {
                state = DEFAULT;
            }
            break;
        case IN_STRING:
            token[tokenLen++] = c;
            if (c == '"')
            {
                state = DEFAULT;
            }
            break;
        case IN_OPERATOR:
            if (isOperatorChar(c))
            {
                token[tokenLen++] = c;
            }
            else
            {
                state = DEFAULT;
                token[tokenLen] = '\0';
                handleToken(keywordRoot, operatorRoot, token, outputFile);
                tokenLen = 0;
            }
            break;
        }
    }

    if (tokenLen > 0)
    {
        token[tokenLen] = '\0';
        handleToken(keywordRoot, operatorRoot, token, outputFile);
    }
}
