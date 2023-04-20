# **Assignment-2** 
### **Operating Systems and Networks, Monsoon 2022**
---
```
Name    : Harsh Bansal
Roll No : 2021101027
```
### **Directory Structure**
---
```
2021101027
|
+--- cd.c
|
+--- cd.h
|
+--- discover.c
|
+--- discover.h
|
+--- echo.c
|
+--- echo.h
|
+--- headers.h
|
+--- helper.c
|
+--- helper.h
|
+--- history.c
|
+--- history.h
|
+--- init.c
|
+--- init.h
|
+--- ls.c
|
+--- ls.h
|
+--- main.c
|
+--- Makefile
|
+--- mkdir.c
|
+--- mkdir.h
|
+--- pinfo.c
|
+--- pinfo.h
|
+--- process.c
|
+--- process.h
|
+--- prompt.c
|
+--- prompt.h
|
+--- pwd.c
|
+--- pwd.h
|
+--- README.md
```

### **Executing the Shell**
---
- First Compile the Code using the Following in the extracted Directory **2021101027_Assignment2** :- 
```
make
```
- Then Run the Code using 
```
./a.out
```


### **Specification-1**
---
- Printing Shell Prompt in every Iteration of the Shell.
```
<username@system_name:curr_dir>
```
- This Specification is Executed in the Following Files.
```
- prompt.c
- prompt.h
```
- The Username represents the Name of the User Executing the Shell.
- The System Name represents the Name of the System.
- Currrent Directory denotes the Current Directory in which the Shell is being executed right now. 
- The Current Directory is represented as **"~"** when the Shell is in the Directory in which it was executed. This represents the Home Directory.

### **Specification-2**
---
- The Following Command are Executed in this Specification.
```bash
cd
echo
pwd
```
- These Commands are Executed based on the Code Written in the Following Files.
```
- cd.c
- cd.h
- pwd.c
- pwd.h
- echo.c
- echo.h
```
#### **Echo**
- Echo Command Prints a Message on the Terminal.
- For Example :
```bash
echo This is the OSN Assignment
```
- Gives the Following Output
```
This is the OSN Assignment
```
- General Usage
```bash
echo <input_string>
```

#### **cd**
- cd changes the Present Working Directory of the Shell.
- It can be Executed using the Following Command.
```bash
cd <target_directory>
```
- We can give both Absolute and Relative Path as the Target Directory
- The Following Flags can also be executed in the cd Command
```bash
cd .    # This Takes us to the Current Directory
cd ..   # This Takes us to the Previous Directory
cd -    # Prints the Previous Working Directory and also changes to that Directory
cd ~    # This takes us to the Home Directory 
```

#### **pwd**
- This Command is Used to Print the Absolute Path of the Current Working Directory of the Shell.
- The Following Command can be used to Execute pwd.
```bash
pwd
```
### **Specification-3**
---
#### **ls**
- List all the Directories and Files of the Given or the Current Working Directory.
- The Code for this Command is written in the Following Files:
```
- ls.c
- ls.h
```
- The Following Flags and Methods can be Used to Execute the ls Command.
```bash
ls <directory>
ls -a/-l/-al/-la 
ls -a/-l/-al/-la <directory>
ls <directory_path>
ls <filename>
```
- The **"-l"** flag prints out all the details of the Current Working Directory.
- The **"-a"** flag shows all the hidden files in the Current Working Directory.
- Color Codiing is done in the Output of this Command.
```
Blue  --> For Directories
Green --> For Executables
```
### **Specification-4**
---
- This Specification Executes the System Commands as both Foreground and Background Processes.
- The Command above runs in the Background.
- Inorder to execute a Foreground Command just Execute the Command Normally.
```bash
sleep 5
```
- Foreground implies that the shell will wait for this process to complete and regain control when this process exits.
- The Time-Taken for a Foreground Process is printed after completion of it's Execution.
```bash
<username@system_name: ~ took 5s >
```
- Incase of Multiple Foreground Processes the Total Time Taken by all of them Combined together is Printed.
- The Commands to be run in the Background are to be followed by an **"&"**
```bash
sleep 5 & 
```
- This implies that the shell will spawn that process and doesn't wait for the process to exit. It will keep taking other user commands.
- Multiple Commands can be Executed in the Background.
```bash
sleep 5 & sleep 10 & sleep 20 &
```
- The Command above Executes Multiple Background Processes with Seperate pid's for each one of them.
- The Sample Output for a Background Process.
```bash
[1] 5670
sleep with pid = 5670 exited normally
```
- The code for this specification can be found in the Following Files.
```
process.c
process.h
helper.c
helper.h
```
### **Specification-5**
---
- pinfo prints the process-related info of your shell program.
- This can be Executed using the Following Command.
```bash
pinfo <pid>
```
- When Pid is provided it, The Command Outputs the Data for the Process with that PID. 
- When the Pid is not provided, The Command gives Data regarding the Shell.
- Sample Output
```bash
pid : 7777
process Status : {R/S/S+/Z} 
memory : 123456 {Virtual Memory} 
executable Path : /usr/bin/gcc
```
- The Code for this Command can be found in the Following Files.
```
pinfo.c
pinfo.h
```
### **Specification-6**
---
- Prints the Exit Message after the Background Process Ends.
- Sample Input
```bash
sleep 5 &
```
- Sample Output
```bash
[1] 4567
# Waits for 5 Seconds
sleep with pid = 4567 exited normally/abnormally
```
- The Code for this Specification can be found in the Following Files.
```
process.c
process.h
```
### **Specification-7**
---
- The Discover Command searches for files in a Directory Hierarchy.
- Depth First Search (DFS) Graph Traversal is Used for Searching in the Directory Hierarchy.
- The Discover Command does not Search for Hidden Files.
- The Following Commands can be executed to run the Discover Command.
```bash
discover
discover <target_dir> <type_flags> <file_name>
discover <target_dir> -d/-f/-d -f
discover -d/-f/-d -f <file_name>
discover <file_name>
discover <target_dir>
```
- The Code for the Specification can be found in the Following Files.
```
discover.c
discover.h
```
### **Specification-8**
---
- The History Command prints the last ten Commands given by the User to the Shell.
- The Commands are stored across sessions of the Shell.
- This is achieved using a Text File.
```bash
.history.txt
```
- This File is created and handeled by the Shell at the System Root.
- The Code for this Specification can be Found in the Following Files.
```bash
history.c
history.h
```
### **Exiting the Shell**
---
- The Shell can be Terminated using the Following Commands.
```bash
q
quit
exit
```
### **Other Files**
---
- The Following Files help in Execution of the Shell.
```
main.c
headers.h
init.c
init.h
```
