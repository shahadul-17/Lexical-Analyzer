#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>

#define LENGTH 256      // will be changed as needed...

char specialCharacters[LENGTH], literals[LENGTH][LENGTH];

struct KeyValuePair
{
    char key[LENGTH], value[LENGTH];
};

int getLength(const char *);
int getLines(FILE *);
void loadLiterals(FILE *);
void splitKeyValue(char, const char *, int, struct KeyValuePair []);
void loadDictionary(struct KeyValuePair [], FILE *);
char compareStrings(const char *, const char *);
char compareCharacterToString(char, const char *);
void copyString(char [], const char *, int);
char isSpecialCharacter(char);
int indexOfSingleCharacterKey(char, int, struct KeyValuePair []);
int indexOfKey(char [], int, struct KeyValuePair []);

#endif
