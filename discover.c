#include "discover.h"

extern int and;

extern char *Home_Dir;
extern char ** Exit_Command;
extern int exit_command;

void Find(char *Curr_Dir, char *Final_Dest, bool flag_d, bool flag_f)
{
    DIR *Directory;
    struct dirent *Read_Directory;

    Directory = opendir(Curr_Dir);

    char Full_Curr_Dir[1000];

    if (Directory != NULL)
    {
        while ((Read_Directory = readdir(Directory)) != NULL)
        {
            if (Read_Directory->d_name[0] == '.')
            {
                continue;
            }
            // If it is a File
            if (Read_Directory->d_type == DT_REG)
            {
                Full_Curr_Dir[0] = '\0';
                strcat(Full_Curr_Dir, Curr_Dir);
                strcat(Full_Curr_Dir, "/");
                strcat(Full_Curr_Dir, Read_Directory->d_name);

                if (strcmp(Final_Dest, Read_Directory->d_name) == 0)
                {
                    // Found the File.
                    if (flag_f == true)
                    {
                        Color_Coding(Full_Curr_Dir);
                    }
                    return;
                }
            }
            else if (Read_Directory->d_type == DT_DIR)
            {
                Full_Curr_Dir[0] = '\0';
                strcat(Full_Curr_Dir, Curr_Dir);
                strcat(Full_Curr_Dir, "/");
                strcat(Full_Curr_Dir, Read_Directory->d_name);

                if (strcmp(Final_Dest, Read_Directory->d_name) == 0)
                {
                    if (flag_d == true)
                    {
                        Color_Coding(Full_Curr_Dir);
                    }
                    return;
                }
                else
                {
                    // This is not the Required Directory.
                    // Traversing it's Subdirectories.

                    strcpy(Full_Curr_Dir, Curr_Dir);
                    if (Full_Curr_Dir[strlen(Full_Curr_Dir) - 1] == '/')
                    {
                        strcat(Full_Curr_Dir, Read_Directory->d_name);
                    }
                    else
                    {
                        strcat(Full_Curr_Dir, "/");
                        strcat(Full_Curr_Dir, Read_Directory->d_name);
                    }
                    Find(Full_Curr_Dir, Final_Dest, flag_d, flag_f);
                }
            }
        }
        closedir(Directory);
    }
    return;
}

void Print_Discover(char *Curr_Dir, bool flag_d, bool flag_f)
{
    DIR *Directory;
    struct dirent *Read_Directory;

    char *Exact_Curr_Dir = (char *)malloc(sizeof(char) * 1000);
    strcpy(Exact_Curr_Dir, Curr_Dir);

    Directory = opendir(Curr_Dir);

    char Full_Curr_Dir[1000];

    if (Directory != NULL)
    {
        while ((Read_Directory = readdir(Directory)) != NULL)
        {
            if (Read_Directory->d_name[0] == '.')
            {
                continue;
            }
            // If it is a File
            if (Read_Directory->d_type == DT_REG)
            {
                Full_Curr_Dir[0] = '\0';
                strcat(Full_Curr_Dir, Curr_Dir);
                strcat(Full_Curr_Dir, "/");
                strcat(Full_Curr_Dir, Read_Directory->d_name);

                if (flag_f == true)
                {
                    Color_Coding(Full_Curr_Dir);
                }
            }
        }
        closedir(Directory);
        Directory = opendir(Curr_Dir);
        while ((Read_Directory = readdir(Directory)) != NULL)
        {
            if (Read_Directory->d_name[0] == '.')
            {
                continue;
            }
            if (Read_Directory->d_type == DT_DIR)
            {
                Full_Curr_Dir[0] = '\0';
                strcat(Full_Curr_Dir, Curr_Dir);
                strcat(Full_Curr_Dir, "/");
                strcat(Full_Curr_Dir, Read_Directory->d_name);

                if (flag_d == true)
                {
                    Color_Coding(Full_Curr_Dir);
                }

                // Traversing it's Subdirectories.
                strcpy(Full_Curr_Dir, Curr_Dir);
                if (Full_Curr_Dir[strlen(Full_Curr_Dir) - 1] == '/')
                {
                    strcat(Full_Curr_Dir, Read_Directory->d_name);
                }
                else
                {
                    strcat(Full_Curr_Dir, "/");
                    strcat(Full_Curr_Dir, Read_Directory->d_name);
                }
                Print_Discover(Full_Curr_Dir, flag_d, flag_f);
            }
        }
    }
    closedir(Directory);
    return;
}

