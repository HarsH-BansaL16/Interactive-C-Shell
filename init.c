#include "init.h"

extern int and;

extern Background Processes[50];
extern Background ForeGround[50];
extern int time_spent;

extern char **Exit_Command;

extern int exit_command;

extern char *Home_Dir;

extern int stdout_ptr;
extern int stdin_ptr;

extern int Ctrl_C;

void Control_Z()
{
    int count = 0;
    pid_t pid;
    int index;
    for (int i = 0; i < 49; i++)
    {
        if (ForeGround[i].pid != -1)
        {
            pid = ForeGround[i].pid;
            index = i;
            count++;
        }
    }
    if (count == 0)
    {
        return;
    }

    setpgid(0, 0);

    kill(pid,SIGTSTP);

    UpdateProcess(pid,ForeGround[index].Command);

    time_spent = 0;

    return;
}

void Control_C()
{
    Ctrl_C = 1;
    time_spent = 0;
    return;
}

void Init(char *System_Root)
{
    stdout_ptr = dup(1);
    stdin_ptr = dup(0);

    and = 0;
    printf("\e[1;1H\e[2J");

    MAGENTA
    printf("Welcome to Harsh's Shell!\n\n");
    RESET

    chdir(System_Root);
    FILE *ptr = fopen(".history.txt", "r");

    if (ptr == NULL)
    {
        ptr = fopen(".history.txt", "w");
        fclose(ptr);
    }
    else
    {
        fclose(ptr);
    }

    chdir(Home_Dir);

    Exit_Command = (char **)malloc(sizeof(char *) * 50);

    for (int i = 0; i < 50; i++)
    {
        Processes[i].pid = -1;
        ForeGround[i].pid = -1;
    }
}