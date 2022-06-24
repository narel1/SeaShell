#include "utils.h"

#include "signals.h"

void initialize_everything() {
    printf(ANSI_CLEAR);
    {
        const char rocket[] =
            "                       ^ \n\
                      /^\\\n\
                      |-|\n\
                      | |\n\
                      |S|\n\
                      |E|\n\
                      |A|\n\
                      |S|\n\
                      |H|\n\
                      |E|\n\
                     /|L|\\\n\
                    / |L| \\\n\
                   |  | |  |\n\
                    `-\"\"\"-`\n\
";
        fputs(rocket, stdout);
    }
    printf(ANSI_YELLOW_BOLD "\n\t***\tWelcome to SeaShell\t***\t\n" ANSI_DEFAULT);

    initialize_signals();
    prompt();
}

void prompt() {
    printf("\nSeaShell > ");
    fflush(stdout);
}

char **tokenize(char *line, char delim) {
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for (i = 0; i < strlen(line); i++) {
        char readChar = line[i];
        if (readChar == delim) {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0) {
                token = trim(token, ' ');
                token = trim(token, '\n');
                tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0;
            }
        } else {
            if (readChar != '\n' && readChar != '\t') {
                token[tokenIndex++] = readChar;
            }
        }
    }

    if (tokenIndex != 0) {
        // This means that we are at the end of the
        // string and it has not been copied yet.
        token[tokenIndex] = '\0';
        token = trim(token, ' ');
        token = trim(token, '\n');
        tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
        strcpy(tokens[tokenNo++], token);
    }
    // TODO: free(token) gives error here. Need to debug for it.
    tokens[tokenNo] = NULL;
    return tokens;
}

void destroy_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
}

char *concat(char *str1, char *str2) {
    // strcat using pointers.
    char *res = malloc(strlen(str1) + strlen(str2) + 1);
    int i = 0, curr_pos = 0;
    while (str1[i] != '\0') {
        res[curr_pos++] = str1[i++];
    }
    i = 0;
    while (str2[i] != '\0') {
        res[curr_pos++] = str2[i++];
    }
    return res;
}

char *trim(char *str, char ch) {
    // This function behaves same as the python/js trim function.
    // We don't modifiy the original pointer so that we can later free the memory.

    char *t = str;
    while (*t == ch) {
        t++;
    }

    for (int i = strlen(t) - 1; t[i] == ch; i--) {
        t[i] = '\0';
    }

    return t;
}

void exit_shell() {
    printf("\nClosed all Background processes\n");
    exit(0);
}
