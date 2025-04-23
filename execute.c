#include "shell.h"

void execute_command(char **args, char *input)
{
    if (strcmp(args[0], "exit") == 0)
    {
        handle_exit(args, input);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        handle_env();
    }
    else
    {
        execute_external_command(args);
    }
}

void execute_external_command(char **args)
{
    pid_t pid;
    char *command_path = args[0];

    if (access(command_path, X_OK) != 0)
    {
        command_path = find_command_in_path(args[0]);
        if (!command_path)
        {
            print_command_error(args[0]);
            exit(127);
        }
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror(command_path);
            exit(127);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("Fork error");
    }

    if (command_path != args[0])
        free(command_path);
}
