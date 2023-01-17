/**
 * @file beaufort.c
 * @author Khojiakbar Yokubjonov
 * @class CSC352, Fall 2022
 * @brief This program implements Beaufort cipher for encrypting messages.
 *        Beaufort cipher requires an encryption key in order to function.
 *        first line it gets on standard input will be the value of the key 
 *        (a char sequence with only upper-case alphabetical letters). 
 *      The remaining lines represent the word/message to be encrypted.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int START = 'A';
int END = 'Z';

/**
 * @brief encrypts a given character
 * 
 * @param letter - a char to be encrypted
 * @param keyChar - a corresponding key letter from the keyword
 * @return char - a resulting encrypting char
 */
char encryptChar(char letter, char keyChar)
{
    int value = letter;
    int keyValue = keyChar;
    int diff;
    if (keyValue >= value)
    {
        diff = keyValue - value;
    }
    else
    {
        diff = END + 1 - value + keyChar - START;
    }
    char newChar = START + diff;
    return newChar;
}

/**
 * @brief returns the corresponding index for the keyword
 *         it handles the cases when the given phrase is longer than the keyword.
 *          this function will calculate and return the matching letter from the keyword.
 * 
 * @param charIndex - index of the letter from the given phrase
 * @param keyWordLength - length of the keyword
 * @return - returns the index of the keyword letter
 */
int getCorrespondingKeyIndex(int charIndex, int keyWordLength)
{
    return charIndex % keyWordLength;
}


/**
 * @brief encrypts a given phrase. User the encryptChar helper function to encrypt the chars.
 * 
 * @param phrase - phrase to be encrypted
 * @param keyWord - the keyword to be used for the enryption
 * @param indexCount - counts the total indexes for the entire phrase
 * @return int - the number of characters encryted in each func call
 */
int encryptText(char phrase[], char keyWord[], int indexCount)
{
    int i=0;
    int indexOffset = 0;
    int phraseLength = strlen(phrase);
    while (i + indexOffset < phraseLength)
    {
        if (phrase[i + indexOffset] == ' ')
        {
            printf("%c", ' ');
            indexOffset++;
        }else if (phrase[i + indexOffset] == '\n')
        {
            printf("%c", '\n');
            indexOffset++;
        }
        else
        {
            int index = getCorrespondingKeyIndex(i + indexCount, strlen(keyWord));
            char newChar = encryptChar(phrase[i + indexOffset], keyWord[index]);
            printf("%c", newChar);
            i++;
        }
    }

    return i + indexCount;
}

int main()
{
    char key[128];
    char buffer[256];
    int line = 0;
    int indexCount=0;

    //accepting stdin 
    while (fgets(buffer, 255, stdin) != NULL)
    {
        if(line==0){
            strtok(buffer, "\n");
            strcpy(key, buffer);
        }else{
            indexCount = encryptText(buffer, key, indexCount);        }
        line++;
    }
  
    return 0;
}
