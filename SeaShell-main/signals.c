#include "signals.h"

#include "utils.h"

void initialize_signals() {
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
}

void signal_handler(int signal_number) {
    if (signal_number == SIGINT || signal_number == SIGTSTP) {
        // End SHELL only if `exit` cmd is passed.
        prompt();
    }
}
