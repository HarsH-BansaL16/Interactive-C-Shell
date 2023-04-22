#include "pwd.h"

extern int and;

void Pwd()
{
    // Getting the Current Working Directory
    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);

    Curr_Dir = getcwd(Curr_Dir, 1000);

    PWD_COLOR
    printf("%s", Curr_Dir);
    RESET
    printf("\n");
}