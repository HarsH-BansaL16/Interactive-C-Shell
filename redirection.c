#include "redirection.h"

extern int output_redirection;
extern int output_append;
extern int input_redirection;
extern int fd_ptr;

bool Check_Extra_Arguements(char *token)
{
    char *temp = (char *)malloc(sizeof(char) * 1000);
    strcpy(temp, token);

    temp = strtok(token, " ");
    temp = strtok(NULL, " ");
    if (temp != NULL && strcmp(temp, ">") != 0)
    {
        printf("%s\n", temp);
        RED;
        printf("Error: Incorrect Syntax");
        RESET;
        printf("\n");
        return false;
    }
    return true;
}

char *HandleRedirection(char *Command_Duplicate)
{
    char *Command = (char *)malloc(sizeof(char) * 1000);
    strcpy(Command, Command_Duplicate);

    // Handling Input Redirection
    if (input_redirection == 1)
    {
        char *File_Name = (char *)malloc(sizeof(char) * 1000);
        char *token = (char *)malloc(sizeof(char) * 1000);
        strcpy(File_Name, Command);

        token = strtok(File_Name, "<");
        trimwhitespace(token);

        strcpy(Command, token);

        token = strtok(NULL, "<");

        trimwhitespace(token);

        bool a = Check_Extra_Arguements(token);
        if (a == false)
        {
            return "false";
        }

        File_Name = Extract_Command(token);

        File_Name[strlen(File_Name)] = '\0';

        FILE *ptr = fopen(File_Name, "r");

        if (ptr == NULL)
        {
            RED;
            printf("Error: Input File Does not Exist");
            RESET;
            printf("\n");
            return "false";
        }
        else
        {
            fclose(ptr);
            fd_ptr = open(File_Name, O_RDONLY);
            dup2(fd_ptr, 0);
        }
    }

    // Handling Output Redirection.
    if (output_redirection == 1)
    {
        char *File_Name = (char *)malloc(sizeof(char) * 1000);
        char *token = (char *)malloc(sizeof(char) * 1000);
        strcpy(File_Name, Command_Duplicate);
        for (int i = 0; i < strlen(Command_Duplicate); i++)
        {
            if (Command_Duplicate[i] == '>')
            {
                if (Command_Duplicate[i + 1] == '>')
                {
                    // Appending the File.
                    output_append = 1;
                    strcpy(File_Name, &Command_Duplicate[i + 2]);
                    File_Name = strtok(File_Name, " \t\n");

                    char *temp = (char *)malloc(sizeof(char) * 1000);

                    token = strtok(Command_Duplicate, ">>");
                    trimwhitespace(token);
                    strtok(Command_Duplicate, token);

                    if (token != NULL)
                    {
                        token = strtok(NULL, " \t\n");
                        if (token != NULL)
                        {
                            RED;
                            printf("Error: Incorrect Syntax");
                            RESET;
                            printf("\n");
                            File_Name = NULL;
                        }
                    }
                    break;
                }
                else
                {
                    // Writing to a File
                    output_append = 0;
                    char *temp = (char *)malloc(sizeof(char) * 1000);
                    token = strtok(File_Name, ">");
                    strcpy(Command_Duplicate, File_Name);
                    token = strtok(NULL, " \t\n");
                    if (token != NULL)
                    {
                        strcpy(temp, token);
                        strcpy(File_Name, temp);
                    }
                    else
                    {
                        RED;
                        printf("Error: Incorrect Syntax");
                        RESET;
                        printf("\n");
                        File_Name = NULL;
                    }
                    break;
                }
            }
        }
        if (input_redirection == 0)
        {
            // strcpy(Final_Command, Extract_Command(Command_Duplicate));
            strcpy(Command, Command_Duplicate);
        }
        if (File_Name == NULL)
        {
            return "false";
        }
        else if (output_append == 1)
        {
            fd_ptr = open(File_Name, O_CREAT | O_APPEND | O_WRONLY, 0644);
            dup2(fd_ptr, 1);
        }
        else if (output_redirection == 1)
        {
            fd_ptr = open(File_Name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_ptr == -1)
            {
                fd_ptr = open(File_Name, 0644);
            }
            dup2(fd_ptr, 1);
        }
    }

    return Command;
}