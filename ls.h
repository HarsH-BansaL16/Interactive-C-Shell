#ifndef __LS__H__
#define __LS__H__

#include "headers.h"

void LS(char *Command, char *Curr_Dir);
void Only_LS_a(char *Curr_Dirr);
void Only_LS(char *Curr_Dir);
void LS_L(bool flag_a, char *Curr_Dir);
void Color_Coding(char *File_Name);
void Color_Coding_without_Directory(char *File_Name);

#endif