#include "fg.h"

extern Background Processes[50];
extern int time_spent;

void fg(char *Command)
{
    char *token = (char *)malloc(sizeof(char *) * 1000);
    strcpy(token, Command);

    token = strtok(NULL, " \t\n");
    if (token == NULL)
    {
        RED;
        printf("Error: Invalid Syntax");
        RESET;
        printf("\n");
        time_spent = 0;
        return;
    }

    int Serial_Number = atoi(token);

    pid_t pid = Return_Pid(Serial_Number);

    // Process with Particular Serial Number doesnot Exist
    if (pid == -1)
    {
        RED;
        printf("Error: No Job Exist");
        RESET;
        printf("\n");
        time_spent = 0;
        return;
    }

    // Setting the pgid of the Given Pid to that of Foreground Processes.
    setpgid(pid, getpgid(0));

    // Setting the Background Input Signal to be Ignored.
    signal(SIGTTIN, SIG_IGN);
    // Setting the Background Output Signal to the Ignored.
    signal(SIGTTOU, SIG_IGN);

    // Setting the Pid to become a Foreground Process.
    tcsetpgrp(0, pid);

    // Continuing the Process in Foreground
    kill(pid, SIGCONT);

    for (int i = 0; i < 49; i++)
    {
        if (Processes[i].pid == pid)
        {
            Processes[i].pid = -1;
        }
    }

    int status;
    waitpid(pid, &status, WUNTRACED);

    time_spent = time(NULL) - time_spent;

    tcsetpgrp(0, getpgid(0));

    // Setting the Background I/O to their Default Values.
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    return;
}