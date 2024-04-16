# C-Shell
Making a shell in C programming language

```
Name    : Harsh Bansal
```

---

## Running shell

1. Run the makefile via `$ make`
2. Start executing shell as `$ ./a.out`
3. Enter commands separted by ; or & just as you would in a unix terminal
    * `$ command1 arguments & command2 arguments`
    * `$ command1 arguments; command2     arguments   ; command3  arguments ...`
    * A command ending with a `;` will be executed in the foreground while a command ending in `&` will executed in background. If no such character is present at the end, then the command is run in foreground.
    * If a foreground process takes more than 1s, then that is indicated in the terminal's prompt. If a series of `;` separated processes are executed, then considers time taken by the most recently executed process.
    * I/O redirection works as follows - 
        1. `cmd` > file : redirects stdout into the file (writes file)
        2. `cmd` < file : reads from file, i.e, takes stdin from file
        3. `cmd` >> file : Appends data to file
        
        (Works on assumption that user will give spaces around <, >, and >>)
    * Piping works as follows - 
    
        `cmd1` | `cmd2` : redirects output of cmd1 into input of cmd2
    * Signals -
        1. `^C` : Terminates running foreground process, if any.
        2. `^D` : Logs out of shell
        3. `^Z` : Pushes running foreground process to background.
    * Autocompletion - 
        
        Whenever `tab` key is pressed it either - 
        1. Displays all the possible files folders starting with the given starting characters (all files and folders if preceeded by a space or nothing) under the prompt.
        2. If there is only one possible file or folder, it is autocompleted in the terminal. 
4. To remove all .o files, main file and history file (hidden) run `$ make clean`

---

## Commands

1. **`echo`**
    * _Output_ : Prints the entered arguments by excluding extra spaces and tabspaces.
    * _Syntax_ : 
    
        `$ echo <arguments>`

    * _Example_ : 

        `$ echo hello     there!`

        `>>> hello there!`
    
2. **`cd`**
    * _Output_ : Changes current directory to given directory
    * _Syntax_ :

        `$ cd` : changes to home directory

        `$ cd ~` : changes to home directory

        `$ cd file_path` : changes to path based on characters such as `.` (current directory) and `..` (parent directory)

        `$ cd -`

    * _Example_ : 

        `$ cd ~`
    
3. **`pwd`**
    * _Output_ : Prints the present working directory
    * _Syntax_ : 
    
        `$ pwd`

    * _Example_ : 

        `$ pwd` prints /HOME/username/... if the present working directory is a descendant of the directory from which the shell was executed

        `$ pwd` prints /home/username/... otherwise

4. **`exit`**
    * _Output_ : Quits shell
    * _Syntax_ :

        `$ exit`

5. **`ls`**
    * _Output_ : 

        * Paths - 
        
            * If no path is given, lists files and directories in current directory.

            * If path of a directory is given, lists files and directories in given directory.

            * If path of a file is given, lists information about the file

            * If the path is invalid, throws an error

        * Flags - 

            * -l lists all relevant information about path

            * -a lists all the hidden files and folders too

    * _Syntax_ :

        `$ ls -<flags> <dir_name>` : changes to home directory

6. **`pinfo`**
    * _Output_ : Prints the relevant information about the given pid (taken as shell's pid if no pid is provided):

        * process id

        * process status (R for running, S for sleeping, Z for zombie; Append '+' if process is run in foreground)

        * memory usage

        * executable path

    * _Syntax_ : 
    
        `$ pinfo <pid>`

7. **`history`**
    * _Output_ : Displays upto 10 previously executed commands in terminal. Included commands from previous runs of the shell as well.
    * _Syntax_ :

        `$ history`

8. **`discover`**
    * _Output_ : 

        * Paths - 
        
            * If no directory path is given, uses current directory

            * If no search path is given, lists files and directories in given directory based on flags

            * If the path is invalid, throws an error

        * Flags - 

            * -f lists/searches only files

            * -d lists/searches only directories

        * CANNOT search for hidden files and folders

    * _Syntax_ :

        `$ discover -<flags> <dir_name>` : changes to home directory

9. **`jobs`**
    * _Output_ : Displays all processes running in background along with pid and status (running or stopped)

        * Flags - 
            * -s print only stopped processes
            * -r print only running processed
    * _Syntax_ :

        `$ jobs -<flags>`

10. **`sig`**
    * _Output_ : Send the signal corresponding to the given signal number to the given job bumber (based on sequential order printed in jobs). Throws an error if either job number or signal number are invalid.
    * _Syntax_ :

        `$ sig <job_number> <signal_number>`

11. **`fg`**
    * _Output_ : Brings the running or stopped background job corresponding to job number to the foreground, and changes
    its state to running.
    * _Syntax_ :

        `$ fg <job_number>`

12. **`bg`**
    * _Output_ : Changes the state of a stopped background job to running (in the background).
    * _Syntax_ :

        `$ bg <job_number>`

13. Any other process is run as in linux terminal using `execvp`

---
