#ifndef __PARSE_H
#define __PARSE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void get_input();
void handle_command(char *command);
void first_stage_parse_input(char *input);

#endif