void Discover(char *Command, char *Curr_Dir)
{
    bool flag_d = false;
    bool flag_f = false;

    int n = strlen(Command);

    char *Command_Without_Flags = (char *)malloc(sizeof(char) * 1000);
    char *File_Name = (char *)malloc(sizeof(char) * 1000);

    int z = 0;
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        if (Command[i] == '-')
        {
            if (Command[i + 1] == 'd' && i < (n - 1))
            {
                flag_d = true;
                i++;
            }
            else if (Command[i + 1] == 'f' && i < (n - 1))
            {
                flag_f = true;
                i++;
            }
            else
            {
                printf("\033[0;31m");
                printf("Invalid Flag\n");
                return;
            }
        }
        else if (Command[i] == '"')
        {
            i++;
            while (Command[i] != '"')
            {
                File_Name[x] = Command[i];
                x++;
                i++;
            }
        }
        else
        {
            Command_Without_Flags[z] = Command[i];
            z++;
        }
    }

    if (flag_d == false && flag_f == false)
    {
        flag_d = true;
        flag_f = true;
    }

    char *token = (char *)malloc(sizeof(char) * 1000);
    char *token_temp = (char *)malloc(sizeof(char) * 1000);

    strcpy(token_temp, token);

    token = strtok(Command_Without_Flags, " \t\n");

    if (token != NULL)
    {
        token = strtok(NULL, " \t\n");
    }

    int count = 0;

    token_temp = strtok(NULL, " \t\n");

    if (token_temp != NULL)
    {
        RED
            printf("discover: Invalid Command\n");
        return;
    }

    char *temp = (char *)malloc(sizeof(char) * 1000);

    if (token != NULL)
    {
        if (strcmp(token, "~/") == 0)
        {
            strcpy(token, "~");
        }
        if (token[0] == '~')
        {
            char *token2 = (char *)malloc(sizeof(char) * 1000);

            strcpy(token2, Home_Dir);

            int z = strlen(token);
            int p = strlen(Home_Dir);

            for (int i = 1; i < z; i++)
            {
                token2[p] = token[i];
                p++;
            }

            strcpy(token, token2);
        }
    }

    if (strcmp(File_Name, "") == 0)
    {
        if (token == NULL)
        {
            if (flag_d == true)
            {
                printf("%s\n", ".");
            }
            Print_Discover(".", flag_d, flag_f);
        }
        else
        {
            if (token[0] != '/' && token[0] != '.')
            {
                strcpy(temp, getcwd(NULL, 0));
                strcat(temp, "/");
                strcat(temp, token);
                strcpy(token, temp);
            }
            if (chdir(token) == -1)
            {
                printf("\033[0;31m");
                printf("discover: %s: No such file or directory\n", HandleDirectory(token));
            }
            else
            {
                if (flag_d == true)
                {
                    Color_Coding(HandleDirectory(token));
                }
                chdir(Curr_Dir);
                Print_Discover(token, flag_d, flag_f);
            }
        }
        return;
    }
    else
    {
        if (token == NULL)
        {
            Find(".", File_Name, flag_d, flag_f);
        }
        else
        {
            if (chdir(token) == -1)
            {
                printf("\033[0;31m");
                printf("discover: %s: No such file or directory\n", HandleDirectory(token));
            }
            else
            {
                chdir(Curr_Dir);
                Find(token, File_Name, flag_d, flag_f);
            }
        }
    }
    return;
}