#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "utility.h"

char isInteger(const char *);
char isReal(const char *);
char isCharacter(const char *);
char isHexadecimal(const char *);
char isString(const char *);
char isIdentifier(const char *);
int indexOfKeyword(const char *, int, struct KeyValuePair []);

#endif
