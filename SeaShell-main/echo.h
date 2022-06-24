#ifndef __ECHO_H
#define __ECHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_echo(char **cmd_list);
void echo(char *text);

#endif
