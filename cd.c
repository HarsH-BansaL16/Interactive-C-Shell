#include "cd.h"

extern int and;

extern char *Home_Dir;

extern char **Exit_Command;
extern int exit_command;

extern int output_redirection;
extern int output_append;

void cd(char *Command, int *flag, char **Prev_Dir)
{
    // Getting the Current Working Directory
    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
    Curr_Dir = getcwd(Curr_Dir, 1000);

    char *token = (char *)malloc(sizeof(char) * 1000);
    token = strtok(Command, " \t\n");
    token = strtok(NULL, " \t\n");

    if (token != NULL)
    {
        char *token2 = (char *)malloc(sizeof(char) * 1000);
        strcpy(token2, token);
        token2 = strtok(NULL, " \t\n");
        if (token2 != NULL)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                RED
            }
            printf("Error: Too Many Arguements to Function Call");
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
            return;
        }
    }

    if (token == 0)
    {
        chdir(Home_Dir);
        if (*flag == -1)
        {
            *flag = 1;
        }
        *Prev_Dir = Curr_Dir;
        return;
    }

    if (strcmp(token, "..") == 0)
    {
        if (strcmp(Curr_Dir, Home_Dir) == 0)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                PWD_COLOR
            }
            printf("%s", Home_Dir);
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
        }
        chdir("..");
        if (*flag == -1)
        {
            *flag = 1;
        }
        *Prev_Dir = Curr_Dir;
        return;
    }
    else if (strcmp(token, "~") == 0)
    {
        int retval = chdir(Home_Dir);
        if (*flag == -1)
        {
            *flag = 1;
        }
        *Prev_Dir = Curr_Dir;
        if (retval == -1)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                RED_BACK
            }
            printf("cd: no such file or directory.");
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
        }
        return;
    }
    else if (strcmp(token, ".") == 0)
    {
        chdir(Curr_Dir);
        if (*flag == -1)
        {
            *flag = 1;
        }
        *Prev_Dir = Curr_Dir;
        return;
    }
    else if (strcmp(token, "-") == 0)
    {
        if (*flag == -1)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                RED
            }
            printf("bash: cd: OLDPWD not set");
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
        }
        else
        {
            printf("%s\n", *Prev_Dir);
            int retval = chdir(*Prev_Dir);
            *Prev_Dir = Curr_Dir;
        }
        return;
    }
    else
    {
        char *dir = (char *)malloc(sizeof(char) * 1000);
        for (int i = 0; i < strlen(token); i++)
        {
            dir[i] = token[i];
        }
        int retval = chdir(dir);
        if (retval != -1)
        {
            *Prev_Dir = Curr_Dir;
        }
        if (retval == -1)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                RED_BACK
            }
            if (strcmp(dir, "") == 0)
            {
                chdir(Home_Dir);
                if (*flag == -1)
                {
                    *flag = 1;
                }
                *Prev_Dir = Curr_Dir;
                return;
            }
            if (dir[0] == '~')
            {
                char *Temp_Dir = (char *)malloc(sizeof(char) * 1000);
                strcpy(Temp_Dir, Home_Dir);
                strcat(Temp_Dir, &dir[1]);
                chdir(Temp_Dir);
                if (*flag == -1)
                {
                    *flag = 1;
                }
                *Prev_Dir = Curr_Dir;
                return;
            }
            printf("cd: no such file or directory: %s", dir);
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
        }
        return;
    }
}