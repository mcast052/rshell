// Melissa Castillo, mcast052 
// Jeremy Chan, jchan107
// CS100 ASSIGNMENT 1, main.cpp 

#include <iostream> 
#include <boost/tokenizer.hpp> 
#include <string>
#include <"connections.h"> 
using namespace std;
using namespace boost;

int main()
{
    string tkn_check;
    getline(cin,tkn_check);

    //parses

    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(" ",";");
    tokenizer tkn(tkn_check,sep);

    //Shows where it is parsed

    for(tokenizer::iterator iter = tkn.begin();iter != tkn.end();
    ++iter)
    {
        cout << *iter << endl;   
    }

    //puts the parsed values into vectors by  command and connectors
    vector< vector<string> > commands;
    vector<string> indivCommand;

    for(tokenizer::iterator iter2 = tkn.begin();iter2 != tkn.end();
    ++iter2)
    {
        if(*iter2 == ";" || *iter2 == "||" || *iter2 == "&&")
        {
            commands.push_back(indivCommand);
            indivCommand.clear();
            indivCommand.push_back(*iter2);
            commands.push_back(indivCommand);
            indivCommand.clear();
        }
        else
        {
            indivCommand.push_back(*iter2);
        }
    }
    //pushes last command into the vector
    if(!indivCommand.empty())
    {
        commands.push_back(indivCommand);
    }
    
    //outputs the vector

    for(int i = 0; i < commands.size(); i++)
    {
        cout << "Command at vector " << i << " contains: " ;
        for(int j = 0; j < commands.at(i).size();j++)
        {
            cout << commands.at(i).at(j)<< " ";
        }
        cout << endl;
    }   
    
    //Vector that will hold objects of our class
    vector<Connectors *> args;   
    for(unsigned int i = 0; i < commands.size(); i++) 
    //Traverses through outer vector 
    {
        //SPECIAL CASE: First command is always run
        if(i == 0) 
        {
            //Sets bool to true, command always run
            new Semicolon obj(1, commands.at(i) ); 
        }
        else if(commands.at(i).at(0) == ";") 
        {
            //Gets vector<string> to the right
            //Does not take the actual sign 
            new Semicolon obj(1, commands.at(i + 1);
        } 
        else if(commands.at(i).at(0) == "&&")
        { 
            //Sets bool to false, so it does not run w/o checking
            new AND obj(0, commands.at(i + 1) ); 
        }
        else if(commands.at(i).at(0) == "||")
        {
            //Sets bool to true, so it does not run w/o checking   
            new OR obj(1, commands.at(i + 1) ); 
        }
    }    
    
    //Executes each command
    for(unsigned int i = 0; i < args.size(); i++)
    {
        //Dynamically calls appropriate execute() function
        args.at(i).exectute();
        //Variable holds whether the current command failed or succeeded
        bool prev = args.at(i).check_prevstate(); 
        //Changes next command's bool to prev
        args.at(i + 1).set_prevstate(prev); 
    }  

    //Deallocates objects and removes pointers
    for(unsigned int i = 0; i < args.size(); i++)
    { 
        delete args[i]; 
    } 
    args.clear();     
       
    return 0; 
}
