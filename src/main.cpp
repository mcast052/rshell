// Melissa Castillo 
// CS100 ASSIGNMENT 1, main.cpp 
// 10/25/2015 
#include <iostream> 
<<<<<<< HEAD
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
=======
#include <boost/tokenizer.hpp>
#include "connectors.h" 

using namespace std; 
using namespace boost;  
int main(int argc, char* argv[])
{
    string line; 
    getline(cin, line); 
    tokenizer<> tok(line);     
    
    vector<Connectors *> v; 
    tokenizer::iterator it; 
    char args[100]; 
    int i = 0; 
    for(it = tok.begin(); it != tok.end(); it++)
    {   
        if(*it == ";" || *it == "&&" || *it == "||")
        {
            arr[i + 1] = NULL; //adds NULL to the end of array
            if(*it == ";") 
            {
                Semicolon S(1, args); 
                v.pushback(S);    
            }
            else if(*it == "&&")
            {
                AND A(1, args);
                v.pushback(A);   
            }
            else
            {
                OR O(1, args); 
                v.pushback(O);
            } 
            i = 0 
            //then clear v
        }
        else
        args[i] = *it; 
        i++;
    }       
>>>>>>> a58b50f7d1383c10a542b3cd9b62d4dd14aa2e16
    return 0; 
}
