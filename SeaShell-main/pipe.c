#include "pipe.h"

#include "redirection.h"
#include "utils.h"

int count_pipes(const char* command) {
    int pipes_count = 0;
    for (int i = 0; i < strlen(command); i++) {
        if (command[i] == '|') {
            pipes_count++;
        }
    }
    return pipes_count;
}

char** segregate_commands(char* commands_str) {
    int num_commands = count_pipes(commands_str) + 1;

    char** commands = (char**)malloc(sizeof(char*) * (num_commands + 1));
    commands[num_commands] = NULL;

    int i = 0;
    char* next = strtok(commands_str, "|");
    while (next != NULL) {
        next = trim(next, ' ');
        next = trim(next, '\n');
        commands[i] = (char*)malloc(sizeof(char) * (strlen(next) + 1));
        strcpy(commands[i++], next);
        next = strtok(NULL, "|");
    }

    return commands;
}

void second_stage_parse_commands(char* commands_str) {
    // Here we handle the piping between the processes.
    size_t num_commands = count_pipes(commands_str) + 1;
    if (num_commands == 1) {
        // No piping found.
        third_stage_parse_command(commands_str);
        return;
    }

    char** commands = segregate_commands(commands_str);

    int fd[num_commands - 1][2];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(fd[i]) < 0) {
            perror("Some error occured while creating the pipes");
            destroy_tokens(commands);
            free(commands);
            return;
        }
    }

    int* pid_list = (int*)malloc(sizeof(int) * num_commands);

    for (int i = 0; i < num_commands; i++) {
        pid_list[i] = fork();
        if (pid_list[i] < 0) {
            perror("Some error occured while creating the pipes");
            destroy_tokens(commands);
            free(commands);
            free(pid_list);
            return;
        }
        if (pid_list[i] == 0) {
            // In Child: It will execute the further commands.
            for (int j = 0; j < num_commands - 1; j++) {
                if (j != (i - 1)) {
                    close(fd[j][0]);
                }
                if (j != i) {
                    close(fd[j][1]);
                }
            }

            if (i > 0 && dup2(fd[i - 1][0], STDIN_FILENO) < 0) {
                perror("Some error occured");
                destroy_tokens(commands);
                free(commands);
                free(pid_list);
                return;
            }

            if (i < (num_commands - 1) && dup2(fd[i][1], STDOUT_FILENO) < 0) {
                perror("Some error occured");
                destroy_tokens(commands);
                free(commands);
                free(pid_list);
                return;
            }

            if (i > 0) {
                close(fd[i - 1][0]);
            }
            if (i < (num_commands - 1)) {
                close(fd[i][1]);
            }

            third_stage_parse_command(commands[i]);
            exit(0);
        }
    }

    for (int i = 0; i < num_commands - 1; i++) {
        // These fds are closed by the parent.
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (int i = 0; i < num_commands; i++) {
        waitpid(pid_list[i], NULL, 0);
    }

    destroy_tokens(commands);
    free(commands);
    free(pid_list);
}
