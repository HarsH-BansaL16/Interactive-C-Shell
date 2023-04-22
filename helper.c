#include "helper.h"

extern int and;

extern char *Home_Dir;

extern int time_spent;

extern int Ctrl_C;

extern char **Exit_Command;
extern int exit_command;

extern int output_redirection;
extern int output_append;
extern int input_redirection;
int fd_ptr;

extern char *Prev_Dir;
extern char *System_Root;

extern int flag;

extern Background Processes[50];

void trimwhitespace(char *str)
{
    int count = 0;
    int j = 0;
    int flag = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == ' ' || str[i] == '\t')
        {
            continue;
        }
        else
        {
            flag = 1;
            j = i;
            break;
        }
    }

    if (flag == 1)
    {
        for (int i = j; str[i]; i++)
        {
            str[count++] = str[i];
        }
        str[count] = '\0';
    }
    else
    {
        strcpy(str, "\0");
    }

    return;
}

char *HandleDirectory(char *Curr_Dir)
{
    int n = strlen(Curr_Dir);
    int m = strlen(Home_Dir);
    int flag = 0, j = 0;

    for (int i = 0; i < n; i++)
    {
        if (Curr_Dir[i] == Home_Dir[i])
        {
            j = i;
            flag++;
        }
    }

    if (flag == n && m == n)
    {
        Curr_Dir = "~";
    }
    else if (flag == m & flag < n)
    {
        char *Return_Dir = (char *)malloc(sizeof(char) * 1000);
        Return_Dir[0] = '~';
        int z = 1;
        j++;
        for (int i = j; i < n; i++)
        {
            Return_Dir[z] = Curr_Dir[i];
            z++;
        }
        return Return_Dir;
    }

    return Curr_Dir;
}

char *Extract_Command(char *Command)
{
    char *s = (char *)malloc(sizeof(char) * 1000);
    strcpy(s, Command);
    char *token = (char *)malloc(sizeof(char) * 1000);
    token = strtok(s, " \t\n");
    return token;
}

