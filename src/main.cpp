// Melissa Castillo, mcast052 
// Jeremy Chan, jchan107
// CS100 ASSIGNMENT 1, main.cpp 
#include <iostream> 
#include <boost/tokenizer.hpp> 
#include <string>
#include "connections.h" 

int main()
{
    using namespace std; 
    using namespace boost;
    cout <<"$ "; 
    string tkn_check;
    getline(cin,tkn_check);

    //parses
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(" $",";#");
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

    tokenizer::iterator iter2;
    bool ifHash = false;
    for(iter2 = tkn.begin();iter2 != tkn.end();
    ++iter2)
    {
        if(*iter2 == "#")
        {
            indivCommand.push_back(*iter2);
            ifHash = true;
            break;
        }
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
    //makes sure hash doesnt go into the commands vector
    if(!indivCommand.empty()&& ifHash == false)
    {
        commands.push_back(indivCommand);
    }
    
    //outputs the vector

    for(unsigned int i = 0; i < commands.size(); i++)
    {
        cout << "Command at vector " << i << " contains: " ;
        for(unsigned int j = 0; j < commands.at(i).size();j++)
        {
            cout << commands.at(i).at(j)<< " ";
        }
        cout << endl;
    }  
    
    //Vector that will hold objects of our class
    vector<Connectors *> args;   
    for(unsigned int i = 0; i < commands.size() - 1; i++) 
    //Traverses through outer vector 
    {
        //SPECIAL CASE: First command is always run
        if(i == 0) 
        {
            args.push_back(new Semicolon_Connector(0, commands.at(i) )); 
            //args.push_back(obj);
        }
        else if(commands.at(i).at(0) == ";") 
        {
            //Gets vector<string> to the right
            //Does not take the actual sign 
            args.push_back(new Semicolon_Connector(0, commands.at(i + 1)));
        } 
        else if(commands.at(i).at(0) == "&&")
        { 
            args.push_back(new AND_Connector(0, commands.at(i + 1) ));  
        }
        else if(commands.at(i).at(0) == "||")
        {
            args.push_back(new OR_Connector (0, commands.at(i + 1) ));  
        }
    }    
    
    unsigned int i = 0; 
    //Executes each command
    for(i = 0; i < args.size()-1; i++)
    {
        //Dynamically calls appropriate execute() function
        args.at(i)->execute();
        //Variable holds whether the current command failed or succeeded
        bool prev = args.at(i)->get_prevstate();
        //Changes next command's bool to prev
        args.at(i + 1)->set_prevstate(prev);
    }
    // gets rid of out-of-bounds error
    args.at(i)->execute();

    //Deallocates objects and removes pointers
    for(unsigned int i = 0; i < args.size(); i++)
    { 
        delete args[i]; 
    } 
    args.clear();
    return 0; 
}     


