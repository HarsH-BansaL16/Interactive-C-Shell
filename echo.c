#include "echo.h"

extern int and;

extern char *Home_Dir;

extern char ** Exit_Command;
extern int exit_command;

void Echo(char *Command)
{
    printf("\033[0;33m");

    char *token = (char *)malloc(sizeof(char) * 1000);
    token = strtok(Command, " \t\n");
    token = strtok(NULL, " \t\n");

    while (token != NULL)
    {
        if (strcmp(token, "~") == 0)
        {
            token = Home_Dir;
        }
        printf("%s ", token);

        token = strtok(NULL, " \t\n");
    }
    printf("\n");

    free(token);

    return;
}
