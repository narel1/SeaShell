#include "echo.h"

#include "utils.h"

void handle_echo(char **cmd_list) {
    // TODO: Here we need to separate out the flags from the text.
    // As of now this doesn't support any flags.
    int i = 1;
    char *text = "";
    while (cmd_list[i] != NULL) {
        text = concat(text, cmd_list[i]);
        i++;
        if (cmd_list[i] != NULL) {
            // Join strings with white spaces.
            char *whitespace = " ";
            text = concat(text, whitespace);
        }
    }

    text = trim(text, '"');
    text = trim(text, '\'');

    echo(text);
}

void echo(char *text) {
    char *arr[] = {"echo", text, NULL};
    pid_t pid = fork();
    if (pid < 0) {
        perror("Could not create the child process");
        return;
    }
    if (pid == 0) {
        execvp(
            "echo",
            arr);
    }
    wait(NULL);
}
