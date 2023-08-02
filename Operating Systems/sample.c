//simulate grep in linux
#include<stdio.h>
#include<string.h>
void main()
{
char fn[10],pat[10],temp[200];
FILE *fp;
printf("Enter file name\n");
scanf("%s",fn);
printf("Enter pattern to be searched\n");
scanf("%s",pat);
fp=fopen(fn,"r");
while(!feof(fp))
{
fgets(temp,1000,fp);
if(strstr(temp,pat))
  printf("%s",temp);
}
fclose(fp);
}
//q2
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2] [file3] ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("Error opening file");
            continue;
        }

        int line_count = 0;
        char c;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
            if (c == '\n') {
                line_count++;
                if (line_count % 20 == 0) {
                    printf("-- More --");
                    getchar();
                }
            }
        }

        fclose(file);
    }

    return 0;
}
//q3
#include <stdio.h>

int main() {
    int i = 42;
    float f = 3.14159;
    char c = 'A';
    char *s = "Hello, world!";

    printf("Integer: %d\n", i);
    printf("Float: %f\n", f);
    printf("Character: %c\n", c);
    printf("String: %s\n", s);

    return 0;
}
//q4
#include <stdio.h>

int main() {
    FILE *source = fopen("source.txt", "r");
    FILE *destination = fopen("destination.txt", "w");

    if (source == NULL || destination == NULL) {
        perror("Error opening files");
        return 1;
    }

    int c;
    while ((c = fgetc(source)) != EOF) {
        fputc(c, destination);
    }

    fclose(source);
    fclose(destination);

    return 0;
}
