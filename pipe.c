#include "pipe.h"

extern int stdout_ptr;
extern int stdin_ptr;

extern int output_redirection;
extern int output_append;
extern int input_redirection;

void pipe_handler(char *Command)
{
    char *token = (char *)malloc(sizeof(char) * 1000);
    strcpy(token, Command);

    char **Files = (char **)malloc(sizeof(char *) * 10);
    for (int i = 0; i < 10; i++)
    {
        Files[i] = (char *)malloc(sizeof(char) * 1000);
    }

    int z = 0;
    int l = 0;
    for (int i = 0; i < strlen(Command); i++)
    {
        if (Command[i] == '|')
        {
            z = 0;
            l++;
        }
        else
        {
            Files[l][z] = Command[i];
            z++;
        }
    }

    for (int i = 0; i < l; i++)
    {
        int p[2];
        if (pipe(p) < 0)
        {
            printf("Error");
        }

        dup2(p[1], 1);

        input_redirection = 0;
        output_redirection = 0;

        for (int k = 0; k < strlen(Files[i]); k++)
        {

            if (Files[i][k] == '>')
            {
                output_redirection = 1;
            }
            else if (Files[i][k] == '<')
            {
                input_redirection = 1;
            }
        }

        HandleCommand(Extract_Command(Files[i]), Files[i]);

        dup2(stdout_ptr, 1);
        close(p[1]);

        dup2(p[0], 0);

        close(p[0]);
    }

    input_redirection = 0;
    output_redirection = 0;

    for (int k = 0; k < strlen(Files[l]); k++)
    {

        if (Files[l][k] == '>')
        {
            output_redirection = 1;
        }
        else if (Files[l][k] == '<')
        {
            input_redirection = 1;
        }
    }

    HandleCommand(Extract_Command(Files[l]), Files[l]);

    Reset_IO_Direction();

    return;
}