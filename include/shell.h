#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

// Function Declarations
void start_shell();
void execute_command(char **args);
void handle_builtin(char **args);
void parse_input(char *input, char **args);
void print_banner();
void print_prompt();
void print_help();

#endif