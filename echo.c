#include "echo.h"

extern int and;

extern char *Home_Dir;

extern char **Exit_Command;
extern int exit_command;

extern int output_redirection;
extern int output_append;

void Echo(char *Command)
{
    if (output_append == 0 && output_redirection == 0)
    {
        YELLOW
    }
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
    if (output_append == 0 && output_redirection == 0)
    {
        RESET
    }
    printf("\n");

    free(token);

    return;
}
