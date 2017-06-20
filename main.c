#include "utility.h"
#include "tokentype.h"

static char identifiers[LENGTH][LENGTH];

int indexOfIdentifier(const char *identifier)
{
    int index;

    for (index = 0; index < LENGTH; index++)
    {
        if (compareStrings(identifier, identifiers[index]) == 0)
        {
            return index;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    char lastSpecialChar = '\0';
    int scount = 0, lines = 0;

    FILE *literalsFile = fopen("literals", "r"), *dictionaryFile = fopen("dictionary", "r");

    if (literalsFile)
    {
        loadLiterals(literalsFile);
        fclose(literalsFile);
    }
    else
    {
        printf("literals could not be loaded...\n\n");

        return 4;       // error code 4 if literals could not be loaded...
    }

    if (dictionaryFile)
    {
        printf("dictionary file found...\n\nloading dictionary...\n\n");

        lines = getLines(dictionaryFile);

        struct KeyValuePair dictionary[lines];        // this will be changed to dynamic...

        loadDictionary(dictionary, dictionaryFile);
        fclose(dictionaryFile);
        printf("dictionary loaded successfully...\n\n");

        FILE *inputFile = fopen("input.txt", "r");

        if (inputFile)
        {
            printf("input file found...\n\n");

            FILE *outputFile = fopen("output.txt", "w");

            if (outputFile)
            {
                char character = '\0', token[LENGTH];
                int tempIndex = 0, indexOfLiterals = -1, index = 0, tokenLength = 0;

                printf("output file opened/created successfully...\n\n");

                while (!feof(inputFile))
                {
                    if (fscanf(inputFile, "%c", &character) == 1)
                    {
                        // here goes the logic of parsing...

                        if (character == '"')
                        {
                            if (scount == 0)
                            {
                                lastSpecialChar = character;
                                scount++;
                            }
                            else
                            {
                                lastSpecialChar = '\0';
                                scount--;
                            }
                        }

                        if (lastSpecialChar != '"' && isSpecialCharacter(character) == 0)
                        {
                            token[index] = '\0';

                            if ((tokenLength = getLength(token)) > 0)
                            {
                                if (isCharacter(token) == 0)
                                {
                                    indexOfLiterals = 0;
                                }
                                else if (isString(token) == 0)
                                {
                                    indexOfLiterals = 4;
                                }
                                else if ((index = indexOfKeyword(token, lines, dictionary)) != -1)   // added later...
                                {
                                    fprintf(outputFile, "%s ", dictionary[index].value);
                                }
                                else if (isIdentifier(token) == 0)
                                {
                                    if ((index = indexOfIdentifier(token)) == -1)
                                    {
                                        copyString(identifiers[tempIndex], token, tokenLength);
                                        fprintf(outputFile, "ID%d ", tempIndex + 1);

                                        tempIndex++;
                                    }
                                    else
                                    {
                                        fprintf(outputFile, "ID%d ", index + 1);
                                    }
                                }
                                else if (isInteger(token) == 0)
                                {
                                    indexOfLiterals = 1;
                                }
                                else if (isReal(token) == 0)
                                {
                                    indexOfLiterals = 2;
                                }
                                else if (isHexadecimal(token) == 0)
                                {
                                    indexOfLiterals = 3;
                                }
                                else if ((index = indexOfKey(token, lines, dictionary)) != -1)
                                {
                                    fprintf(outputFile, "%s ", dictionary[index].value);
                                }
                                else
                                {
                                    fprintf(outputFile, "ERROR");

                                    break;
                                }

                                if (indexOfLiterals != -1)
                                {
                                    fprintf(outputFile, "%s ", literals[indexOfLiterals]);
                                }
                            }
                            else
                            {
                                token[index] = character;
                                token[index + 1] = '\0';
                            }

                            if ((index = indexOfSingleCharacterKey(character, lines, dictionary)) != -1)
                            {
                                fprintf(outputFile, "%s ", dictionary[index].value);

                                if (character == ';')
                                {
                                    fprintf(outputFile, "\n");
                                }
                            }

                            indexOfLiterals = -1;
                            index = 0;
                        }
                        else
                        {
                            token[index] = character;

                            index++;
                        }
                    }
                }

                fclose(outputFile);
                printf("output file written successfully...\n\n");
            }
            else
            {
                printf("unable to open/create output file...\n\n");

                return 3;   // error code 3 if output file could not be opened/created...
            }

            fclose(inputFile);
        }
        else
        {
            printf("input file not found...\n\n");

            return 2;
        }
    }
    else
    {
        printf("dictionary not found...\n\n");

        return 1;       // error code 1 if dictionary not found...
    }

    return 0;
}
