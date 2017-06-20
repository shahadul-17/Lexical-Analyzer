#include "utility.h"

int getLength(const char *string)
{
    int index = 0;

    while (string[index] != '\0')
    {
        index++;
    }

    return index;
}

int getLines(FILE *file)
{
    char string[LENGTH];
    int lines = 0;

    while (!feof(file))
    {
        fscanf(file, "%s", string);
        lines++;
    }

    rewind(file);

    return lines;
}

void loadLiterals(FILE *literalsFile)
{
    int i = 0;

    while (!feof(literalsFile))
    {
        fscanf(literalsFile, "%s", literals[i]);

        i++;
    }
}

void splitKeyValue(char separator, const char *string, int index, struct KeyValuePair dictionary[])
{
    char flag = 0;
    int i = 0, j = 0, k = 0, length = getLength(string);

    while (i < length)
    {
        if (string[i] == separator)
        {
            i++;
            flag = 1;
        }

        if (flag == 0)
        {
            if (index > -1 && index < 14)
            {
                specialCharacters[index + 4] = string[i];   // adding rest of the special characters...
            }

            dictionary[index].key[j] = string[i];
            j++;
        }
        else
        {
            dictionary[index].value[k] = string[i];
            k++;
        }

        i++;
    }

    dictionary[index].key[j] = dictionary[index].value[k] = '\0';
}

void loadDictionary(struct KeyValuePair dictionary[], FILE *dictionaryFile)
{
    char string[LENGTH];
    int index = 0;

    copyString(specialCharacters, " \n\r\t", 4);    // copying 4 special characters...

    while (!feof(dictionaryFile))
    {
        fscanf(dictionaryFile, "%s", string);
        splitKeyValue('#', string, index, dictionary);      // '#' is our separator...

        index++;
    }
}

char compareStrings(const char *string_1, const char *string_2)
{
    int i = 0, length_1 = getLength(string_1), length_2 = getLength(string_2);

    if (length_1 != length_2)
    {
        return -1;
    }

    for (i = 0; i < length_1; i++)
    {
        if (string_1[i] != string_2[i])
        {
            return -1;
        }
    }

    return 0;
}

char compareCharacterToString(char character, const char *string)
{
    if (getLength(string) != 1 || character != string[0])
    {
        return -1;
    }

    return 0;
}

void copyString(char string_1[], const char *string_2, int length)
{
    int i;

    for (i = 0; i < length; i++)
    {
        string_1[i] = string_2[i];
    }

    string_1[i] = '\0';
}

char isSpecialCharacter(char character)
{
    int i = 0, length = getLength(specialCharacters);

    for (i = 0; i < length; i++)
    {
        if (specialCharacters[i] == character)
        {
            return 0;
        }
    }

    return -1;
}

int indexOfSingleCharacterKey(char key, int size, struct KeyValuePair dictionary[])
{
    int index;

    for (index = 0; index < size; index++)
    {
        if (compareCharacterToString(key, dictionary[index].key) == 0)
        {
            return index;
        }
    }

    return -1;
}

int indexOfKey(char key[], int size, struct KeyValuePair dictionary[])
{
    int index;

    for (index = 0; index < size; index++)
    {
        if (compareStrings(key, dictionary[index].key) == 0)
        {
            return index;
        }
    }

    return -1;
}
