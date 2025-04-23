#include "shell.h"

void print_command_error(const char *cmd)
{
    fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
}