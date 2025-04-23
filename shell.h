#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char **tokenize_input(char *input);
char *find_command_in_path(char *command);
void execute_command(char **args, char *input);
void handle_exit(char **args, char *input);
void handle_env(void);
void execute_external_command(char **args);

#endif

