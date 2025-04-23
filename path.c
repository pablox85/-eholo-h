#include "shell.h"

char *get_env_variable(const char *name)
{
    int i;
    size_t len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            return environ[i] + len + 1;
        }
    }
    return NULL;
}

char *find_command_in_path(char *command)
{
    char *path = get_env_variable("PATH");
    char *path_copy, *token, *full_path;
    size_t command_len, dir_len;

    if (!path || !command)
        return (NULL);

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    command_len = strlen(command);

    token = strtok(path_copy, ":");
    while (token)
    {
        dir_len = strlen(token);
        full_path = malloc(dir_len + command_len + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        sprintf(full_path, "%s/%s", token, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}