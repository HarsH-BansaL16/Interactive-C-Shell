#include "prompt.h"

extern int and;

extern int time_spent;

extern char ** Exit_Command;
extern int exit_command;

extern char *Home_Dir;

void Prompt()
{
    and = 0;

    char *User_Name = (char *)malloc(sizeof(char) * 1000);
    User_Name = getlogin();

    struct utsname unameData;
    uname(&unameData);

    char *Host_Name = (char *)malloc(sizeof(char) * 1000);
    // Host_Name = unameData.sysname;

    gethostname(Host_Name, 1000);

    // Getting the Current Working Directory
    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
    Curr_Dir = getcwd(Curr_Dir, 1000);

    Curr_Dir = HandleDirectory(Curr_Dir);

    if (exit_command > 0)
    {
        PrintCompletedProcess();
        exit_command = 0;
    }

    printf("\033[0;32m");
    printf("<%s@%s:", User_Name, Host_Name);
    printf("\033[0;34m");
    printf("%s", Curr_Dir);
    if (time_spent >= 1)
    {
        printf("\033[0;35m");
        printf(" took %ds ", time_spent);
    }
    time_spent = 0;
    printf("\033[0;32m");
    printf("> ");
    printf("\033[0;36m");
}