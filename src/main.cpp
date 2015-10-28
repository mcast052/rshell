// Melissa Castillo 
// CS100 ASSIGNMENT 1, main.cpp 
// 10/25/2015 
#include <iostream> 
#include <boost/tokenizer.hpp> 
#include <string>
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
    return 0; 
}
