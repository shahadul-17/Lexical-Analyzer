#include "tokentype.h"

char isInteger(const char *token)
{
    int i, length = getLength(token);

    for (i = 0; i < length; i++)
    {
        if (!(token[i] > 47 && token[i] < 58))
        {
            return -1;
        }
    }

    return 0;
}

char isReal(const char *token)
{
    char flag = -1;
    int i, j, length = getLength(token);

    for (i = 0; i < length; i++)
    {
        if (token[i] == '.')
        {
            flag = 0;

            break;
        }
    }

    if (i == length - 1)
    {
        return -1;
    }

    for (j = 0; flag == 0 && j < length; j++)
    {
        if (j == i)
        {
            continue;
        }

        if (!(token[j] > 47 && token[j] < 58))
        {
            flag = -1;

            break;
        }
    }

    if (j == 1)
    {
        flag = -1;
    }

    return flag;
}

char isCharacter(const char *token)
{
    char flag = -1;
    int length = getLength(token);

    if (length != 3)
    {
        return flag;
    }

    if ((token[0] == '\'' && token[0] == token[length - 1]) &&
        ((token[0] > 64 || token[0] < 91) && (token[0] > 96 || token[0] < 123)))
    {
        flag = 0;
    }

    return flag;
}

char isHexadecimal(const char *token)
{
    char flag = -1;
    int i, length = getLength(token);

    if (length - 2 > 16)        // hexa decimal MAX DIGITS = 16...
    {
        return flag;
    }

    if (token[0] == '0' && token[1] == 'x')
    {
        flag = 0;

        for (i = 2; i < length; i++)
        {
            if (!((token[i] > 47 && token[i] < 58) ||
                (token[i] > 64 && token[i] < 71) ||
                (token[i] > 96 && token[i] < 103)))
            {
                flag = -1;

                break;
            }
        }
    }

    return flag;
}

char isString(const char *token)
{
    int length = getLength(token);

    if (token[0] == '"' && token[length - 1] == '"')
    {
        return 0;
    }

    return -1;
}

char isIdentifier(const char *token)
{
    char flag = -1;
    int i, length = getLength(token);

    if (token[0] > 47 && token[0] < 58)
    {
        return flag;    // -1;
    }
    else if ((token[0] == '$' || token[0] == '-') && length == 1)
    {
        return flag;    // -1;
    }
    else
    {
        flag = 0;

        for (i = 0; i < length; i++)
        {
            if (token[i] != '-' && token[i] != '$' &&
                (token[i] < 65 || token[i] > 90) &&
                (token[i] < 97 || token[i] > 122) &&
                (token[i] < 48 || token[i] > 57))
            {
                flag = -1;

                break;
            }
        }

        return flag;
    }
}

int indexOfKeyword(const char *token, int length, struct KeyValuePair dictionary[])
{
    int index;

    for (index = 25; index < length; index++)       // 25 is the starting index of keywords in dictionary...
    {
        if (compareStrings(token, dictionary[index].key) == 0)
        {
            return index;
        }
    }

    return -1;
}
