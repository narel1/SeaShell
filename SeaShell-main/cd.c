#include "cd.h"

#include "utils.h"

void handle_cd(char **cmd_list) {
    if (cmd_list[1] != NULL && cmd_list[2] == NULL) {
        cd(cmd_list[1]);
    } else {
        puts("Wrong number of arguments");
    }
}

void cd(char *path) {
    if (chdir(path) < 0) {
        puts("Could not change directory or path does not exist");
    }
}
