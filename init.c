#include "init.h"

extern int and;

extern Background Processes[50];

extern char ** Exit_Command;
extern int exit_command;

extern char *Home_Dir;

void Init(char * System_Root)
{
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
    }
}