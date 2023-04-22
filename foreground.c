#include "foreground.h"

extern Background ForeGround[50];

void UpdateForeGroundProcess(pid_t pid, char *Command)
{
    for (int i = 0; i < 49; i++)
    {
        if (ForeGround[i].pid == -1)
        {
            ForeGround[i].pid = pid;
            ForeGround[i].Command = Command;
            ForeGround[i].Serial = i + 1;
        }
    }
}

void RemoveForeGroundProcess(pid_t pid)
{
    for (int i = 0; i < 49; i++)
    {
        if (ForeGround[i].pid == pid)
        {
            ForeGround[i].pid = -1;
        }
    }
}