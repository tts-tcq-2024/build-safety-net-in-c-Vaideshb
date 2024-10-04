#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

// Get Soundex code for a character
char getSoundexCode(char character) {
    static const char soundexTable[26] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', 
        '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', 
        '0', '1', '0', '2', '0', '2'
    };

    character = toupper(character);
    if (character < 'A' || character > 'Z') {
        return '0';
    }

    return soundexTable[character - 'A'];
}

// Capitalize and return the initial character
char extractAndCapitalizeInitial(const char *inputName) {
    return toupper(inputName[0]);
}

// Fill the Soundex code with zeros to ensure length of 4
void fillWithZeros(char *soundexCode, int *currentIndex) {
    while (*currentIndex < 4) {
        soundexCode[(*currentIndex)++] = '0';
    }
    soundexCode[4] = '\0';
}

// Check if the current code is a duplicate of the previous one
int isCodeDuplicate(char currentCode, char previousCode) {
    return currentCode == previousCode && currentCode != '0';
}

// Append the Soundex code to the result
void appendSoundexCode(char *soundexCode, int *currentIndex, char code) {
    if (*currentIndex < 4) {
        soundexCode[(*currentIndex)++] = code;
    }
}

// Determine if the current character should be encoded
int shouldEncode(char currentCode, char lastEncodedCode) {
    return currentCode != '0' && !isCodeDuplicate(currentCode, lastEncodedCode);
}

// Update the last encoded code
void updateLastEncodedCode(char currentCode, char *lastEncodedCode) {
    if (currentCode != '0') {
        *lastEncodedCode = currentCode;
    }
}

// Process a single character for Soundex encoding
void processCharacter(char character, char *soundexCode, int *currentIndex, char *lastEncodedCode) {
    char currentCode = getSoundexCode(character);
    if (shouldEncode(currentCode, *lastEncodedCode)) {
        appendSoundexCode(soundexCode, currentIndex, currentCode);
    }
    updateLastEncodedCode(currentCode, lastEncodedCode);
}

// Process remaining characters in the input name
void processRemainingLetters(const char *inputName, char *soundexCode, int *currentIndex, char *lastEncodedCode) {
    for (int i = 1; inputName[i] != '\0'; i++) {
        processCharacter(inputName[i], soundexCode, currentIndex, lastEncodedCode);
    }
}

// Check if the input name is null or empty
int isNullOrEmpty(const char *inputName) {
    return inputName == NULL || strlen(inputName) == 0;
}

// Check for invalid input
int isInvalidInput(const char *inputName, char *soundexCode) {
    return soundexCode == NULL || isNullOrEmpty(inputName);
}

// Handle empty or null input for Soundex
void handleEmptyOrNullInput(const char *inputName, char *soundexCode) {
    if (isInvalidInput(inputName, soundexCode)) {
        soundexCode[0] = '\0';
    }
}

// Generate the Soundex code for a given name
void generateSoundex(const char *inputName, char *soundexCode) {
    handleEmptyOrNullInput(inputName, soundexCode);
    if (soundexCode[0] == '\0') {
        return;
    }

    soundexCode[0] = extractAndCapitalizeInitial(inputName);
    int currentIndex = 1;
    char lastEncodedCode = getSoundexCode(inputName[0]);

    processRemainingLetters(inputName, soundexCode, &currentIndex, &lastEncodedCode);
    fillWithZeros(soundexCode, &currentIndex);
}

#endif // SOUNDEX_H
