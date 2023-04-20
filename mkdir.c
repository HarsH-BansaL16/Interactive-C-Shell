#include "mkdir.h"

extern int and;

void my_mkdir(char *Command, char *Curr_Dir)
{
    chdir(Curr_Dir);

    char *token = (char *)malloc(sizeof(char) * 1000);
    token = strtok(Command, " \t\n");
    token = strtok(NULL, " \t\n");

    int retval = mkdir(token, 0777);
    if (retval == -1)
    {
        printf("\033[0;31m");
        printf("mkdir: %s: %s\n", token, strerror(errno));
    }

    return;
}