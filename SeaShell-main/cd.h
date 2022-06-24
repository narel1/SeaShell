#ifndef __CD_H
#define __CD_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_cd(char **cmd_list);
void cd(char *path);

#endif