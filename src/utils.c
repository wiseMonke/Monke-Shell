#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

// Parse user input into arguments
void parse_input(char *input, char **args)
{
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

// Execute external commands
void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
    }
    else if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("Command execution failed");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process waits
        wait(NULL);
    }
}