#include "rawmode.h"

struct termios orig_termios;

// Function which Kills any Process
void Die(const char *s)
{
    perror(s);
    exit(1);
}

// Disabling the Raw Mode
void Disable_Raw_Mode()
{
    // printf("\n");
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    {
        Die("tcsetattr");
    }
}

// Enabling the Raw Mode
void Enable_Raw_Mode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    {
        Die("tcgetattr");
    }
    atexit(Disable_Raw_Mode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    {
        Die("tcsetattr");
    }
}