//Hey your code goes here..!
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_contents(FILE *fp)
{
    char *text = NULL;
    size_t len = 0;

    while (getline(&text, &len, fp) != -1) 
    {
        printf("%s", text);
    }

    free(text);
}

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *fp = NULL;

    for (i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }

        print_contents(fp);

        fclose(fp);
    }

    return 0;
}