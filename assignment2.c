#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int alphanumeric(char c);  // fn to check a character is alphanumeric
char generateRandomChar();  // Function to generate a random character from a given set
char *generateRandomPalindromeString(int minLength, int maxLength);  // Function to generate a random alphanumeric palindrome string
int countPossiblePalindromes(char *str);  // Function to count the number of possible palindromic combinations
void printPossiblePalindromes(char *str, char *prefix, int length);  // Function to print all possible palindromic combinations
void generatePalindromesHelper(char *str, char *prefix, int *charCount, int length, int index);

int main() {
    int minLength = 5;
    int maxLength = 11;
    srand(time(0));
    char *randompalindrome = generateRandomPalindromeString(minLength, maxLength);
    printf("The randomly generated alphanumeric palindrome string is %s", randompalindrome);
    int combinations = countPossiblePalindromes(randompalindrome);
    printf(" and total %d other palindrome strings can be generated from this palindrome string.\n", combinations);
    char *prefix = "";
    printPossiblePalindromes(randompalindrome, prefix, strlen(randompalindrome));
    free(randompalindrome);
    return 0;
}

int alphanumeric(char c) {
    return isalnum(c);
}

char generateRandomChar() {
    char set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len = strlen(set);
    return set[rand() % len];
}

char *generateRandomPalindromeString(int minLength, int maxLength) {
    int length = rand() % (maxLength - minLength + 1) + minLength;
    char *str = (char *)malloc((length + 1) * sizeof(char));

    // Generate the first half of the palindrome string
    for (int i = 0; i < length / 2; i++) {
        char c = generateRandomChar();
        str[i] = c;
    }
    for (int i = length / 2 - 1; i >= 0; i--) {
        str[length - i - 1] = str[i];
    }
    str[length] = '\0';
    return str;
}

int countPossiblePalindromes(char *str) {
    int count = 0;
    int len = strlen(str);
    // To count occurrences of each character
    int charCount[256] = {0};
    for (int i = 0; i < len; i++) {
        charCount[str[i]]++;
    }
    int oddCountChars = 0;
    for (int i = 0; i < 256; i++) {
        if (charCount[i] % 2 != 0) {
            oddCountChars++;
        }
    }

    // Calculate the number of combinations for palindromes
    if (oddCountChars <= 1) {
        count = 1;
        for (int i = 0; i < 256; i++) {
            if (charCount[i] > 0) {
                count *= charCount[i] / 2 + 1;
            }
        }
    }

    return count;
}

void printPossiblePalindromes(char *str, char *prefix, int length) {
    // To count occurrences of each character
    int charCount[256] = {0};
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        charCount[str[i]]++;
    }
    generatePalindromesHelper(str, prefix, charCount, length, 0);
}

void generatePalindromesHelper(char *str, char *prefix, int *charCount, int length, int index) {
    if (index >= length) {
        printf("%s%s\n", prefix, str);
        return;
    }

    for (int i = 0; i < 256; i++) {
        if (charCount[i] > 0) {
            charCount[i] -= 2;
            prefix[index] = i;
            prefix[length - index - 1] = i;
            generatePalindromesHelper(str, prefix, charCount, length, index + 1);
            charCount[i] += 2;
        }
    }
}
