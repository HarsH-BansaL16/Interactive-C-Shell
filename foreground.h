#ifndef __FOREGROUND_H__
#define __FOREGROUND_H__

#include "headers.h"

void UpdateForeGroundProcess(pid_t pid, char * Command);
void RemoveForeGroundProcess(pid_t pid);

#endif