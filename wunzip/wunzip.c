// Code by William (Joe) Brashear
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

int decompress(FILE *fp)
{
    int len;
    char char_sub;
    int i = 0;
    int ret = 0;

    while (1) 
    {
        ret = fread(&len, sizeof(int), 1, fp);
        if (ret != 1)
        {
            return 0;
        }
        
        char_sub = fgetc(fp);
        if (char_sub == EOF)
        {
            printf("format should be <int><char>\n");
            return 1;
        }

        for (i = 0; i < len; i++)
        {
            fprintf(stdout, "%c", char_sub);
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *fp = NULL;
    FILE *ofp = NULL;
    char c;
    
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    if (argc == 2)
    {
        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            printf("wunzip: cannot open file\n");
            return 1;
        }   
    }
    else
    {
        fp = fopen("tests-out/combined", "w+");

        if (fp == NULL)
        {
            printf("failed to create master file\n");
            return 1;
        }   

        for (i = 1; i < argc; i++)
        {
            ofp = fopen(argv[i], "r");

            if (ofp == NULL)
            {
                printf("wunzip: cannot open file\n");
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
    }

    if (decompress(fp) == 1)
    {
        return 1;
    }

    fclose(fp);

    return 0;
}