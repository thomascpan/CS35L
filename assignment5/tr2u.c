#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int findElement(const char *list, char c, int length) {
    int result = -1;
    int i;
    for (i = 0; i < length; i++) {
        if (list[i] == c) {
            result = i;
            break;
        }
    }
    return result;
}

void testInputLength(int len1, int len2) {
    if (len1 != len2) {
        fprintf(stderr, "%s\n", "From and To are not same length.");
        exit(1);
    }
}

void testDuplicates(const char *list, int length) {
    int i;
    for (i = 0; i < length; i++) {
        int j;
        for (j = i+1; j < length; j++) {
            if (list[i] == list[j]) {
                fprintf(stderr, "%s\n", "From has duplicate byte.");
                exit(1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    char* from = argv[1];
    char* to = argv[2];
    int fromLen = strlen(from);
    int toLen = strlen(to);

    testInputLength(fromLen, toLen);
    testDuplicates(from, fromLen);

    char c[1];

    while (read(0, c, 1)) {
        char output = *c;
        int index = findElement(from, *c, fromLen);
        if (index != -1)
            output = to[index];
        write(1, &output, 1);
    }

    return 0;
}


