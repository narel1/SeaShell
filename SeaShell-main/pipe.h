#ifndef __PIPE_H
#define __PIPE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int count_pipes(const char* command);
char** segregate_commands(char* commands_str);
void second_stage_parse_commands(char* commands);

#endif
