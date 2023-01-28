// Code by William (Joe) Brashear
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line_w_word(FILE *fp, char *needle)
{
    char *haystack = NULL;
    size_t len = 0;
    char *res = NULL;

    while (getline(&haystack, &len, fp) != -1) 
    {
        res = strstr(haystack, needle);
        if (res != NULL)
        {
            printf("%s", haystack);
        }
    }

    free(haystack);
}

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *fp = NULL;

    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    if (argc == 2)
    {
        fp = stdin;

        if (fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        print_line_w_word(fp, argv[1]);

        fclose(fp);
    }

    for (i = 2; i < argc; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        print_line_w_word(fp, argv[1]);

        fclose(fp);
    }

    return 0;
}