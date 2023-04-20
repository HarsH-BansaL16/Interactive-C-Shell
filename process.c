#include "process.h"

extern int and;
extern int time_spent;

extern char *Home_Dir;

extern char **Exit_Command;
extern int exit_command;

extern Background Processes[50];

void Check_Exit_Status()
{
    int status;
    int wait_status;
    for (int i = 0; i < 50; i++)
    {
        if (Processes[i].pid != -1)
        {
            pid_t pid = Processes[i].pid;
            wait_status = waitpid(pid, &status, WNOHANG);
            if (wait_status == 0)
            {
                // Not Exited
                continue;
            }
            else
            {
                PrintExitProcess(pid, WIFEXITED(status) ? 1 : 0);
            }
        }
    }
    return;
}

void PrintCompletedProcess()
{
    for (int i = 0; i < exit_command; i++)
    {
        YELLOW
        printf("%s", Exit_Command[i]);
        RESET
    }
    exit_command = 0;
}

void Handler()
{
    int status;
    RESET
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid != -1)
    {
        PrintExitProcess(pid, WIFEXITED(status) ? 1 : 0);
    }
    return;
}

void UpdateProcess(pid_t pid, char *Command)
{
    for (int i = 0; i < 50; i++)
    {
        if (Processes[i].pid == -1)
        {
            Processes[i].pid = pid;
            Processes[i].Command = Command;
            Processes[i].Serial = i + 1;
            return;
        }
    }
    return;
}

void PrintBeginProcess(pid_t pid)
{
    for (int i = 0; i < 50; i++)
    {
        if (Processes[i].pid == pid)
        {
            MAGENTA
            printf("[%d] %d\n", Processes[i].Serial, pid);
            RESET
            return;
        }
    }
    return;
}

void PrintExitProcess(pid_t pid, int flag)
{
    // When Flag == 1 --> Exited Normally
    // When Flag == 0 --> Exited Abnormally
    for (int i = 0; i < 50; i++)
    {
        if (Processes[i].pid == pid)
        {
            Exit_Command[exit_command] = (char *)malloc(sizeof(char) * 1000);
            sprintf(Exit_Command[exit_command++], "%s with pid = %d exited %s\n", Processes[i].Command, pid, flag ? "normally" : "abnormally");
            Processes[i].pid = -1;
            return;
        }
    }
    return;
}

void BackGround(char *Command, char **Argv)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        setpgrp();
        // Child Process.
        int retval = execvp(Command, Argv);

        if (retval == -1)
        {
            printf("\033[0;31m");
            if (strcmp(&Command[strlen(Command) - 1], "\n") == 0)
            {
                char *temp = (char *)malloc(sizeof(char) * 1000);
                strncpy(temp, Command, strlen(Command) - 1);

                printf("bash: %s: command not found\n", temp);
                exit(0);
                return;
            }

            printf("bash: %s: command not found\n", Command);
            exit(0);
            return;
        }
    }
    else
    {
        // Parent Process
        UpdateProcess(pid, Command);
        PrintBeginProcess(pid);

        return;
    }
}
