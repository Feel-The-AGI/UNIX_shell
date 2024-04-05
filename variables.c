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
 * replace_special_vars - Replaces special variables in the tokens
 * @tokens: Array of tokens (arguments)
 * @shell_pid: The process ID of the shell
 * @last_status: The status of the last executed command
 *
 * Return: 0 if successful, 1 otherwise
 */
int replace_special_vars(char **tokens, pid_t shell_pid, int last_status)
{
    char *var_value;
    char buffer[16];

    for (int i = 0; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "$?") == 0)
        {
            snprintf(buffer, sizeof(buffer), "%d", last_status);
            var_value = strdup(buffer);
            if (var_value == NULL)
            {
                perror("strdup");
                return 1;
            }
            free(tokens[i]);
            tokens[i] = var_value;
        }
        else if (strcmp(tokens[i], "$$") == 0)
        {
            snprintf(buffer, sizeof(buffer), "%ld", (long)shell_pid);
            var_value = strdup(buffer);
            if (var_value == NULL)
            {
                perror("strdup");
                return 1;
            }
            free(tokens[i]);
            tokens[i] = var_value;
        }
    }

    return 0;
}