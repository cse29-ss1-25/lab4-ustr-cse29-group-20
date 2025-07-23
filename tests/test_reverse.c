#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ustr.h"

/*
rints out the reverse of the input string 
*/
int main() {
    char input[256];
    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline character if present
        size_t l = strlen(input);
        if (l > 0 && input[l - 1] == '\n') {
            input[l - 1] = '\0';
        }

        UStr s = new_ustr(input);
	UStr r = reverse(s);
        print_ustr(r);
        printf("\n");
        free_ustr(r);
        free_ustr(s);
    }
    return 0;
}
