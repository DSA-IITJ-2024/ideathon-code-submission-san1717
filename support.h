#ifndef SUPPORT_H
#define SUPPORT_H

int isCharConstant(const char *token);
int isOperatorChar(char c);
int isValidFloat(const char *token);
int isValidNumberChar(char c);
int isWhitespace(char c);
int isValidIdentifier(const char *token);
int isValidInteger(const char *token);

#endif