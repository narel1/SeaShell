#include "parse.h"

#include "cd.h"
#include "echo.h"
#include "helper.h"
#include "pipe.h"
#include "utils.h"

void get_input() {
    char *line = (char *)malloc(sizeof(char) * MAX_INPUT_SIZE);

    fgets(line, MAX_INPUT_SIZE, stdin);
    if (strlen(line) != 1 && line[0] != '\n') {
        first_stage_parse_input(line);
    }
    free(line);
}

void handle_command(char *command) {
    char **cmd_list = tokenize(command, ' ');
    char *cmd = cmd_list[0];

    if (strcmp(cmd, "cd") == 0) {
        handle_cd(cmd_list);
    } else if (strcmp(cmd, "echo") == 0) {
        handle_echo(cmd_list);
    } else if (strcmp(cmd, "clear") == 0) {
        printf(ANSI_CLEAR);
    } else if (strcmp(cmd, "exit") == 0) {
        exit_shell();
    } else {
        handle_cmd(cmd, cmd_list);
    }

    destroy_tokens(cmd_list);
}

void first_stage_parse_input(char *input) {
    // At first stage, we segregate strings by `;;`.
    const char *delim = ";;";
    char *saveptr;
    char *next = strtok_r(input, delim, &saveptr);
    while (next != NULL) {
        // In the 2nd stage, we deal with pipes.
        next = trim(next, ' ');
        next = trim(next, '\n');
        second_stage_parse_commands(next);
        next = strtok_r(NULL, delim, &saveptr);
    }
}
