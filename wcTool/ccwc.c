#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void exec(char *filename);
long long get_bytes(char *filename);
int count_lines(char *filename);
unsigned long count_words(char *filename);
void print_c_option(char *filename);
void print_l_option(char *filename);
void print_w_option(char *filename);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Supply filename");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[2];

    if (argc == 3)
    {
        char *option = argv[1];

        if (strcmp(option, "-c") == 0)
        {
            print_c_option(filename);
        }
        else if (strcmp(option, "-l") == 0)
        {
            print_l_option(filename);
        }
        else if (strcmp(option, "-w") == 0)
        {
            print_w_option(filename);
        }
        else
        {
            perror("Don't know that option.");
            exit(1);
        }
    }
}

long long get_bytes_file(char *filename)
{
    struct stat st;
    if (stat(filename, &st) != 0)
    {
        perror(filename);
        exit(1);
    }

    return (long long)st.st_size;
}

int count_lines(char *filename)
{
    FILE *fp;
    int count = 0;
    char c;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        exit(1);
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count++;

    fclose(fp);

    return count;
}

unsigned long count_words(char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        exit(1);
    }

    unsigned long count = 0;
    char ch;
    int in_word = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace((unsigned char)ch))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
    }

    fclose(fp);

    return count;
}

void print_c_option(char *filename)
{
    long long file_size = get_bytes_file(filename);

    printf("%lld %s\n", file_size, filename);
}

void print_l_option(char *filename)
{
    int quantity_lines = count_lines(filename);

    printf("%d %s\n", quantity_lines, filename);
}

void print_w_option(char *filename)
{
    int quantity_words = count_words(filename);

    printf("%d %s\n", quantity_words, filename);
}
