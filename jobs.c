#include "jobs.h"

extern char **Exit_Command;
extern int exit_command;

extern Background Processes[50];

void jobs(char *Command)
{
    MAGENTA

    bool flag_r = false;
    bool flag_s = false;

    for (int i = 0; i < strlen(Command); i++)
    {
        if (Command[i] == '-')
        {
            if (Command[i + 1] == 's')
            {
                flag_s = true;
            }
            else if (Command[i + 1] == 'r')
            {
                flag_r = true;
            }
        }
    }

    if (flag_r == false && flag_s == false)
    {
        flag_r = true;
        flag_s = true;
    }

    char **Files = (char **)malloc(sizeof(char *) * 100);
    int count = 0;
    for (int i = 0; i < 50; i++)
    {
        if (Processes[i].pid != -1)
        {
            Files[count] = (char *)malloc(sizeof(char) * 1000);
            strcpy(Files[count], Processes[i].Command);
            count++;
        }
    }

    // Sorting Algorithm
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (strcmp(Files[j], Files[j + 1]) > 0)
            {
                char *temp = (char *)malloc(sizeof(char) * 1000);
                strcpy(temp, Files[j]);
                strcpy(Files[j], Files[j + 1]);
                strcpy(Files[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (Processes[j].pid != -1)
            {
                if (strcmp(Processes[j].Command, Files[i]) == 0 && Processes[j].Flag == 0)
                {
                    // Making the File Name
                    char *Open_File = (char *)malloc(sizeof(char) * 100);
                    
                    strcpy(Open_File, "/proc/");

                    char *temp = (char *)malloc(sizeof(char) * 100);
                    sprintf(temp, "%d", Processes[j].pid);

                    strcat(Open_File, temp);
                    strcat(Open_File, "/stat");

                    char State;

                    FILE *ptr = fopen(Open_File, "r");
                    if (ptr == NULL)
                    {
                        State = 'T';
                    }
                    else
                    {
                        fscanf(ptr, "%*d %*s %c", &State);
                        fclose(ptr);
                    }

                    if (State == 'T' && flag_s == true)
                    {
                        printf("[%d] %s %s [%d]\n", Processes[j].Serial, "Stopped", Processes[j].Command, Processes[j].pid);
                    }
                    else if (flag_r == true && State != 'T')
                    {
                        printf("[%d] %s %s [%d]\n", Processes[j].Serial, "Running", Processes[j].Command, Processes[j].pid);
                    }

                    Processes[j].Flag = 1;
                    break;
                }
            }
        }
    }

    for (int j = 0; j < 50; j++)
    {
        Processes[j].Flag = 0;
    }

    RESET

    return;
}