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
***cd:*** cannot run in rshell, because it is built-in to bash 

***'#' at the end of the word:***

  ```sh 
  $ echo hello# world
  
  RSHELL OUTPUT: 
  hello
  
  BASH OUTPUT: 
  hello# world
  ```
  
***TAB:*** If a tab is entered in a string of commands, rshell does not remove the TAB, instead attaching it to the beginning of a command. Therefore, the command will not run.

  ```sh 
  $ echo hello;     ls
  
  RSHELL OUTPUT: 
  hello 
  execvp failed in child
  
  BASH OUTPUT: 
  hello 
  LICENSE Makefile README.md src tests
  ```
  
***Consecutive spaces:*** Causes an out-of-range error rather than reprompting

***Creating new file with cat:*** Does not recognize redirection symbol and will not run the command.
  
