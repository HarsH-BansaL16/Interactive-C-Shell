#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "headers.h"

void BackGround(char *Command, char **Argv);

void UpdateProcess(pid_t pid , char * Command);

void PrintBeginProcess(pid_t pid);

void PrintExitProcess(pid_t pid, int flag);

void Handler();

void PrintCompletedProcess();

void Check_Exit_Status();

#endif