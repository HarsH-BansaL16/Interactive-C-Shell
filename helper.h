#ifndef __HELPER_H__
#define __HELPER_H__

#include "headers.h"

void trimwhitespace(char *str);
char *HandleDirectory(char *Curr_Dir);
char *Extract_Command(char *Command);
void HandleCommand(char *Final_Command, char *Command, char **Prev_Dir, int *flag, char *System_Root);

#endif