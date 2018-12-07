#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b);

int cmp(const void *x, const void *y);

void inputErr();

void outputErr();

void checkMemError(const void *x);

int main() {
    char *chars = (char *) malloc(sizeof(char));
    checkMemError(chars);
    char c = getchar();
    inputErr("Input error.");
    int charsCount = 0;
    while (c != EOF) {
        chars = (char *) realloc(chars, (charsCount+1) * sizeof(char));
        checkMemError(chars);
        chars[charsCount] = c;
        c = getchar();
        inputErr("Input error.");
        charsCount++;
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
    int k;

    qsort(words, wordCount, sizeof(char*), cmp);

    for (k = 0; k < wordCount; k++) {
        printf("%s", words[k]);
        outputErr();
    }

    chars = NULL;
    words = NULL;
    free(chars);
    free(words);
    exit(EXIT_SUCCESS);
}

int frobcmp(const char *a, const char *b) {
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

int cmp(const void *x, const void *y) {
    const char** xPtr = (const char**) x;
    const char** yPtr = (const char**) y;
    const char *xVal = *xPtr;
    const char *yVal = *yPtr;
    return frobcmp(xVal, yVal);
}

void inputErr() {
    if (ferror(stdin)) {
        fprintf(stderr, "Input error.");
        exit(EXIT_FAILURE);
    }
}

void outputErr() {
    if (ferror(stdout)) {
        fprintf(stderr, "Output error.");
        exit(EXIT_FAILURE);
    }   
}

void checkMemError(const void *x) {
    if (x == NULL) {
        fprintf(stderr, "Memory allocation error.");
        exit(EXIT_FAILURE);
    }
}
