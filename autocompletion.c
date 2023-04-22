#include "autocompletion.h"

char *RemoveString(char *str, char *word)
{
    int i, j = 0, k = 0, n = 0;
    int flag = 0;

    char *neww = (char *)malloc(sizeof(char) * 1000);

    for (i = 0; i < strlen(str); i++)
    {
        k = i;

        while (str[i] == word[j])
        {
            i++;
            j++;
            if (j == strlen(word))
            {
                flag = 1;
                break;
            }
        }
        j = 0;

        if (flag == 0)
        {
            i = k;
        }
        else
        {
            flag = 0;
        }

        neww[n++] = str[i];
    }

    neww[n] = '\0';

    return neww;
}

char *Handle_Tab(char *Command)
{
    if (strcmp(Command, "") == 0)
    {
        char *Curr_Dir = ".";

        DIR *mydir;
        struct dirent *myfile;
        mydir = opendir(Curr_Dir);

        char **Files = (char **)malloc(sizeof(char *) * 1000);
        int n = 0;
        while ((myfile = readdir(mydir)) != NULL)
        {
            Files[n] = (char *)malloc(sizeof(char) * 1000);

            strcpy(Files[n], myfile->d_name);

            n++;
        }

        printf("\n");
        for (int i = 0; i < n; i++)
        {
            if (Files[i][0] != '.')
            {
                struct stat sfile;

                if (stat(Files[i], &sfile) != -1)
                {
                    if ((sfile.st_mode & S_IFDIR) != 0)
                    {
                        printf("%s/\n", Files[i]);
                    }
                    else
                    {
                        printf("%s\n", Files[i]);
                    }
                }
            }
        }
        Prompt();
        return Command;
    }

    int index = strlen(Command);
    for (int i = strlen(Command) - 1; i >= 0; i--)
    {
        if (Command[i] == '/')
        {
            index = i;
            break;
        }
    }
    index++;

    char *search = (char *)malloc(sizeof(char) * 1000);
    int z = 0;
    for (int i = index; i < strlen(Command); i++)
    {
        search[z] = Command[i];
        z++;
    }

    int index2 = 0;
    for (int i = strlen(Command); i >= 0; i--)
    {
        if (Command[i] == ' ')
        {
            index2 = i;
            index2++;
            break;
        }
    }

    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
    z = 0;
    for (int i = index2; i < index - 1; i++)
    {
        Curr_Dir[z] = Command[i];
        z++;
    }

    if (index == strlen(Command) + 1)
    {
        strcpy(search, Curr_Dir);
        Curr_Dir = "";
    }

    if (strcmp(Curr_Dir, "") == 0)
    {
        Curr_Dir = ".";
    }

    DIR *mydir;
    struct dirent *myfile;

    mydir = opendir(Curr_Dir);

    char **Files = (char **)malloc(sizeof(char *) * 1000);
    int n = 0;

    while ((myfile = readdir(mydir)) != NULL)
    {
        if (myfile->d_name[0] != '.')
        {
            Files[n] = (char *)malloc(sizeof(char) * 1000);
            strcpy(Files[n], myfile->d_name);
            n++;
        }
    }

    char **Matches = (char **)malloc(sizeof(char *) * 1000);
    z = 0;

    int count_match = 0;

    for (int i = 0; i < n; i++)
    {
        if (strncmp(Files[i], search, strlen(search)) == 0)
        {
            Matches[z] = (char *)malloc(sizeof(char) * 1000);
            strcpy(Matches[z], Files[i]);
            z++;
            count_match++;
        }
    }

    if (count_match == 0)
    {
        printf("\r");
        Prompt();
        printf("%s", Command);
        return Command;
    }
    else if (count_match == 1)
    {
        printf("\r");
        Prompt();
        char *New_String = (char *)malloc(sizeof(char) * 1000);
        New_String = RemoveString(Command, search);
        strcat(New_String, Matches[0]);
        struct stat sfile;
        if (stat(Matches[0], &sfile) != -1)
        {
            if ((sfile.st_mode & S_IFDIR) != 0)
            {
                strcat(New_String, "/ ");
                printf("%s", New_String);
            }
            else
            {
                strcat(New_String, " ");
                printf("%s", New_String);
            }
        }
        return New_String;
    }
    else
    {
        int count = z;
        int b = 0;

        char *temp = (char *)malloc(sizeof(char) * 1000);
        strcpy(temp, search);

        char *final = (char *)malloc(sizeof(char) * 1000);
        while (count == z)
        {
            temp[strlen(temp)] = Matches[0][strlen(search) + b];

            count = 0;

            for (int i = 0; i < z; i++)
            {
                if (strncmp(Matches[i], temp, strlen(temp)) == 0)
                {
                    count++;
                }
            }
            if (count == z)
            {
                strcpy(final, temp);
                b++;
            }
            else
            {
                break;
            }
        }

        printf("\n");
        for (int i = 0; i < z; i++)
        {
            if (strncmp(Matches[i], final, strlen(final)) == 0)
            {
                struct stat sfile;

                if (stat(Matches[i], &sfile) != -1)
                {
                    if ((sfile.st_mode & S_IFDIR) != 0)
                    {
                        printf("%s/ \n", Matches[i]);
                    }
                    else
                    {
                        printf("%s \n", Matches[i]);
                    }
                }
            }
        }

        Prompt();

        char *New_String = (char *)malloc(sizeof(char) * 1000);
        New_String = RemoveString(Command, search);

        if(strcmp(final,"") == 0)
        {
            strcpy(final,search);
        }

        strcat(New_String, final);

        printf("%s", New_String);

        return New_String;
    }

    return Command;
}