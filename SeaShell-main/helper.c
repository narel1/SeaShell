#include "helper.h"

void handle_cmd(char* cmd, char* arr[]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Could not create the child process");
        return;
    }
    if (pid == 0) {
        execvp(
            cmd,
            arr);
    }
    waitpid(pid, NULL, 0);
}
