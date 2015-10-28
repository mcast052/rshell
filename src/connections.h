#include <iostream> 
#include <vector> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 

using namespace std; 

class Connectors
{
    private:
        bool prevstate;  
        //Will hold value stating if prev state passed or failed 
    public: 
        void set_prevstate(bool prev)
        {
            prevstate = prev; 
        }
        bool get_prevstate()
        {
            return prevstate;
        }
        void bool execute() = 0; //Pure virtual function
};


class Semicolon: private Connectors
{
    private: 
        char argv[];        
        Semicolon()
        {
            Connectors::set_prevstate(1); 
        }
        Semicolon(bool prev, const vector<string> &args)
        {
            Connectors::set_prevstate(prev);
            for(unsigned int i = 0; i < args.size(); i++)
            {
               argv[i] = args.at(i); 
            }
            argv[i] = NULL;  
        }
        virtual void execute() 
        {
            //Always executres, no matter if the previous 
            //command failed or passed
            pid_t c_pid = fork(); //Child's process ID
            pid_t pid; //Parent's process ID  
            int status; //Will indicate the status of the child process 
            
            if(c_pid < 0) 
            {
               perror("Forking failed"); 
               exit(1); 
            }
            else if(c_pid == 0) 
            {
               //If fork() == 0, this fork is the child process
               execvp(argv[0], argv); 
               perror("execvp failed in child");
               //execvp, if successful, never returns
            } 
            else 
            {
                if( (pid = waitpid(c_pid,&status) < 0) 
                { 
                    perror("ERROR");
                    //if waitpid returns -1, there was an ERROR 
                    exit(1); 
                }
                //else, child process if finished and the parent can continue
                //the rest of its process. 
                Connectors::set_prevstate(1); 
                return; 
               //return 1 == Coommand has been executed
            }
         } 

               //If fork > 0, this fork is the parent process 
            }
        }
};

class AND: private Connectors
{
    private: 
        char argv[];

    public: 
        AND()
        {
            Connectors::set_prevstate(1); 
        }
        AND(bool prev, const vector<string> & args)
        {
            Connectors::set_prevstate(prev); 
            for(unsigned int i = 0; i < args.size(); i++)
            {
               argv[i] = args.at(i); 
            }
            argv[i] = NULL;  
        }
        virtual void execute()
        {
            if(Connectors::get_prevstate() == 0)
                return; 
            else
                //Execute command (only does when previous command succeeded)
        }
}; 

class OR: private Connectors
{
    private: 
        char argv[]; 

    public: 
        OR()
        {
            Connectors::set_prevstate(1); 
        }
        OR(bool prev, const vector<string> &args)
        {
            Connectors::set_prevstate(prev); 
            for(unsigned int i = 0; i < args.size(); i++)
            {
               argv[i] = args.at(i); 
            }
            argv[i] = NULL;  
 
        }
        virtual void execute()
        {
            if(Connectors::get_prevstate() == 1)
                return; 
            else 
                //Execute command (only when previous command fails
        }
};
