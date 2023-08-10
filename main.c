#include "headers.h"

int and = 0;
int time_spent = 0;
int fore = 0;
int stdout_ptr;
int stdin_ptr;

int Ctrl_C = 0;

int output_redirection = 0;
int input_redirection = 0;
int output_append = 0;

Background Processes[50];
Background ForeGround[50];

char **Exit_Command;

char *Prev_Dir;

int exit_command;

char *Home_Dir;

char *System_Root;

int flag = -1;

int main()
{
    int Control_C_char = 0;

    char *Prev_Command = (char *)malloc(sizeof(char) * 1000);
    char *Prev_Dir = (char *)malloc(sizeof(char *) * 1000);

    // Extracting the Current Working Directory
    Home_Dir = getcwd(Home_Dir, 1000);

    // History
    struct passwd *pw = getpwuid(getuid());
    System_Root = pw->pw_dir;

    Init(System_Root);
    setbuf(stdout, NULL);

    while (1)
    {
        Enable_Raw_Mode();

        // Signal Handling
        signal(SIGCHLD, Handler);

        // Signal Handling for Control-C
        signal(SIGINT, Control_C);

        // Signal Handling for Control-Z
        signal(SIGTSTP, Control_Z);

        // Signal Handling for Printing the Exit Status
        Check_Exit_Status();

        // Getting the Current Working Directory
        char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
        Curr_Dir = getcwd(Curr_Dir, 1000);

        char *Curr_Dir_Copy = (char *)malloc(sizeof(char) * 1000);
        strcpy(Curr_Dir_Copy, Curr_Dir);

        // Taking Command_Temp of the Command
        char *Command_Temp = (char *)malloc(sizeof(char) * 1000);
        char *Command = (char *)malloc(sizeof(char) * 1000);

        prompt(Home_Dir);

        char c = 0;
        int pt = 0;
        while (read(0, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                {
                    printf("\n");
                    break;
                }
                else if (c == 127)
                {
                    // Backspace
                    if (pt > 0)
                    {
                        if (Command_Temp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        Command_Temp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                {
                    // TAB character
                    Command_Temp = Handle_Tab(Command_Temp);
                    pt = strlen(Command_Temp);
                    // Command_Temp[pt++] = c;
                }
                else if (c == 4)
                {
                    // Handling Control-D
                    printf("\n");
                    RED;
                    printf("Exiting the Program!");
                    RESET;
                    printf("\n");
                    Disable_Raw_Mode();
                    exit(0);
                }
                else
                {
                    printf("%d", c);
                }
            }
            else if (c)
            {
                Command_Temp[pt++] = c;
                printf("%c", c);
            }
        }

        Command_Temp[strlen(Command_Temp)] = '\n';
        Command_Temp[strlen(Command_Temp)] = '\0';

        Store_History(Command_Temp, Prev_Command, System_Root, Curr_Dir_Copy);
        strcpy(Prev_Command, Command_Temp);

        // Handling the New Line Character
        int count_space = 0;
        int semicolon = 0;

        int i = 0;
        for (i = 0; i < strlen(Command_Temp); i++)
        {
            if (Command_Temp[i] == 10 && count_space == i)
            {
                break;
            }
            else if (Command_Temp[i] == '>' && semicolon == 0)
            {
                output_redirection = 1;
            }
            else if (Command_Temp[i] == '<' && semicolon == 0)
            {
                input_redirection = 1;
            }
            else if (Command_Temp[i] == 32 || Command_Temp[i] == '\t')
            {
                count_space++;
            }
            else if (Command_Temp[i] == ';')
            {
                semicolon++;
            }
            else if (Command_Temp[i] == '&')
            {
                and++;
            }
        }
        if (count_space == i || Command_Temp[0] == 10)
        {
            PrintCompletedProcess();
            continue;
        }

        // Redirecting the Work Flow to a Function to Handle Command.
        if (semicolon > 0)
        {
            int n = 0;
            input_redirection = 0;
            output_redirection = 0;

            semicolon++;
            while (semicolon > 0)
            {
                semicolon--;
                char *token = (char *)malloc(sizeof(char) * 1000);
                char *Temp = (char *)malloc(sizeof(char) * 1000);
                strcpy(Temp, Command_Temp);
                token = strtok(Temp, ";");
                n = strlen(token);

                // printf("-%s-",token);

                if (Command_Temp[0] == ';')
                {
                    printf("bash: syntax error near unexpected token `;'\n");
                    break;
                }

                if (strcmp(token, "\n") == 0)
                {
                    printf("bash: syntax error near unexpected token `;'\n");
                    break;
                }

                Command = Extract_Command(token);

                if ((Command == NULL || strcmp(Command, "\n") == 0))
                {
                    printf("bash: syntax error near unexpected token `;'\n");
                    break;
                }

                for (int i = 0; i < strlen(token); i++)
                {
                    if (token[i] == '>')
                    {
                        output_redirection = 1;
                    }
                    else if (token[i] == '<')
                    {
                        input_redirection = 1;
                    }
                }

                HandleCommand(Command, token);

                Command_Temp = &Command_Temp[n + 1];
            }
        }
        else
        {
            Command = Extract_Command(Command_Temp);
            HandleCommand(Command, Command_Temp);
        }
        Disable_Raw_Mode();
    }
}
