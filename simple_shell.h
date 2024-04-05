#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/* Function prototypes for simple_shell.c */
int execute_input_file(const char *file, char **env);
int main(int argc, char **argv, char **env);


/* Function prototypes for parse.c */
char *read_line(void);
char **parse_line(char *line);
int process_input(char *line, char **env);
int is_builtin(char *cmd);
int execute_builtin(char **tokens, char **env);
int execute_external(char **tokens, char **env);

/* Function prototypes for builtins.c */
int builtin_exit(char **tokens, char **env);
int builtin_env(char **tokens, char **env);
int builtin_setenv(char **tokens, char **env);
int builtin_unsetenv(char **tokens, char **env);
int builtin_cd(char **tokens, char **env);
void free_tokens(char **tokens);

/* Function prototypes for variables.c */
int replace_special_vars(char **tokens, pid_t shell_pid, int last_status);

/* Function prototypes for utilities.c */
ssize_t _getline(char **lineptr, size_t *n);
void print_error(char *argv0, char *input, char *err);
size_t token_count(const char *str, const char *delim);

#endif /* SIMPLE_SHELL_H */