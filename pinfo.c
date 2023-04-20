#include "pinfo.h"

extern int and;

void P_Info(char *Command)
{
    // Creating File Path
    char *token = (char *)malloc(sizeof(char) * 1000);
    strcpy(token, Command);

    token = strtok(Command, " \t\n");
    token = strtok(NULL, " \t\n");

    char *Open_File = (char *)malloc(sizeof(char) * 100);
    strcpy(Open_File, "/proc/");

    if (token == NULL)
    {
        strcat(Open_File, "self/");
    }
    else
    {
        strcat(Open_File, token);
        strcat(Open_File, "/");
    }
    char *Temp_Dir = (char *)malloc(sizeof(char) * 100);
    strcpy(Temp_Dir, Open_File);

    strcat(Open_File, "stat");

    FILE *ptr = fopen(Open_File, "r");
    // Error Handling
    if (ptr == NULL)
    {
        RED;
        if (token == NULL)
        {
            printf("Error: The Process does not Exist.");
        }
        else
        {
            printf("Error: The Process with PID = %s does not Exist.", token);
        }
        RESET;
        printf("\n");
        return;
    }

    int pid, pgrp, tpgid, vm_memory, ppid;
    char State;

    char *buf = (char *)malloc(sizeof(char) * 1000);
    int dummy_var = 0;

    // Reading from the Stat File
    fscanf(ptr, "%d %s %c %d %d %d %d %d", &pid, buf, &State, &ppid, &pgrp, &dummy_var, &dummy_var, &tpgid);

    fclose(ptr);

    // Reading from the Status File
    strcat(Open_File, "us");
    ptr = fopen(Open_File, "r");
    if (ptr == NULL)
    {
        RED if (token == NULL)
        {
            printf("Error: The Process does not Exist.");
        }
        else
        {
            printf("Error: The Process with PID = %s does not Exist.", token);
        }
        RESET
        printf("\n");
        return;
    }

    int n = 0;
    size_t len;

    char **Files = (char **)malloc(sizeof(char *) * 100);

    while (fgets(buf, 100, ptr))
    {
        Files[n] = (char *)malloc(sizeof(char) * 100);
        strcpy(Files[n], buf);
        n++;
    }

    fclose(ptr);

    YELLOW
    printf("pid : %d", pid);
    RESET
    printf("\n");

    YELLOW
    if (tpgid == pgrp)
    {
        printf("process Status : %c+", State);
    }
    else
    {
        printf("process Status : %c", State);
    }
    RESET
    printf("\n");

    char *vmsize = (char *)malloc(sizeof(char) * 100);
    strcpy(vmsize, &Files[17][7]);
    vmsize = strtok(vmsize, " \t\n");

    YELLOW
    printf("memory : %s {Virtual Memory}", vmsize);
    RESET
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        free(Files[i]);
    }

    // Reading from the Exe File.
    strcat(Temp_Dir, "exe\0");
    char *Exec_Path = (char *)malloc(sizeof(char) * 1000);
    ssize_t Length = readlink(Temp_Dir, Exec_Path, 990);
    Exec_Path[Length] = '\0';

    YELLOW
    printf("executable Path : %s", Exec_Path);
    RESET
    printf("\n");

    return;
}
