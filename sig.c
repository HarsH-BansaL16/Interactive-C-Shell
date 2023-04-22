#include "sig.h"

extern Background Processes[50];

pid_t Return_Pid(int Serial_Number)
{
    pid_t pid = -1;

    for (int i = 49; i >= 0; i--)
    {
        if (Processes[i].pid != -1)
        {
            if (Processes[i].Serial == Serial_Number)
            {
                pid = Processes[i].pid;
                break;
            }
        }
    }

    return pid;
}

void sig(char *Command)
{
    char *temp = (char *)malloc(sizeof(char *) * 1000);
    strcpy(temp, Command);

    temp = strtok(NULL, " \t\n");
    if (temp == NULL)
    {
        RED;
        printf("Error: Invalid Syntax");
        RESET;
        printf("\n");
        return;
    }

    int Serial_Number = atoi(temp);

    temp = strtok(NULL, " \t\n");
    if (temp == NULL)
    {
        RED;
        printf("Error: Invalid Syntax");
        RESET;
        printf("\n");
        return;
    }

    int Signal_Num = atoi(temp);

    pid_t pid = Return_Pid(Serial_Number);

    if (pid == -1)
    {
        RED
            printf("Error: No Job Exist");
        RESET
        printf("\n");
        return;
    }

    kill(pid, Signal_Num);
    return;
}