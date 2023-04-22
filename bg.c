#include "bg.h"

extern Background Processes[50];

void bg_handle(char *Command)
{
    char *token = (char *)malloc(sizeof(char *) * 1000);
    strcpy(token, Command);

    token = strtok(NULL, " \t\n");
    if (token == NULL)
    {
        RED;
        printf("Error: Invalid Syntax");
        RESET;
        printf("\n");
        return;
    }

    int Serial_Number = atoi(token);

    pid_t pid = Return_Pid(Serial_Number);

    // Process with Particular Serial Number doesnot Exist
    if (pid == -1)
    {
        RED;
        printf("Error: No Job Exist");
        RESET;
        printf("\n");
        return;
    }

    char *File_Path = (char *)malloc(sizeof(char) * 1000);

    // Making the File Path
    strcpy(File_Path, "/proc/");

    char *temp = (char *)malloc(sizeof(char) * 100);
    sprintf(temp, "%d", pid);

    strcat(File_Path, temp);
    strcat(File_Path, "/stat");

    char State;

    FILE *ptr = fopen(File_Path, "r");
    if (ptr == NULL)
    {
        State = 'T';
    }
    else
    {
        fscanf(ptr, "%*d %*s %c", &State);
        fclose(ptr);
    }

    if (State != 'T')
    {
        return;
    }

    // Sending the SIGCONT to the Process.
    if (kill(pid, SIGCONT) < 0)
    {
        perror("Error");
        return;
    }

    return;
}