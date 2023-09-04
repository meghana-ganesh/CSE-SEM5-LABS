#include <stdio.h>
#include <stdlib.h>

void removeComments(FILE *fa, FILE *fb) {
    int insideString = 0;
    char ca, cb;

    if (fa == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    ca = getc(fa);

    while (ca != EOF) {
        if (ca == '"') {
            
            insideString = !insideString;
            putc(ca, fb);
        } else if (ca == '/') {
            cb = getc(fa);

            if (cb == '/') {
                if (!insideString) {
                    while (ca != '\n') {
                        ca = getc(fa);
                    }
                } else {
                    putc(ca, fb);
                    putc(cb, fb);
                }
            } else if (cb == '*') {
                if (!insideString) {
                    char prev = ca;
                    ca = getc(fa);
                    cb = getc(fa);
                    while (prev != '*' || ca != '/') {
                        prev = ca;
                        ca = cb;
                        cb = getc(fa);
                    }
                } else {
                    putc(ca, fb);
                    putc(cb, fb);
                }
            } else {
                putc(ca, fb);
                putc(cb, fb);
            }
        } else {
            putc(ca, fb);
        }

        ca = getc(fa);
    }
}

