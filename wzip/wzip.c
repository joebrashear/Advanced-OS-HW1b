// Code by William (Joe) Brashear
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

void compress(FILE *fp)
{
    char *text = NULL;
    size_t buffer_len = 0;
    int left = 0;
    int right = 0;
    int len = 0;
    int substring_len = 0;

    while (getline(&text, &buffer_len, fp) != -1) 
    {
        left = 0;
        substring_len = 0;
        len = strlen(text);

        for (right = 1; right < len; right++)
        {
            substring_len = right - left;

            if (text[left] != text[right])
            {
                if (debug == 1)
                {
                    printf("%d%c", substring_len, text[left]);
                }
                fwrite(&substring_len, 1, sizeof(int), stdout);
                fprintf(stdout, "%c", text[left]);
                left = right;
            }
        }
        if (debug == 1)
        {
            printf("\n");
        }
    }

    free(text);
}

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *fp = NULL;
    FILE *ofp = NULL;
    char c;

    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    fp = fopen(argv[1], "r+");

    if (fp == NULL)
    {
        printf("wzip: cannot open file\n");
        return 1;
    }   

    for (i = 2; i < argc; i++)
    {
        ofp = fopen(argv[i], "r");

        if (ofp == NULL)
        {
            printf("wzip: cannot open file\n");
            fclose(fp);
            return 1;
        }

        while ((c = fgetc(ofp)) != EOF)
        {
            fputc(c, fp);
        }

        fclose(ofp);
    }

    rewind(fp);
    compress(fp);
    fclose(fp);

    return 0;
}