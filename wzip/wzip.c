// Code by William (Joe) Brashear
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

int compress(FILE *fp)
{
    char left = fgetc(fp);
    char right;
    int substring_len = 0;
    int ret = 0;

    while (left != EOF) 
    {
        substring_len = 1;
        
        while ((right = fgetc(fp)) != EOF && left == right)
            substring_len++;

        ret = fwrite(&substring_len, sizeof(substring_len), 1, stdout);
        if (ret != 1)
        {
            printf("fwrite failed\n");
            return 1;
        }

        fprintf(stdout, "%c", left);
        left = right;
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
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    if (argc == 2)
    {
        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
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
    }

    if (compress(fp) == 1)
    {
        return 1;
    }

    fclose(fp);

    return 0;
}