#ifndef __DISCOVER_H__
#define __DISCOVER_H__

#include "headers.h"

void Find(char *Curr_Dir, char *Final_Dest, bool flag_d, bool flag_f);
void Print_Discover(char *Curr_Dir, bool flag_d, bool flag_f);
void Discover(char *Command, char *Curr_Dir);

#endif