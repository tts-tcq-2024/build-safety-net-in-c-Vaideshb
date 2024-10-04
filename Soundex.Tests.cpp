#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoundexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
    char soundexCode[5];
    generateSoundex("AX", soundexCode);
    ASSERT_STREQ(soundexCode, "A200");
}

TEST(SoundexTestsuite, RetainsSoleLetterOfOneLetterWord) {
    char soundexCode[5];
    generateSoundex("A", soundexCode);
    ASSERT_STREQ(soundexCode, "A000");
}

TEST(SoundexTestsuite, PadsWithZerosToEnsureThreeDigits) {
    char soundexCode[5];
    generateSoundex("I", soundexCode);
    ASSERT_STREQ(soundexCode, "I000");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsSeparatedByVowels) {
    char soundexCode[5];
    generateSoundex("Abfcg", soundexCode);
    ASSERT_STREQ(soundexCode, "A120");
}

TEST(SoundexTestsuite, UppercasesFirstLetter) {
    char soundexCode[5];
    generateSoundex("abcd", soundexCode);
    ASSERT_STREQ(soundexCode, "A123");
}

TEST(SoundexTestsuite, IgnoresCaseWhenEncodingConsonants) {
    char soundexCode[5];
    generateSoundex("BCDL", soundexCode);
    ASSERT_STREQ(soundexCode, "B234");
}

TEST(SoundexTestsuite, HandlesEmptyString) {
    char soundexCode[5];
    generateSoundex("", soundexCode);
    ASSERT_STREQ(soundexCode, "");
}

TEST(SoundexTestsuite, HandlesNullString) {
    char soundexCode[5];
    generateSoundex(nullptr, soundexCode);
    ASSERT_STREQ(soundexCode, "");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsWithHAndWInBetween) {
    char soundexCode[5];
    generateSoundex("Ashcraft", soundexCode);
    ASSERT_STREQ(soundexCode, "A261");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsWithHAndWInBetween2) {
    char soundexCode[5];
    generateSoundex("Tymczak", soundexCode);
    ASSERT_STREQ(soundexCode, "T520");
}

TEST(SoundexTestsuite, StopsAtThreeDigits) {
    char soundexCode[5];
    generateSoundex("Washington", soundexCode);
    ASSERT_STREQ(soundexCode, "W252");
}
