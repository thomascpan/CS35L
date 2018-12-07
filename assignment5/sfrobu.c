#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int frobcmp(char const *a, char const *b);

int cmp(const void *x, const void *y);

int frobcmpIgnoreCase(char const *a, char const *b);

int cmpIngoreCase(const void *x, const void *y);

void fileError(int ret);

void inputErr(int ret);

void outputErr(int ret);

void checkMemError(const void *x);

void setIgnoreCase(int* ignoreCase, char* arg);

int validChar(char c);

int comparisonCount = 0;

int main(int argc, char* argv[]) {
    int ignoreCase = 0;
    if (argc == 2) { setIgnoreCase(&ignoreCase, argv[1]); }

    struct stat buf;
    fileError(fstat(0, &buf));
    printf("%d\n", buf.st_size);

    char *chars = (char *) malloc(buf.st_size);
    checkMemError(chars);
    ssize_t charsCount = buf.st_size;
    int ret = read(0, chars, buf.st_size);
    inputErr(ret);
    char c;
    ret = read(0, &c, 1);
    inputErr(ret);

    while (ret) {
        if (charsCount > buf.st_size) {
            chars = (char *) realloc(chars, (charsCount) * sizeof(char));
            checkMemError(chars);
        }
        chars[charsCount++] = c;
        ret = read(0, &c, 1);
        inputErr(ret);
    }
    if (charsCount) {
        chars = (char *) realloc(chars, (charsCount+1) * sizeof(char));
        checkMemError(chars);
        chars[charsCount++] = ' ';
    }

    char **words = (char **) malloc(sizeof(char *));
    checkMemError(chars);
    int wordCount = 0;
    int start = 0;
    int end = 0;
    int i;
    for (i = 0; i < charsCount; i++) {
        if (chars[end] == ' ') {
            int length = (end-start)+2;
            words = (char **) realloc(words, (wordCount+1) * sizeof(char *));
            checkMemError(chars);
            char *word = (char *) malloc(length * sizeof(char));
            int j = 0;
            int k = start;
            while (k <= end) {
                word[j] = chars[k];
                j++;
                k++;
            }
            word[j] = 0;
            words[wordCount] = word;
            start = end+1;
            wordCount++;
            word = NULL;
            free(word);
        }
        end++;
    }

    if (ignoreCase) {
        qsort(words, wordCount, sizeof(char*), cmpIngoreCase);
    } else {
        qsort(words, wordCount, sizeof(char*), cmp);
    }

    int k;
    for (k = 0; k < wordCount; k++) {
        int size = 0;
        while (words[k][size++] != ' ');
        ret = write(1, words[k], size);
        outputErr(ret);
    }

    chars = NULL;
    words = NULL;
    free(chars);
    free(words);
    exit(EXIT_SUCCESS);
}

int frobcmp(const char *a, const char *b) {
    comparisonCount++;
    while (1) {
        char aVal = *a;
        char bVal = *b;
        if (aVal == ' ' && bVal == ' ') { return 0; }
        if (aVal == ' ') { return -1; }
        if (bVal == ' ') { return 1; }
        char aOVal = aVal ^ 42;
        char bOVal = bVal ^ 42;
        if (aOVal < bOVal) { return -1; }
        if (aOVal > bOVal) { return 1; }
        a++;
        b++;
    }
}

int cmpIngoreCase(const void *x, const void *y) {
    const char** xPtr = (const char**) x;
    const char** yPtr = (const char**) y;
    const char *xVal = *xPtr;
    const char *yVal = *yPtr;
    return frobcmpIgnoreCase(xVal, yVal);
}

int frobcmpIgnoreCase(const char *a, const char *b) {
    comparisonCount++;
    while (1) {
        char aVal = *a;
        char bVal = *b;
        if (aVal == ' ' && bVal == ' ') { return 0; }
        if (aVal == ' ') { return -1; }
        if (bVal == ' ') { return 1; }
        char aOVal = aVal ^ 42;
        char bOVal = bVal ^ 42;
        char aOUVal = toupper(aVal ^ 42);
        char bOUVal = toupper(bVal ^ 42);
        if (validChar(aVal)) { aOVal = aOUVal; }
        if (validChar(bVal)) { bOVal = bOUVal; }
        if (aOVal < bOVal) { return -1; }
        if (aOVal > bOVal) { return 1; }
        a++;
        b++;
    }
}

int cmp(const void *x, const void *y) {
    const char** xPtr = (const char**) x;
    const char** yPtr = (const char**) y;
    const char *xVal = *xPtr;
    const char *yVal = *yPtr;
    return frobcmp(xVal, yVal);
}

void fileError(int ret) {
    if (ret == -1) {
        char msg[] = "File error.";
        write(2, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
}

void inputErr(int ret) {
    if (ret == -1) {
        char msg[] = "Input error.";
        write(2, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
}

void outputErr(int ret) {
    if (ret == -1) {
        char msg[] = "Output error.";
        write(2, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
}

void checkMemError(const void *x) {
    if (x == NULL) {
        char msg[] = "Memory allocation error.";
        write(2, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
}

void setIgnoreCase(int* ignoreCase, char* arg) {
    *ignoreCase = !strcmp(arg, "-f");
}

int validChar(char c) {
    int result = 0;
    result = c < CHAR_MAX;
    result = c > CHAR_MIN;
    return result;
}

