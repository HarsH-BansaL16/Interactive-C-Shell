#include "prompt.h"

extern int and;

extern int time_spent;

extern char **Exit_Command;
extern int exit_command;

extern int Ctrl_C;

extern char *Home_Dir;

extern int stdout_ptr;
extern int stdin_ptr;

extern int output_redirection;
extern int output_append;
extern int input_redirection;

void Reset_IO_Direction()
{
    // Configuring the Stdin and Stdout
    dup2(stdout_ptr, 1);
    dup2(stdin_ptr, 0);
    output_redirection = 0;
    output_append = 0;
    input_redirection = 0;
}

void prompt()
{
    Reset_IO_Direction();

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
    if (time_spent >= 1 && Ctrl_C == 0)
    {
        printf("\033[0;35m");
        printf(" took %ds ", time_spent);
    }
    time_spent = 0;
    printf("\033[0;32m");
    printf("> ");
    printf("\033[0;36m");

    Ctrl_C = 0;
}