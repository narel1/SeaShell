#include "redirection.h"

#include "parse.h"
#include "utils.h"

void third_stage_parse_command(char* command) {
    // 3rd stage: this is the final stage before
    // actually executing the command.
    //
    // Here we check for redirection.
    char** tokens = tokenize(command, '>');
    char* cmd = tokens[0];
    char* filename = tokens[1];

    if (filename == NULL) {
        // No redirection found.
        handle_command(cmd);
        destroy_tokens(tokens);
        free(tokens);
        return;
    }
    // create space of redirection.
    pid_t pid = fork();
    if (pid == -1) {
        perror("Could not create the child process");
        destroy_tokens(tokens);
        free(tokens);
        return;
    }
    if (pid == 0) {
        int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (file == -1) {
            perror("could not open the file");
            destroy_tokens(tokens);
            free(tokens);
            return;
        }
        int file2 = dup2(file, STDOUT_FILENO);
        close(file);

        handle_command(cmd);

        close(file2);
        exit(0);
    } else {
        wait(NULL);
    }

    destroy_tokens(tokens);
    free(tokens);
}
