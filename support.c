#include "support.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isCharConstant(const char *token)
{
    return token[0] == '\'' && token[2] == '\'' && token[3] == '\0';
}

int isOperatorChar(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '=' || c == '!' || c == '&' || c == '|';
}

int isValidFloat(const char *token)
{
    int hasDecimalPoint = 0;
    for (int i = 0; token[i] != '\0'; i++)
    {
        if (token[i] == '.')
        {
            if (hasDecimalPoint)
                return 0;
            hasDecimalPoint = 1;
        }
        else if (!isdigit(token[i]))
        {
            return 0;
        }
    }
    return hasDecimalPoint;
}

// Function to check if a character is a valid part of a number
int isValidNumberChar(char c)
{
    return isdigit(c) || c == '+' || c == '-';
}

// Function to check if a character is a whitespace
int isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Function to check if a token is a valid identifier
int isValidIdentifier(const char *token)
{
    if (!isalpha(token[0]) && token[0] != '_')
    {
        return 0; // Identifier must start with a letter or underscore
    }
    for (int i = 1; token[i] != '\0'; i++)
    {
        if (!isalnum(token[i]) && token[i] != '_')
        {
            return 0; // Invalid character in identifier
        }
    }
    return 1;
}

int isValidInteger(const char *token)
{
    if (token[0] == '-' || token[0] == '+') // Account for optional sign
        return isdigit(token[1]) && strchr(token, '.') == NULL;
    return isdigit(token[0]) && strchr(token, '.') == NULL;
}
