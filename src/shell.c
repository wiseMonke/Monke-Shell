#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void start_shell()
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];

    while (1)
    {
        print_prompt(); // Colorful prompt
        if (!fgets(input, MAX_INPUT_SIZE, stdin))
        {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Parse input
        parse_input(input, args);

        if (args[0] == NULL)
            continue;

        handle_builtin(args);
    }
}

void print_banner()
{
    FILE *fp = popen("figlet -f slant 'Monke Shell'", "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("\033[1;36m%s\033[0m", buffer); // Cyan color for the banner
    }

    pclose(fp);

    // Get system information
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    char *username = getenv("USER");

    printf("\n\033[1;35mWelcome, \033[1;32m%s\033[1;35m!\033[0m\n", username);
    printf("\033[1;35mHostname: \033[1;32m%s\033[0m\n", hostname);
    printf("\033[1;35mDate: \033[1;32m%s\033[0m\n", __DATE__);
    printf("\n=======================\n");
    printf("  Type 'help' for commands  \n");
    printf("=======================\n\n");
}

void print_prompt()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\033[1;32m%s\033[0m\033[1;34m > \033[0m", cwd);
    fflush(stdout);
}