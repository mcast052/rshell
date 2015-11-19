#include <iostream> 
#include <vector> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>
#include <cstdlib>

using namespace std; 
class ABC //Abstract Base Class
{
    public:
        virtual ~ABC()
        {} 
        virtual void execute() = 0; //pure virtual function
};

class Connectors: public ABC
{
    private:
        bool prevstate;
        bool exitbool;          
        //Will hold value stating if prev state passed or failed 
    public: 
        void set_exit(bool exbool)
        {
            exitbool = exbool; 
        }
        bool get_exit()
        {
            return exitbool; 
        }
        void set_prevstate(bool prev)
        {
            prevstate = prev; 
        }
        bool get_prevstate()
        {
            return prevstate;
        }
        virtual void execute() 
        {}

}; 


class Semicolon_Connector: public Connectors
{
    private: 
        const char * argv[25];
        string first; 

    public:         
        Semicolon_Connector(bool prev, const vector<string> &args)
        {
            set_prevstate(prev);
            first = args.at(0);  
            set_exit(0); 

            unsigned int i = 0; 
            for(i = 0; i < args.size(); i++)
            {
               argv[i] = args.at(i).c_str();  
            }
            argv[i] = NULL;  
        } 
        virtual void execute() 
        {
           string exitcmd = "exit"; 
           if(first.compare(exitcmd) == 0)
           {   
               set_exit(1); 
               return; 
           }           

           //Always executes, no matter if the previous 
           //command failed or passed
           pid_t c_pid = fork(); //Child's process ID
           pid_t pid; //Parent's process ID  
           int status; 
        
           if(c_pid < 0) 
           {
               perror("Forking failed");
               set_prevstate(0);    
               return; 
           }   
           else if(c_pid == 0) 
           { 
               //If fork() == 0, this fork is the child process
                int run = execvp(argv[0], const_cast<char * const *>(argv));
                if( run == -1) 
                {  
                    perror("execvp failed in child");
                    set_prevstate(0);
                    //return;
                    exit(127); 
                }    
           } 
           else
           {
               if((pid = waitpid(c_pid, &status, 0)) < 0) 
               { 
                   perror("ERROR while waiting");
                   //if waitpid returns -1, there was an ERROR 
                   set_prevstate(0);
                   return;  
               }
               //else, child process if finished and the parent can continue
               //the rest of its process.
               if(status == 0) 
               { 
                   set_prevstate(1); 
                   return;
               }
               else if(status != 0)
               {
                   set_prevstate(0); 
                   return;
               }
           }
        } 
};

class AND_Connector: public Connectors
{
    private: 
        const char * argv[25];
        string first; 

    public:
        AND_Connector(bool prev, const vector<string> & args)
        {
            set_prevstate(prev);
            first = args.at(0); 
            set_exit(0); 

            unsigned int i = 0;   
            for(i = 0; i < args.size(); i++)
            {
               argv[i] = args.at(i).c_str();  
            }
            argv[i] = NULL;  
        }
        virtual void execute()
        {
            if(get_prevstate() == 0)
            { 
                return; 
            } 
            else
            {
               string exitcheck = "exit";
               if(first.compare(exitcheck) == 0)
               { 
                   set_exit(1); 
                   return;
               }
               pid_t c_pid = fork(); //Child's process ID
               pid_t pid; //Parent's process ID  
               int status; //Will indicate the status of the child process
               if(c_pid < 0) 
               {
                    perror("Error forking child"); 
                    set_prevstate(0); 
                    return;     
               } 
               else if(c_pid == 0)
               {
                   //If fork() == 0, this fork is the child process
                    int run = execvp(argv[0], const_cast<char * const *>(argv));
                    if( run == -1) 
                    {  
                        perror("execvp failed in child");
                        set_prevstate(0);
                        //return;
                        exit(127); 
                    }     
               }
               else
               {
                    if((pid = waitpid(c_pid, &status, 0)) < 0) 
                    { 
                        //perror("ERROR");
                        //if waitpid returns -1, there was an ERROR 
                        perror("ERROR while waiting"); 
                        set_prevstate(0); 
                        return; 
                    }
                    //else, child process if finished and the parent can continue
                    //the rest of its process
                    if(status == 0)
                    {
                        set_prevstate(1); 
                        return; 
                    }
                    else if(status != 0)
                    {    
                        set_prevstate(0); 
                        return;
                    }  
                    
               }
            }
           
        }
}; 

