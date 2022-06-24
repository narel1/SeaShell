#ifndef __REDIRECTION_H
#define __REDIRECTION_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void third_stage_parse_command(char *command);

#endif
