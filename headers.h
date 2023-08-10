#ifndef __HEADERS_H__
#define __HEADERS_H__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <grp.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "helper.h"
#include "ls.h"
#include "history.h"
#include "mkdir.h"
#include "discover.h"
#include "pinfo.h"
#include "process.h"
#include "init.h"
#include "prompt.h"
#include "rawmode.h"
#include "redirection.h"
#include "jobs.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "foreground.h"
#include "pipe.h"
#include "autocompletion.h"

// Colors
#define RED printf("\x1b[31m");
#define RED_BACK printf("\x1b[41m");
#define GREEN printf("\x1b[32m");
#define YELLOW printf("\x1b[33m");
#define BLUE printf("\x1b[34m");
#define MAGENTA printf("\x1b[35m");
#define CYAN printf("\x1b[36m");
#define RESET printf("\x1b[0m");
#define PWD_COLOR printf("\x1b[44m");

struct Info
{
    pid_t pid;
    int Serial;
    char *Command;
    int Status; // For Changing the Indexing Method
    int Flag;   // For Jobs
};
typedef struct Info Background;

#endif