#include <stdio.h>
#include "../ustr.h"

int main() {
    char buf1[1024];
    char buf2[1024];

    // Read first string
    if (fgets(buf1, sizeof(buf1), stdin) == NULL) return 1;
    // Remove newline
    int len1 = 0;
    while (buf1[len1] != '\0') {
        if (buf1[len1] == '\n') {
            buf1[len1] = '\0';
            break;
        }
        len1++;
    }

    // Read second string
    if (fgets(buf2, sizeof(buf2), stdin) == NULL) return 1;
    // Remove newline
    int len2 = 0;
    while (buf2[len2] != '\0') {
        if (buf2[len2] == '\n') {
            buf2[len2] = '\0';
            break;
        }
        len2++;
    }

    // Create UStr objects
    UStr str1 = new_ustr(buf1);
    UStr str2 = new_ustr(buf2);

    // Concatenate
    UStr result = concat(str1, str2);
    print_ustr(result);

    // Free all allocated memory
    free_ustr(str1);
    free_ustr(str2);
    free_ustr(result);

    return 0;
}

