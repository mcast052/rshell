Melissa Castillo

Jeremy Chan

RSHELL
======
By: Melissa Castillo [mcast052] (https://github.com/mcast052), Jeremy Chan [jchan107] (https://github.com/jchan107)

> CS100 (FALL 2015), Assignment #1

Description
-----------
Rshell is a command shell, which is modeled after Bash, that can execute all the commands, except for those that are built-in to bash (such a "cd"). It can run a string of chained commands, with no limit to the number of commands and can handle any combinations of connectors. 
Example: 
  ```sh
  $ ls -a; mkdir google && echo hello || echo world; exit
  ```
The **exit** command has been changed. Instead of closing the terminal when it is called, as it does in Bash, it simply exits rshell. 

Known Bugs
---------
