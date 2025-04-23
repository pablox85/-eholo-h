#include "shell.h"

void handle_exit(char **args, char *input)
{
    if (args)
        free(args);
    if (input)
        free(input);
    exit(0);
}

void handle_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}
