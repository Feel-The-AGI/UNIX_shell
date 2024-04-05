#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - The main function for the simple shell
 * @argc: The argument count
 * @argv: The argument values
 * @env: The environment variables
 * Return: 0 on success, otherwise the status of the last executed command
 */
int main(int argc, char **argv, char **env)
{
    int status = 0;
    char *line;

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [scriptfile]\n", argv[0]);
        return (1);
    }
    else if (argc == 2)
    {
        status = execute_input_file(argv[1], env);
    }
    else
    {
        while (1)
        {
            printf("$ ");
            line = read_line();
            if (line == NULL)
            {
                printf("\n");
                break;
            }
            status = process_input(line, env);
            free(line);
        }
    }

    return (status);
}

/**
 * execute_input_file - Execute commands from an input file
 * @file: The path to the input file
 * @env: Null-terminated array of environment variables
 *
 * Return: 0 on success, 1 on error
 */
// Execute commands from an input file
int execute_input_file(const char *file, char **env)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    while ((nread = getline(&line, &len, fp)) != -1)
    {
        line[nread - 1] = '\0'; // Remove the newline character

        char **tokens = parse_line(line);
        if (is_builtin(tokens[0]))
        {
            execute_builtin(tokens, env);
        }
        else
        {
            execute_external(tokens, env);
        }

        free_tokens(tokens);
    }

    free(line);
    fclose(fp);

    return 0;
}

/**
 * read_line - Read a line from standard input
 *
 * Return: A pointer to the read line on success, NULL on error or end of file
 */
// Read a line from standard input
char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);

    if (nread == -1)
    {
        free(line);
        return NULL;
    }

    line[nread - 1] = '\0'; // Remove the newline character

    return line;
}
