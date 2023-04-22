#include "ls.h"

extern int and;

extern char *Home_Dir;

extern char **Exit_Command;
extern int exit_command;

extern int output_redirection;
extern int output_append;

void Color_Coding_without_Directory(char *File_Name)
{
    struct stat sfile;

    if (stat(File_Name, &sfile) != -1)
    {
        if ((sfile.st_mode & S_IFDIR) != 0)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                CYAN
            }
            printf("%s", File_Name);
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
            return;
        }
        else if (((sfile.st_mode & S_IXOTH) == 1) || ((sfile.st_mode & S_IXUSR) == 1) || ((sfile.st_mode & S_IXGRP) == 1))
        {
            if (output_append == 0 && output_redirection == 0)
            {
                GREEN
            }
            printf("%s", File_Name);
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
            return;
        }
    }
    if (output_append == 0 && output_redirection == 0)
    {
        printf("\033[00;37m");
    }
    printf("%s", File_Name);
    if (output_append == 0 && output_redirection == 0)
    {
        RESET
    }
    printf("\n");
    return;
}

void Color_Coding(char *File_Name)
{
    struct stat sfile;

    if (stat(File_Name, &sfile) != -1)
    {
        if ((sfile.st_mode & S_IFDIR) != 0)
        {
            if (output_append == 0 && output_redirection == 0)
            {
                CYAN
            }
            printf("%s", HandleDirectory(File_Name));
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
            return;
        }
        else if (((sfile.st_mode & S_IXOTH) == 1) || ((sfile.st_mode & S_IXUSR) == 1) || ((sfile.st_mode & S_IXGRP) == 1))
        {
            if (output_append == 0 && output_redirection == 0)
            {
                GREEN
            }
            printf("%s", HandleDirectory(File_Name));
            if (output_append == 0 && output_redirection == 0)
            {
                RESET
            }
            printf("\n");
            return;
        }
    }
    if (output_append == 0 && output_redirection == 0)
    {
        printf("\033[00;37m");
    }
    printf("%s", File_Name);
    if (output_append == 0 && output_redirection == 0)
    {
        RESET
    }
    printf("\n");
    return;
}

void LS_L(bool flag_a, char *Curr_Dir)
{
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

    char *temp = (char *)malloc(sizeof(char) * 1000);

    // Sort Files using the Bubble Sort algorithm
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(Files[j], Files[j + 1]) > 0)
            {
                strcpy(temp, Files[j]);
                strcpy(Files[j], Files[j + 1]);
                strcpy(Files[j + 1], temp);
            }
        }
    }

    struct stat thestat;

    struct passwd *tf;
    struct group *gf;

    int max = 0;
    int max1 = 0;
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        stat(Files[i], &thestat);
        tf = getpwuid(thestat.st_uid);
        gf = getgrgid(thestat.st_gid);
        if (flag_a == true)
        {
            total += thestat.st_blocks;
        }
        else if (flag_a == false)
        {
            if (Files[i][0] == '.')
            {
                total += 0;
            }
            else
            {
                total += thestat.st_blocks;
            }
        }
        if (strlen(tf->pw_name) > max)
        {
            max = strlen(tf->pw_name);
        }
        if (strlen(gf->gr_name) > max1)
        {
            max1 = strlen(gf->gr_name);
        }
    }

    if (output_append == 0 && output_redirection == 0)
    {
        printf("\033[00;37m");
    }
    printf("total %d", total/2);
    if (output_append == 0 && output_redirection == 0)
    {
        RESET
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        if (output_append == 0 && output_redirection == 0)
        {
            printf("\033[00;37m");
        }
        if (flag_a == false)
        {
            if (Files[i][0] == '.')
            {
                continue;
            }
        }

        stat(Files[i], &thestat);

        switch (thestat.st_mode & S_IFMT)
        {
        case S_IFDIR:
            printf("d");
            break;
        default:
            printf("-");
            break;
        }

        printf((thestat.st_mode & S_IRUSR) ? "r" : " -");
        printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
        printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
        printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
        printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
        printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
        printf((thestat.st_mode & S_IROTH) ? "r" : "-");
        printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
        printf((thestat.st_mode & S_IXOTH) ? "x" : "-");

        printf("%*d ", 3, thestat.st_nlink);

        tf = getpwuid(thestat.st_uid);

        printf("%*s", max, tf->pw_name);

        gf = getgrgid(thestat.st_gid);
        printf(" %*s", max1, gf->gr_name);

        printf(" %*lld ", 6, thestat.st_size);

        int x = 0;
        char *timeStruct = ctime(&thestat.st_mtime);

        for (int i = 4; i < strlen(timeStruct); i++)
        {
            if (timeStruct[i] == ':')
            {
                x++;
            }
            if (x == 2)
            {
                break;
            }
            printf("%c", timeStruct[i]);
        }
        printf(" ");

        Color_Coding(Files[i]);
    }
}