class OR_Connector: public Connectors
{
    private: 
        const char * argv[25]; 
        string first;  

    public:
        OR_Connector(bool prev, const vector<string> &args)
        {
            first = args.at(0); 
            set_prevstate(prev); 
            set_exit(0); 

            unsigned int i = 0;  
            for(i = 0; i < args.size(); i++)
            {
              argv[i] = args.at(i).c_str();  
            }
            argv[i] = NULL;  
        } 
        virtual void execute()
        {
            if(get_prevstate() == 1)
            { 
                return; 
            } 
            else
            { 
                string exitcheck = "exit";
                if(first.compare(exitcheck) == 0)
                { 
                    set_exit(1); 
                    return;
                }
                //Execute command (only when previous command fails
                pid_t c_pid = fork(); //Child's process ID
                pid_t pid; //Parent's process ID  
                int status; //Will indicate the status of the child process 
            
                if(c_pid < 0)
                { 
                    set_prevstate(0);    
                    return; 
                }   
                else if(c_pid == 0) 
                {
                    //If fork() == 0, this fork is the child process
                    int run = execvp(argv[0], const_cast<char * const *>(argv));
                    if( run == -1) 
                    {  
                        perror("execvp failed in child");
                        set_prevstate(0);
                        exit(127); 
                    }                     
                }
                else 
                {
                    if((pid = waitpid(c_pid, &status, 0)) < 0) 
                    {
                        perror("ERROR while waiting");
                        //if waitpid returns -1, there was an ERROR 
                        set_prevstate(0);
                        return;  
                    }
                    //else, child process if finished and the parent can continue
                    //the rest of its process.
                    if(status == 0) 
                    { 
                        set_prevstate(1); 
                        return;
                    }
                    else if(status != 0) 
                    {   
                        set_prevstate(0); 
                        return; 
                    }
                }
            }   
        }
};

class Paren: class Connectors
{
    private:  
       vector<Connector *> v;   
       bool is_and; 
       bool is_or; 
       bool error_check; 

    public: 
       Paren(bool is_and_1, bool is_or_1, 
             bool prev, vector<string> commands)
       { 
            is_and = is_and_1; 
            is_or = is_or_1; 
            set_prevstate(prev); 

            error_check = false; 

            while(!error_check)
            {
                unsigned int j = commands.size() - 1;   
                for(unsigned int i = 0; i < commands.size(); i++) 
                //Traverses through outer vector 
                { 
                    if(i == 0 && commands.at(i).at(0) == ";") 
                    {
                        cout << "Syntax error near unexpected token ';'" << endl;
                        error_check = true;
                        break; 
                    }
                    else if(i == 0 && commands.at(i).at(0) == "||") 
                    {
                        cout << "Syntax error near unexpected token \"||\"" << endl; 
                        error_check = true;
                        break;
                    }
                    else if(i == 0 && commands.at(i).at(0) == "&&") 
                    {
                        cout << "Syntax error near unexpected token \"&&\"" << endl; 
                        error_check = true;
                        break;
                    }

                    //SPECIAL CASE: First command is always run
                    else if(i == 0) 
                    {
                        v.push_back(new Semicolon_Connector(0, commands.at(i) )); 
                    }
                    else if(commands.at(i).at(0) == ";") 
                    {
                        if(i == j)
                        {
                            cout << "Syntax error" << endl;
                            error_check  = true;
                            break;
                        } 
                        v.push_back(new Semicolon_Connector(0, commands.at(i + 1)));  
                    } 
                    else if(commands.at(i).at(0) == "&&")
                    { 
                        if(i == j) 
                        {

                            cout << "Syntax error" << endl;
                            error_check = true;
                            break; 
                        }
                        v.push_back(new AND_Connector(0, commands.at(i + 1) ));   
                    }
                    else if(commands.at(i).at(0) == "||")
                    {
                        if(i == j) 
                        {
                            cout << "Syntax error" << endl;
                            error_check = true;
                            break; 
                        }
                        v.push_back(new OR_Connector (0, commands.at(i + 1) ));   
                        }
                    }
            }
       }

       virtual void execute()
       {
            if(is_or && get_prevstate)
            {
                return; 
            }
            else if(is_and && !get_prevstate)
            {
                return; 
            }

            for(unsigned int i = 0; i < v.size(); i++)
            {
                v.at(i)->execute;       
            }
            set_prevstate(v.at(v.size() - 1)->get_prevstate()); 
       }
       bool get_error()
       {
           return error_check; 
       }
};
