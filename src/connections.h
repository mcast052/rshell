#include <iostream> 
using namespace std; 

class Connectors
{
    private: 
        bool prevstate; //Will hold value stating if prev state passed or failed
    public: 
        void set_prevstate(bool prev)
        {
            prevstate = prev; 
        }
        bool get_prevstate()
        {
            return prevstate;
        }
        virtual bool execute(char arr[]) = 0; //Pure virtual function
};


class Semicolon: private Connectors
{
    public:
        Semicolon()
        {
            Connectors::set_prevstate(1); 
        }
        Semicolon(bool prev)
        {
            Connectors::set_prevstate(prev); 
        }
        virtual bool execture(char arr[]) 
        {
            //Always executres, no matter if the previous command failed or passed
        }
};

class AND: private Connectors
{
    public: 
        AND()
        {
            Connectors::set_prevstate(1); 
        }
        AND(bool prev)
        {
            Connectors::set_prevstate(prev); 
        }
        virtual bool execute(char arr[])
        {
            if(Connectors::get_prevstate() == 0)
                return false; 
            else
                //Execute command (only does when previous command succeeded)
        }
}; 

class OR: private Connectors
{
    public: 
        OR()
        {
            Connectors::set_prevstate(1); 
        }
        OR(bool prev)
        {
            Connectors::set_prevstate(prev); 
        }
        virtual bool execute(char arr[])
        {
            if(Connectors::get_prevstate() == 1)
                return false; 
            else 
                //Execute command (only when previous command fails
        }
};
