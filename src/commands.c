#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "shell.h"

void handle_builtin(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        printf("Exiting shell...\n");
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            // If no argument, go to home directory
            chdir(getenv("HOME"));
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("cd");
            }
        }
    }
    else if (strcmp(args[0], "help") == 0)
    {
        print_help();
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("pwd");
        }
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        for (int i = 1; args[i] != NULL; i++)
        {
            printf("%s ", args[i]);
        }
        printf("\n");
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        const char *dir_path = "."; // Default to current directory
        if (args[1] != NULL)
        {
            dir_path = args[1]; // Use the provided directory
        }

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(dir_path)) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                // Skip hidden files (those starting with '.')
                if (ent->d_name[0] == '.')
                {
                    continue;
                }

                // Get file stats
                char full_path[1024];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, ent->d_name);
                struct stat st;
                if (stat(full_path, &st) == 0)
                {
                    if (S_ISDIR(st.st_mode))
                    {
                        // Directory: blue
                        printf("\033[1;34m%s\033[0m\n", ent->d_name);
                    }
                    else if (st.st_mode & S_IXUSR)
                    {
                        // Executable: red
                        printf("\033[1;31m%s\033[0m\n", ent->d_name);
                    }
                    else
                    {
                        // Regular file: green
                        printf("\033[1;32m%s\033[0m\n", ent->d_name);
                    }
                }
                else
                {
                    perror("stat");
                }
            }
            closedir(dir);
        }
        else
        {
            perror("ls");
        }
    }
    else if (strcmp(args[0], "mkdir") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "mkdir: missing operand\n");
        }
        else
        {
            if (mkdir(args[1], 0777) == -1)
            {
                perror("mkdir");
            }
        }
    }
    else if (strcmp(args[0], "rmdir") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "rmdir: missing operand\n");
        }
        else
        {
            if (rmdir(args[1]) == -1)
            {
                perror("rmdir");
            }
        }
    }
    else if (strcmp(args[0], "rm") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "rm: missing operand\n");
        }
        else
        {
            if (unlink(args[1]) == -1)
            {
                perror("rm");
            }
        }
    }
    else if (strcmp(args[0], "touch") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "touch: missing operand\n");
        }
        else
        {
            int fd = open(args[1], O_CREAT | O_WRONLY, 0644);
            if (fd == -1)
            {
                perror("touch");
            }
            else
            {
                close(fd);
            }
        }
    }
    else if (strcmp(args[0], "cat") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "cat: missing operand\n");
        }
        else
        {
            FILE *file = fopen(args[1], "r");
            if (file == NULL)
            {
                perror("cat");
            }
            else
            {
                char ch;
                while ((ch = fgetc(file)) != EOF)
                {
                    putchar(ch);
                }
                fclose(file);
            }
        }
    }
    else if (strcmp(args[0], "cp") == 0)
    {
        if (args[1] == NULL || args[2] == NULL)
        {
            fprintf(stderr, "cp: missing operand\n");
        }
        else
        {
            FILE *src = fopen(args[1], "r");
            FILE *dest = fopen(args[2], "w");

            if (src == NULL || dest == NULL)
            {
                perror("cp");
            }
            else
            {
                char ch;
                while ((ch = fgetc(src)) != EOF)
                {
                    fputc(ch, dest);
                }
                fclose(src);
                fclose(dest);
            }
        }
    }
    else if (strcmp(args[0], "mv") == 0)
    {
        if (args[1] == NULL || args[2] == NULL)
        {
            fprintf(stderr, "mv: missing operand\n");
        }
        else
        {
            if (rename(args[1], args[2]) == -1)
            {
                perror("mv");
            }
        }
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        printf("\033[H\033[J");
    }
    else
    {
        // Not a built-in command, execute as external command
        execute_command(args);
    }
}

void print_help()
{
    printf("\033[1;35mAvailable commands:\033[0m\n");
    printf("  \033[1;32mexit\033[0m          - Exit the shell\n");
    printf("  \033[1;32mcd <dir>\033[0m      - Change directory\n");
    printf("  \033[1;32mhelp\033[0m          - Display this help message\n");
    printf("  \033[1;32mpwd\033[0m           - Print working directory\n");
    printf("  \033[1;32mecho <text>\033[0m   - Print text to the terminal\n");
    printf("  \033[1;32mls <dir>\033[0m      - List directory contents (default: current directory)\n");
    printf("  \033[1;32mmkdir <dir>\033[0m   - Create a directory\n");
    printf("  \033[1;32mrmdir <dir>\033[0m   - Remove a directory\n");
    printf("  \033[1;32mrm <file>\033[0m     - Remove a file\n");
    printf("  \033[1;32mtouch <file>\033[0m  - Create an empty file\n");
    printf("  \033[1;32mcat <file>\033[0m    - Display file contents\n");
    printf("  \033[1;32mcp <src> <dest>\033[0m - Copy file\n");
    printf("  \033[1;32mmv <src> <dest>\033[0m - Move file\n");
    printf("  \033[1;32mclear\033[0m         - Clear the terminal screen\n");
    printf("  \033[1;32m...\033[0m (other commands are executed as external commands)\n");
}