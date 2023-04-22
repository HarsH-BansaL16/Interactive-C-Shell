#include "history.h"

extern int and;

extern char *Home_Dir;

extern char ** Exit_Command;
extern int exit_command;

void Print_History(char *System_Root, char *Curr_Dir)
{
    chdir(System_Root);
    FILE *ptr = fopen(".history.txt", "r");

    char *buf = (char *)malloc(sizeof(char) * 100);
    int n = 0;
    size_t len;

    char **Files = (char **)malloc(sizeof(char *) * 20);

    while (getline(&buf, &len, ptr) != -1)
    {
        Files[n] = (char *)malloc(sizeof(char) * 100);
        strcpy(Files[n], buf);
        n++;
    }

    fclose(ptr);

    if (n > 10)
    {
        int z = 1;
        for (int i = n - 10; i < n; i++)
        {
            printf("[%d] %s", z, Files[i]);
            z++;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            printf("[%d] %s", i+1, Files[i]);
        }
    }
    chdir(Curr_Dir);

    return;
}

void Store_History(char *Command, char *Prev_Command, char *System_Root, char *Curr_Dir)
{
    if (strcmp(Command, "\n") == 0)
    {
        return;
    }
    chdir(System_Root);
    if (strcmp(Command, Prev_Command) != 0)
    {
        FILE *ptr = fopen(".history.txt", "r");

        char *buf = (char *)malloc(sizeof(char) * 100);

        int n = 0;

        size_t len;

        char **Files = (char **)malloc(sizeof(char *) * 20);

        while (getline(&buf, &len, ptr) != -1)
        {
            Files[n] = (char *)malloc(sizeof(char) * 100);
            strcpy(Files[n], buf);
            n++;
        }
        fclose(ptr);

        Files[n] = (char *)malloc(sizeof(char) * 100);
        strcpy(Files[n], Command);

        if (n > 1)
        {
            if (strcmp(Files[n], Files[n - 1]) == 0)
            {
                chdir(Curr_Dir);
                return;
            }
        }

        ptr = fopen(".history.txt", "w");

        if (n < 20)
        {
            for (int i = 0; i < n + 1; i++)
            {
                fprintf(ptr, "%s", Files[i]);
            }
        }
        else
        {
            for (int i = 1; i < n + 1; i++)
            {
                fprintf(ptr, "%s", Files[i]);
            }
        }

        fclose(ptr);
    }
    chdir(Curr_Dir);
    return;
}