void HandleCommand(char *Final_Command, char *Command)
{
    int bg = 0;
    char *Command_Duplicate = (char *)malloc(sizeof(char) * 1000);
    strcpy(Command_Duplicate, Command);

    char **argv = (char **)malloc(sizeof(char *) * 10);
    char *token = (char *)malloc(sizeof(char) * 1000);

    // Getting the Current Working Directory
    char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
    Curr_Dir = getcwd(Curr_Dir, 1000);

    int pipe = 0;
    for (int i = 0; i < strlen(Command); i++)
    {
        if (Command[i] == '|')
        {
            pipe++;
        }
    }
    if (pipe > 0)
    {
        pipe_handler(Command);
        return;
    }

    if (and == 0)
    {
        Command = HandleRedirection(Command_Duplicate);

        if (strcmp(Command, "false") == 0)
        {
            return;
        }
        Final_Command = (Extract_Command(Command));
    }

    // Handling Foreground and Background
    if (and > 0)
    {
        int n = 0;
        char *token = (char *)malloc(sizeof(char) * 1000);
        strcpy(token, Command);

        char **Array = (char **)malloc(sizeof(char *) * 20);
        for (int k = 0; k < 20; k++)
        {
            Array[k] = (char *)malloc(sizeof(char) * 1000);
            strcpy(Array[k], "");
        }

        int x = 0;
        int l = 0;

        for (int i = 0; i < strlen(Command); i++)
        {
            if (Command[i] == '&')
            {
                Array[x][l] = '\0';
                Array[x] = strtok(Array[x], "\n");
                if (Array[x] != NULL)
                {
                    trimwhitespace(Array[x]);
                    if (Array[x] == NULL || strcmp(Array[x], "") == 0)
                    {
                        printf("\033[0;41m");
                        printf("bash: syntax error near unexpected token '&'");
                        RESET
                        printf("\n");
                        return;
                    }
                }
                l = 0;
                x++;
                Array[x][l] = '\0';
            }
            else
            {
                Array[x][l] = Command[i];
                l++;
            }
        }

        Array[x] = strtok(Array[x], "\n");
        if (Array[x] != NULL)
        {
            trimwhitespace(Array[x]);
        }

        // Segregating as ForeGround and BackGround.
        for (int i = 0; i <= x; i++)
        {
            if ((Array[x] == NULL || strcmp(Array[x], "") == 0) && i == x)
            {
                continue;
            }
            else
            {
                if (i == x)
                {
                    char *token = (char *)malloc(sizeof(char) * 1000);

                    output_append = 0;
                    input_redirection = 0;
                    output_redirection = 0;

                    for (l = 0; l < strlen(Array[i]); l++)
                    {
                        if (Array[i][l] == '>')
                        {
                            output_redirection = 1;
                            if (Array[i][l] == '>')
                            {
                                output_append = 1;
                            }
                        }
                        else if (Array[i][l] == '<')
                        {
                            input_redirection = 1;
                        }
                    }

                    if (output_append == 1 || output_redirection == 1 || input_redirection == 1)
                    {
                        Command = HandleRedirection(Array[i]);
                        Final_Command = Extract_Command(Command);
                    }
                    else
                    {
                        strcpy(Command, Array[i]);

                        token = strtok(Array[i], " ");

                        strcpy(Final_Command, token);
                    }

                    goto x;
                }
                else if (Array[i] != NULL)
                {
                    char *token = (char *)malloc(sizeof(char) * 1000);

                    output_append = 0;
                    input_redirection = 0;
                    output_redirection = 0;

                    for (l = 0; l < strlen(Array[i]); l++)
                    {
                        if (Array[i][l] == '>')
                        {
                            output_redirection = 1;
                            if (Array[i][l + 1] == '>')
                            {
                                output_append = 1;
                            }
                        }
                        else if (Array[i][l] == '<')
                        {
                            input_redirection = 1;
                        }
                    }

                    if (output_append == 1 || output_redirection == 1 || input_redirection == 1)
                    {
                        Command = HandleRedirection(Array[i]);
                        Final_Command = Extract_Command(Command);
                    }
                    else
                    {
                        strcpy(Command, Array[i]);

                        token = strtok(Array[i], " ");

                        strcpy(Final_Command, token);
                    }

                    bg = 1;

                    goto z;

                y:
                    continue;
                }
            }
        }
    }
    else
    {
    x:
        if (Ctrl_C == 1 && bg == 0)
        {
            return;
        }
        if (strcasecmp(Final_Command, "Quit") == 0 || strcasecmp(Final_Command, "Q") == 0 || strcasecmp(Final_Command, "exit") == 0)
        {
            PrintCompletedProcess();
            printf("\033[0;41m");
            printf("Terminal Successfully Exited!");
            RESET;
            printf("\n");
            Disable_Raw_Mode();
            exit(0);
        }
        else if (strcmp(Final_Command, "echo") == 0)
        {
            Echo(Command);
        }
        else if (strcmp(Final_Command, "pwd") == 0)
        {
            Pwd();
        }
        else if (strcmp(Final_Command, "cd") == 0)
        {
            cd(Command, &flag, &Prev_Dir);
        }
        else if (strcmp(Final_Command, "ls") == 0)
        {
            LS(Command, Curr_Dir);
        }
        else if (strcmp(Final_Command, "mkdir") == 0)
        {
            my_mkdir(Command, Curr_Dir);
        }
        else if (strcmp(Final_Command, "discover") == 0)
        {
            Discover(Command, Curr_Dir);
        }
        else if (strcmp(Final_Command, "pinfo") == 0)
        {
            P_Info(Command);
        }
        else if (strcmp(Final_Command, "jobs") == 0)
        {
            jobs(Command);
        }
        else if (strcmp(Final_Command, "sig") == 0)
        {
            sig(Command);
        }
        else if (strcmp(Final_Command, "fg") == 0)
        {
            time_spent = time(NULL);
            fg(Command);
        }
        else if (strcmp(Final_Command, "bg") == 0)
        {
            bg_handle(Command);
        }
        else if (strcmp(Final_Command, "history") == 0)
        {
            char *token = (char *)malloc(sizeof(char) * 1000);
            token = strtok(Command, " \t\n");
            token = strtok(NULL, " \t\n");

            if (token != NULL)
            {
                RED;
                printf("Error: Too Many Arguements to Function Call");
                RESET;
                printf("\n");
                return;
            }

            Print_History(System_Root, Curr_Dir);
        }
        else if (strcmp(Final_Command, "clear") == 0)
        {
            printf("\e[1;1H\e[2J");
        }
        else
        {
        z:
            token = strtok(Command, " \n");

            int i = 0;
            while (token != NULL)
            {
                argv[i] = (char *)malloc(sizeof(char) * 1000);
                strcpy(argv[i], token);
                token = strtok(NULL, " \n");
                i++;
            }
            argv[i] = (char *)malloc(sizeof(char) * 1000);
            argv[i] = NULL;

            if (bg == 1)
            {
                BackGround(argv[0], argv);
                bg = 0;
                Reset_IO_Direction();
                goto y;
            }
            else
            {
                pid_t pid = fork();

                double begin = time(NULL);
                int retval;

                // Child Process
                if (pid == 0)
                {
                    printf("\033[00;37m");
                    retval = execvp(Final_Command, argv);

                    if (retval == -1)
                    {
                        printf("\033[0;31m");
                        if (strcmp(&Final_Command[strlen(Final_Command) - 1], "\n") == 0)
                        {
                            char *temp = (char *)malloc(sizeof(char) * 1000);
                            strncpy(temp, Final_Command, strlen(Final_Command) - 1);

                            printf("bash: %s: command not found", temp);
                            RESET
                            printf("\n");
                            exit(0);
                            return;
                        }
                        printf("bash: %s: command not found", Final_Command);
                        RESET
                        printf("\n");
                        exit(0);
                    }
                }
                else
                {
                    // Updating the Process in the ForeGround Array
                    UpdateForeGroundProcess(pid, Final_Command);

                    int status;
                    waitpid(pid, &status, WUNTRACED | WCONTINUED);

                    double end = time(NULL);
                    time_spent += (end - begin);

                    // Updating the Process when it has Exited
                    RemoveForeGroundProcess(pid);
                }
            }
        }
    }
    if (output_redirection == 1 || output_append == 1 || input_redirection == 1)
    {
        close(fd_ptr);
        Reset_IO_Direction();
    }

    return;
}