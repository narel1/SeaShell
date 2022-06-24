#include "shell.h"

#include "parse.h"
#include "utils.h"

int main() {
    initialize_everything();

    while (true) {
        handle_input();
    }

    return 0;
}

void handle_input() {
    get_input();
    prompt();
}
