#include "simple_shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple_shell.h"

/**
 * execute_external - Execute an external command
 * @tokens: Null-terminated array of command and arguments
 * @env: Null-terminated array of environment variables
 *
 * Return: 0 on success, 1 on error
 */
// Execute an external command
int execute_external(char **tokens, char **env)
{
    (void) env;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0) // Child process
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            perror("execvp");
        }
        exit(EXIT_FAILURE); // Only reached if execvp() fails
    }
    else // Parent process
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}


/**
 * process_input - Processes user input and executes commands
 * @line: The input line
 * @env: The environment variables
 * Return: The status of the command execution
 */
int process_input(char *line, char **env)
{
    int status = 0;
    char **tokens;

    tokens = parse_line(line);

    if (tokens[0] == NULL)
    {
        free(tokens);
        return 1;
    }

    if (is_builtin(tokens[0]))
    {
        status = execute_builtin(tokens, env);
    }
    else
    {
        status = execute_external(tokens, env);
    }

    free(tokens);
    return status;
}

/**
 * parse_line - Parses a line into an array of tokens
 * @line: The line to parse
 * Return: A null-terminated array of tokens
 */
char **parse_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "simple_shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "simple_shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * is_builtin - Checks if a command is a builtin command
 * @cmd: The command to check
 * Return: 1 if the command is builtin, 0 otherwise
 */
int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {
        "exit",
        "setenv",
        "unsetenv",
        "cd",
        NULL
    };

    for (i = 0; builtins[i]; i++)
    {
        if (strcmp(cmd, builtins[i]) == 0)
            return (1);
    }

    return (0);
}