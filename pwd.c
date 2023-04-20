#include "pwd.h"

extern int and;

void Pwd()
{
    // Getting the Current Working Directory
    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);

    Curr_Dir = getcwd(Curr_Dir, 1000);

    printf("\033[0;44m");
    printf("%s", Curr_Dir);
    RESET
    printf("\n");
}