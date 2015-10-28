// Melissa Castillo 
// CS100 ASSIGNMENT 1, main.cpp 
// 10/25/2015 
#include <iostream> 
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
    return 0; 
}
