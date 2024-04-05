#include "simple_shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
/**
 * _getline - Custom getline function to read a line from stdin
 * @lineptr: Pointer to the buffer to store the read line
 * @n: Size of the buffer
 *
 * Return: The number of characters read, -1 on failure or EOF
 */
ssize_t _getline(char **lineptr, size_t *n)
{
    return getline(lineptr, n, stdin);
}

/**
 * print_error - Prints an error message to stderr
 * @argv0: Name of the shell (first argument)
 * @input: User input
 * @err: Error message
 */
void print_error(char *argv0, char *input, char *err)
{
    fprintf(stderr, "%s: %s: %s\n", argv0, input, err);
}

/**
 * token_count - Counts the number of tokens in a string
 * @str: The string to count tokens in
 * @delim: The delimiter string
 *
 * Return: The number of tokens in the string
 */
size_t token_count(const char *str, const char *delim)
{
    size_t count = 0;
    char *copy, *token;

    copy = strdup(str);
    if (copy == NULL)
    {
        perror("strdup");
        return 0;
    }

    token = strtok(copy, delim);
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, delim);
    }

    free(copy);
    return count;
}