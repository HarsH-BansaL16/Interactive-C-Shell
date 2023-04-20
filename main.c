#include "headers.h"

int and = 0;
int time_spent = 0;

Background Processes[50];

char **Exit_Command;
int exit_command;

char *Home_Dir;

int main()
{
    char *Prev_Command = (char *)malloc(sizeof(char) * 1000);
    char *Prev_Dir = (char *)malloc(sizeof(char *) * 1000);

    int flag = -1;

    // Extracting the Current Working Directory
    Home_Dir = getcwd(Home_Dir, 1000);

    // History
    struct passwd *pw = getpwuid(getuid());
    char *System_Root = pw->pw_dir;

    Init(System_Root);

    while (1)
    {
        // Signal Handling
        signal(SIGCHLD, Handler);

        // Printing the Exit Status
        Check_Exit_Status();

        // Getting the Current Working Directory
        char *Curr_Dir = (char *)malloc(sizeof(char) * 1000);
        Curr_Dir = getcwd(Curr_Dir, 1000);

        char *Curr_Dir_Copy = (char *)malloc(sizeof(char) * 1000);
        strcpy(Curr_Dir_Copy, Curr_Dir);

        // Taking Input of the Command
        char *Command_Temp = (char *)malloc(sizeof(char) * 1000);
        char *Command = (char *)malloc(sizeof(char) * 1000);

        Prompt(Home_Dir);

        fgets(Command_Temp, 1000, stdin);

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
        if (Command_Temp[strlen(Command_Temp) - 1] == '\n')
        {
            for (int i = 0; i < exit_command; i++)
            {
                YELLOW
                printf("%s", Exit_Command[i]);
                RESET
            }
            exit_command = 0;
        }

        // Redirecting the Work Flow to a Function to Handle Command.
        if (semicolon > 0)
        {
            int n = 0;

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

                HandleCommand(Command, token, &Prev_Dir, &flag, System_Root);

                Command_Temp = &Command_Temp[n + 1];
            }
        }
        else
        {
            Command = Extract_Command(Command_Temp);
            HandleCommand(Command, Command_Temp, &Prev_Dir, &flag, System_Root);
        }
    }
}