void Only_LS(char *Curr_Dir)
{
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

    char *temp = (char *)malloc(sizeof(char) * 1000);

    // Sort Files using the Bubble Sort algorithm
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(Files[j], Files[j + 1]) > 0)
            {
                strcpy(temp, Files[j]);
                strcpy(Files[j], Files[j + 1]);
                strcpy(Files[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        Color_Coding(Files[i]);
    }

    for (int i = 0; i < n; i++)
    {
    }

    closedir(mydir);
    return;
}

void Only_LS_a(char *Curr_Dir)
{
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

    char *temp = (char *)malloc(sizeof(char) * 1000);

    // Sort Files using the Bubble Sort algorithm
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(Files[j], Files[j + 1]) > 0)
            {
                strcpy(temp, Files[j]);
                strcpy(Files[j], Files[j + 1]);
                strcpy(Files[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        Color_Coding(Files[i]);
    }

    for (int i = 0; i < n; i++)
    {
    }

    closedir(mydir);

    return;
}

void LS(char *Command, char *Curr_Dir)
{
    char *token2 = (char *)malloc(sizeof(char) * 1000);
    char *token = (char *)malloc(sizeof(char) * 1000);

    char *Command_Temp = (char *)malloc(sizeof(char) * 1000);
    strcpy(Command_Temp, Command);

    Command_Temp = strtok(Command_Temp, " \t\n");
    Command_Temp = strtok(NULL, "\t\n");

    token = strtok(Command, " \t\n");
    token = strtok(NULL, " \t\n");

    bool flag_a = false;
    bool flag_l = false;

    // For Plain LS
    if (token == NULL)
    {
        Only_LS(Curr_Dir);
        return;
    }

    // Computation for Multiple Flags
    int z = 0;
    for (int i = 0; i < strlen(Command_Temp); i++)
    {
        if (Command_Temp[i] == '-')
        {
            if (Command_Temp[i + 1] == 'a')
            {
                i++;
                flag_a = true;
            }
            if (Command_Temp[i + 1] == 'l')
            {
                i++;
                flag_l = true;
                if (Command_Temp[i + 1] == 'a')
                {
                    i++;
                    flag_a = true;
                }
            }
        }
        else
        {
            token2[z] = Command_Temp[i];
            z++;
        }
    }

    char *temp2 = strtok(token2, " \t\n");
    Curr_Dir[strlen(Curr_Dir)] = '\0';

    // Implementing LS for -a and -l flags Seperately
    if (temp2 == NULL)
    {
        if (flag_l == true)
        {
            LS_L(flag_a, Curr_Dir);
            return;
        }
        else if (flag_a == true)
        {
            Only_LS_a(Curr_Dir);
        }
        return;
    }

    int count = 0;
    char *count_it = (char *)malloc(sizeof(char) * 1000);
    strcpy(count_it, token2);

    char **Files = (char **)malloc(sizeof(char) * 1000);

    while (count_it != NULL)
    {
        Files[count] = (char *)malloc(sizeof(char) * 1000);
        Files[count] = count_it;
        count_it = strtok(NULL, " \t\n");
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        Files[i] = strtok(Files[i], " ");
    }

    // Implementing LS For All Other Cases
    int i = 0;
    int flag = 0;
    for (int i = 0; i < count; i++)
    {
        if (Files[i][0] == '~')
        {
            char *temp = (char *)malloc(sizeof(char) * 1000);
            strcpy(temp, Home_Dir);
            strcat(temp, "/");
            if (temp[strlen(temp) - 1] != '/')
            {
                strcat(temp, &Files[i][1]);
            }
            else
            {
                strcat(temp, &Files[i][2]);
            }
            strcpy(Files[i], temp);
            flag = 1;
        }
        if (count > 1)
        {
            printf("\033[00;37m");
            printf("%s:\n", Files[i]);
        }

        if (strcmp(Files[i], "..") == 0)
        {
            if (flag_l == true)
            {
                chdir("..");

                char *Curr_Dir_Temp = (char *)malloc(sizeof(char) * 1000);
                Curr_Dir_Temp = getcwd(Curr_Dir_Temp, 1000);

                LS_L(flag_a, Curr_Dir_Temp);

                chdir(Curr_Dir);
            }
            else if (flag_a == true)
            {
                chdir("..");

                char *Curr_Dir_Temp = (char *)malloc(sizeof(char) * 1000);
                Curr_Dir_Temp = getcwd(Curr_Dir_Temp, 1000);
                Curr_Dir_Temp[strlen(Curr_Dir_Temp)] = '\0';

                Only_LS_a(Curr_Dir_Temp);

                chdir(Curr_Dir);
            }
            else
            {
                chdir("..");

                char *Curr_Dir_Temp = (char *)malloc(sizeof(char) * 1000);
                Curr_Dir_Temp = getcwd(Curr_Dir_Temp, 1000);
                Curr_Dir_Temp[strlen(Curr_Dir_Temp)] = '\0';

                Only_LS(Curr_Dir_Temp);

                chdir(Curr_Dir);
            }
            if (count > 1)
            {
                printf("\n");
            }
        }
        else if (strcmp(Files[i], ".") == 0)
        {
            Curr_Dir[strlen(Curr_Dir)] = '\0';
            if (flag_l == true)
            {
                LS_L(flag_a, Curr_Dir);
            }
            else if (flag_a == true)
            {
                Only_LS_a(Curr_Dir);
            }
            else
            {
                Only_LS(Curr_Dir);
            }
            if (count > 1)
            {
                printf("\n");
            }
        }
        else if (strcmp(Files[i], "~") == 0)
        {
            chdir(Home_Dir);
            Home_Dir[strlen(Home_Dir)] = '\0';
            if (flag_l == true)
            {
                LS_L(flag_a, Home_Dir);
            }
            else if (flag_a == true)
            {
                Only_LS_a(Home_Dir);
            }
            else
            {
                Only_LS(Home_Dir);
            }
            chdir(Curr_Dir);
            if (count > 1)
            {
                printf("\n");
            }
        }
        else
        {
            char *Curr_Temp_Dir = (char *)malloc(sizeof(char) * 1000);

            struct stat sfile;

            char *temp = (char *)malloc(sizeof(char) * 1000);

            if (Files[i][0] != '/')
            {
                strcpy(temp, getcwd(NULL, 0));
                strcat(temp, "/");
                strcat(temp, Files[i]);
                strcpy(Files[i], temp);
            }

            if (stat(Files[i], &sfile) != -1)
            {
                if ((sfile.st_mode & S_IFDIR) != 0)
                {
                    chdir(Files[i]);

                    Curr_Temp_Dir = getcwd(Curr_Temp_Dir, 1000);
                    Curr_Temp_Dir[strlen(Curr_Temp_Dir)] = '\0';

                    if (flag_l == true)
                    {
                        LS_L(flag_a, Curr_Temp_Dir);
                    }
                    else if (flag_a == true)
                    {
                        Only_LS_a(Curr_Temp_Dir);
                    }
                    else
                    {
                        Only_LS(Curr_Temp_Dir);
                    }
                    chdir(Curr_Dir);
                }
                else
                {
                    if (flag_l == false)
                    {
                        Color_Coding(Files[i]);
                    }
                    else if (flag_l == true)
                    {
                        strcpy(Curr_Temp_Dir, Curr_Dir);
                        strcat(Curr_Temp_Dir, "/");
                        strcat(Curr_Temp_Dir, Files[i]);

                        struct stat thestat;

                        struct passwd *tf;
                        struct group *gf;

                        int max = 0;
                        int max1 = 0;

                        stat(Curr_Temp_Dir, &thestat);
                        tf = getpwuid(thestat.st_uid);
                        gf = getgrgid(thestat.st_gid);

                        max = strlen(tf->pw_name);

                        max1 = strlen(gf->gr_name);

                        printf("\033[00;37m");

                        switch (thestat.st_mode & S_IFMT)
                        {
                        case S_IFDIR:
                            printf("d");
                            break;
                        default:
                            printf("-");
                            break;
                        }

                        printf((thestat.st_mode & S_IRUSR) ? "r" : " -");
                        printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
                        printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
                        printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
                        printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
                        printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
                        printf((thestat.st_mode & S_IROTH) ? "r" : "-");
                        printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
                        printf((thestat.st_mode & S_IXOTH) ? "x" : "-");

                        printf("%*d ", 3, thestat.st_nlink);

                        tf = getpwuid(thestat.st_uid);

                        printf("%*s", max, tf->pw_name);

                        gf = getgrgid(thestat.st_gid);
                        printf(" %*s", max1, gf->gr_name);

                        printf(" %*lld ", 6, thestat.st_size);

                        int x = 0;
                        char *timeStruct = ctime(&thestat.st_mtime);

                        for (int i = 4; i < strlen(timeStruct); i++)
                        {
                            if (timeStruct[i] == ':')
                            {
                                x++;
                            }
                            if (x == 2)
                            {
                                break;
                            }
                            printf("%c", timeStruct[i]);
                        }
                        printf(" ");

                        Color_Coding(Files[i]);
                    }
                }
                if (count > 1)
                {
                    printf("\n");
                }
                if (count > 1)
                {
                    printf("\n");
                }
            }
            else
            {
                printf("\033[00;31m");
                printf("ls: %s: No such file or directory\n", HandleDirectory(Files[i]));
                printf("\033[00;37m");
            }
        }
    }
    return;
}