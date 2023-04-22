#ifndef __HISTORY__H__
#define __HISTORY__H__

#include "headers.h"

void Print_History(char *System_Root, char *Curr_Dir);

void Store_History(char *Command, char *Prev_Command, char *System_Root, char *Curr_Dir);

#endif