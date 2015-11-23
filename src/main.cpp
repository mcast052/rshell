// Melissa Castillo, mcast052 
// Jeremy Chan, jchan107
// CS100 ASSIGNMENT 1, main.cpp 
#include <iostream> 
#include <boost/tokenizer.hpp> 
#include <string>
#include <stdio.h>
#include <iterator>
#include "connections.h" 

int main()
{
    using namespace std; 
    using namespace boost;
    
    bool exitcheck = 0; 
    do
    {
        char * name = getlogin(); 
        if(name == NULL)
        {
            cout << "Retrieving username failed" << endl; 
            exit (127); 
        }
        char hostname[1024]; 
        hostname[1023] = '\0'; 
        int hostcheck = gethostname(hostname, 2013); 
        if(hostcheck == -1)
        {
            cout << "Retrieving host name failed" << endl; 
            exit(127); 
        }
        cout << name << "@" << hostname << "$ ";
        string tkn_check;
        getline(cin,tkn_check);
        if(!tkn_check.empty())
        {
            //parses
            typedef tokenizer<char_separator<char> > tokenizer;
            char_separator<char> sep(" $", ";#|&()[]\"");
            tokenizer tkn(tkn_check,sep);
            bool error = false;

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
            tokenizer::iterator ite3 = tkn.begin();
            bool ifHash = false;
            for(iter2 = tkn.begin();iter2 != tkn.end(); ++iter2)
            {

                if(*iter2 == "#")
                {
                    if(indivCommand.size() != 0)
                    {
                        commands.push_back(indivCommand); 
                        ifHash = true;
                        break;
                    }
                    else
                    {
                        ifHash = true;
                        break;
                    }
                }
               
                if(*iter2 == "echo")
                {
                    int numOfQuotes = 0;
                    string tempQuote; 
                    for(tokenizer::iterator echoiter = iter2;echoiter != tkn.end(); ++echoiter)
                    {
                        if(*echoiter == "\"")
                        {
                            numOfQuotes++;
                            while(iter2 != echoiter)
                            {
                                if(*iter2 != "\"")
                                {
                                    if(*iter2 == "echo")
                                    {
                                        indivCommand.push_back(*iter2);
                                    }
                                    else
                                    {
                                        if(tempQuote == "")
                                        {
                                            tempQuote = *iter2;
                                        }
                                        else
                                        {
                                            tempQuote += " " + *iter2;
                                        }
                                    }
                                }
                                iter2++;
                            }
                            while(*iter2 != "\"")
                            {
                                indivCommand.push_back(*iter2);
                                iter2++;
                               break; 
                            }
                            if(tempQuote != "")
                            {
                                indivCommand.push_back(tempQuote);
                            }
                            tempQuote = "";
                        }
                        
                    }
                    if(numOfQuotes % 2 != 0)
                    {
                        cout << "Syntax error" << endl;
                        error = true;
                        break;
                    }
                }
               
          
                if(*iter2 == "(")
                {
                    while(*iter2 != ")")
                    {
                        if(*iter2 == "echo")
                        {
                            int numOfQuotes;
                            string tempQuote; 
                            for(tokenizer::iterator echoiter = iter2;echoiter != tkn.end(); ++echoiter)
                            {
                                if(*echoiter == "\"")
                                {
                                    numOfQuotes++;
                                    while(iter2 != echoiter)
                                    {
                                        if(*iter2 != "\"")
                                        {
                                            if(*iter2 == "echo")
                                            {
                                                indivCommand.push_back(*iter2);
                                            }
                                            else
                                            {
                                                if(tempQuote == "")
                                                {
                                                    tempQuote = *iter2;
                                                }
                                                else
                                                {
                                                    if(*iter2 != "\"")
                                                    {
                                                        tempQuote += " " + *iter2;
                                                    }
                                                }
                                            }
                                        }
                                        iter2++;
                                    }
                                    while(*iter2 != "\"")
                                    {
                                        indivCommand.push_back(*iter2);
                                        iter2++;
                                        break; 
                                    }
                                    if(tempQuote != "")
                                    {
                                        indivCommand.push_back(tempQuote);
                                    }
                                    tempQuote = "";
                                }
                        
                            }
                            if(numOfQuotes % 2 != 0)
                            {
                                cout << "Syntax error" << endl;
                                error = true;
                                break;
                            }

                        }

                        if(*iter2 == ";" || *iter2 == "|" || *iter2 == "&")
                        {
                            if(*iter2 == "|" || *iter2 == "&")
                            {
                                tokenizer::iterator iter3 = iter2;
                                iter3++;
                        
                        //if & or | is at the end it will make an error
                                if(iter3 == tkn.end())
                                {
                                    cout << "Syntax error" << endl;
                                    error = true;
                                    break;
                                }
                                else
                                {
                            //now checks to see if connector is | or &
                                    if(*iter2 == "|")
                                    {
                                //checks if connector is || 
                                //and if it is then you need another 
                                //iterator to see next string val
                                        if(*iter3 == "|")
                                        {
                                            tokenizer::iterator iter4 = iter3;
                                            iter4++;
                                 
                                    //if this iterator is at the end 
                                    //that means the connector at the end is: 
                                    //||(which is okay)
                                            if(iter4 == tkn.end())
                                            {
                                                if(indivCommand.size() != 0)
                                                {
                                                    commands.push_back(indivCommand); 
                                            //push into commands, 
                                            //a vector holding list of commands 
                                            //before connector
                                                }
                                                indivCommand.clear(); 
                                                string tempConnector = *iter2 + *iter3;
                                                indivCommand.push_back(tempConnector);
                                                commands.push_back(indivCommand); 
                                        // pushes single connector into commands
                                                indivCommand.clear(); 
                                        // clears vector againv
                                                break;
                                            }
                                            else
                                            {
                                        //if the connector goes to: ||| 
                                        //it returns an error
                                                if(*iter4 == "|")
                                                {
                                                    cout << "Syntax error at '|||'" << endl;
                                                    error = true;
                                                    break;
                                                }
                                                else
                                                {
                                            //if connector is the right size 
                                            //then it just puts it into the vector 
                                            // clears vector holding list of commands
                                                    string tempConnector = *iter2 + *iter3;
                                                    indivCommand.push_back(tempConnector); 
                                            // pushes single connector into commands
                                                    iter2 = iter3;
                                                }
                                            }
                                        }
                                        else//if only one | then return error
                                        {
                                            cout << "Syntax error at '|'" << endl;
                                            error = true;
                                            break;
                                        }
                                    }
                                    else if(*iter2 == "&")
                                    {
                                        if(*iter3 == "&")
                                        {
                                            tokenizer::iterator iter4 = iter3;
                                            iter4++;
                                            if(iter4 == tkn.end())
                                            {
                                                if(indivCommand.size() != 0)
                                                {
                                                    commands.push_back(indivCommand); 
                                            //push into commands, 
                                            //a vector holding list of 
                                            //commands before connector
                                                }
                                                indivCommand.clear(); 
                                        // clears vector holding list of commands
                                                string tempConnector = *iter2 + *iter3;
                                                indivCommand.push_back(tempConnector);
                                                commands.push_back(indivCommand); 
                                        // pushes single connector into commands
                                                indivCommand.clear();
                                                break;
                                            }
                                            else
                                        {
                                                if(*iter4 == "&")
                                                {
                                                    cout << "Syntax error at '&&&'" << endl;
                                                    error = true;
                                                    break;
                                                }
                                                else
                                                { 
                                            // clears vector holding list of commands
                                                    string tempConnector = *iter2 + *iter3;
                                                    indivCommand.push_back(tempConnector); 
                                            // pushes single connector into commands
                                            // clears vector againv
                                                    iter2 = iter3;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            cout << "Syntax error at '&'" << endl;
                                            error = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            else// only in use for connector: ;
                            {
                                tokenizer::iterator iter3 = iter2;
                                iter3++;
                                if(iter3 != tkn.end())
                                {
                                    if(*iter3 == ";")
                                    {
                                        cout << "Syntax error at ';;'" << endl;
                                        error = true;
                                        break;
                                    }
                                }
                                indivCommand.push_back(*iter2); // clears vector againv
                            }
                        }
                        else
                        {
                            if(*iter2 != "\"")
                            {
                                indivCommand.push_back(*iter2);
                            }
                        }

                        iter2++;
                        if(iter2 == tkn.end())
                        {
                            cout << "Syntax error" << endl;
                            error = true;
                            break;
                        }
                    }
                    if(error == true)
                    {
                        break;
                    }
                            indivCommand.push_back(*iter2);
                            commands.push_back(indivCommand);
                            indivCommand.clear();
                    
                }
                
                else if(*iter2 == ";" || *iter2 == "|" || *iter2 == "&")
                {
                    if(*iter2 == "|" || *iter2 == "&")
                    {
                        tokenizer::iterator iter3 = iter2;
                        iter3++;
                        
                        //if & or | is at the end it will make an error
                        if(iter3 == tkn.end())
                        {
                            cout << "Syntax error" << endl;
                            error = true;
                            break;
                        }
                        else
                        {
                            //now checks to see if connector is | or &
                            if(*iter2 == "|")
                            {
                                //checks if connector is || 
                                //and if it is then you need another 
                                //iterator to see next string val
                                if(*iter3 == "|")
                                {
                                    tokenizer::iterator iter4 = iter3;
                                    iter4++;
                                 
                                    //if this iterator is at the end 
                                    //that means the connector at the end is: 
                                    //||(which is okay)
                                    if(iter4 == tkn.end())
                                    {
                                        if(indivCommand.size() != 0)
                                        {
                                            commands.push_back(indivCommand); 
                                            //push into commands, 
                                            //a vector holding list of commands 
                                            //before connector
                                        }
                                        indivCommand.clear(); 
                                        string tempConnector = *iter2 + *iter3;
                                        indivCommand.push_back(tempConnector);
                                        commands.push_back(indivCommand); 
                                        // pushes single connector into commands
                                        indivCommand.clear(); 
                                        // clears vector againv
                                        break;
                                    }
                                    else
                                    {
                                        //if the connector goes to: ||| 
                                        //it returns an error
                                        if(*iter4 == "|")
                                        {
                                            cout << "Syntax error at '|||'" << endl;
                                            error = true;
                                            break;
                                        }
                                        else
                                        {
                                            //if connector is the right size 
                                            //then it just puts it into the vector
                                            if(indivCommand.size() != 0)
                                            {
                                                 commands.push_back(indivCommand); 
                                                 //push into commands, 
                                                 //a vector holding list of 
                                                 //commands before connector
                                            }
                                            indivCommand.clear(); 
                                            // clears vector holding list of commands
                                            string tempConnector = *iter2 + *iter3;
                                            indivCommand.push_back(tempConnector);
                                            commands.push_back(indivCommand); 
                                            // pushes single connector into commands
                                            indivCommand.clear(); // clears vector againv
                                            iter2 = iter3;
                                        }
                                    }
                                }
                                else//if only one | then return error
                                {
                                    cout << "Syntax error at '|'" << endl;
                                    error = true;
                                    break;
                                }
                            }
                            else if(*iter2 == "&")
                            {
                                if(*iter3 == "&")
                                {
                                    tokenizer::iterator iter4 = iter3;
                                    iter4++;
                                    if(iter4 == tkn.end())
                                    {
                                        if(indivCommand.size() != 0)
                                        {
                                            commands.push_back(indivCommand); 
                                            //push into commands, 
                                            //a vector holding list of 
                                            //commands before connector
                                        }
                                        indivCommand.clear(); 
                                        // clears vector holding list of commands
                                        string tempConnector = *iter2 + *iter3;
                                        indivCommand.push_back(tempConnector);
                                        commands.push_back(indivCommand); 
                                        // pushes single connector into commands
                                        indivCommand.clear();
                                        break;
                                    }
                                    else
                                    {
                                        if(*iter4 == "&")
                                        {
                                            cout << "Syntax error at '&&&'" << endl;
                                            error = true;
                                            break;
                                        }
                                        else
                                        {
                                            if(indivCommand.size() != 0)
                                            {
                                                commands.push_back(indivCommand); 
                                                //push into commands, 
                                                //a vector holding list of commands 
                                                //before connector
                                            }
                                            indivCommand.clear(); 
                                            // clears vector holding list of commands
                                            string tempConnector = *iter2 + *iter3;
                                            indivCommand.push_back(tempConnector);
                                            commands.push_back(indivCommand); 
                                            // pushes single connector into commands
                                            indivCommand.clear(); 
                                            // clears vector againv
                                            iter2 = iter3;
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "Syntax error at '&'" << endl;
                                    error = true;
                                    break;
                                }
                            }
                        }
                    }
                    else// only in use for connector: ;
                    {
                        tokenizer::iterator iter3 = iter2;
                        iter3++;
                        if(iter3 != tkn.end())
                        {
                            if(*iter3 == ";")
                            {
                                cout << "Syntax error at ';;'" << endl;
                                error = true;
                                break;
                            }
                        }
                        if(indivCommand.size() != 0)
                        {
                             commands.push_back(indivCommand); //push into commands, a vector holding list of commands before connector
                        }
                        indivCommand.clear(); // clears vector holding list of commands
                        indivCommand.push_back(*iter2); // holds only the connector now
                        commands.push_back(indivCommand); // pushes single connector into commands
                        indivCommand.clear(); // clears vector againv
                    }
                }
                else
                {
                   if(*iter2 != "\"")
                   { 
                      indivCommand.push_back(*iter2);
                   }
                }
        
                ite3++;
            }
            //makes sure hash doesnt go into the commands vector
            if(!indivCommand.empty() && ifHash == false)
            {
                commands.push_back(indivCommand);
            }

            //outputs the vector
            /*
            for(unsigned int i = 0; i < commands.size(); i++)
            {
                cout << "Command at vector " << i << " contains: " ;
                for(unsigned int j = 0; j < commands.at(i).size();j++)
                {
                    cout << commands.at(i).at(j)<< " ";
                }
                cout << endl;
            }  
            */
            vector<Connectors *> args;
            if(error == false && commands.size() > 0)
            {
                //Vector that will hold objects of our class  
                for(unsigned int i = 0; i < commands.size(); i++) 
                    //Traverses through outer vector 
                {
                    if(commands.at(i).at(0) != "(" && commands.at(i).at(commands.at(i).size() - 1) == ")")
                    {
                        cout << "Syntax error" << endl;
                        error = true;
                        break;
                    }
                    if(commands.at(i).at(0) != "[" && commands.at(i).at(commands.at(i).size() - 1) == "]")
                    {
                        cout << "Syntax error" << endl;
                        error = true;
                        break;
                    }

                    if(commands.at(i).at(0) == "(" && commands.at(i).at(commands.at(i).size() - 1) == ")")
                    {
                        commands.at(i).at(0) = "()";
                        commands.at(i).pop_back();
                    }
                    if(commands.at(i).at(0) == "[" && commands.at(i).at(commands.at(i).size() - 1) == "]")
                    {
                        commands.at(i).at(0) = "test";
                        commands.at(i).pop_back();
                    }
                    else if(commands.at(i).at(0) == "[" && commands.at(i).at(commands.at(i).size() - 1) != "]")
                    {
                        cout << "Syntax error" << endl;
                        error = true;
                        break;
                    }
                }            
            }

            
            for(unsigned int i = 0; i < commands.size(); i++)
            {
                cout << "Command at vector " << i << " contains: " ;
                for(unsigned int j = 0; j < commands.at(i).size();j++)
                {
                    cout << commands.at(i).at(j)<< " ";
                }
                cout << endl;
            }
            
             
            if(error == false && commands.size() > 0)
            {
                //Vector that will hold objects of our class
                unsigned int j = commands.size() - 1;   
                for(unsigned int i = 0; i < commands.size(); i++) 
                    //Traverses through outer vector 
                {
                    if(i == 0 && commands.at(i).at(0) == ";") 
                    {
                        cout << "Syntax error near unexpected token ';' not here" << endl;
                        error = true;
                        break; 
                    }
                    else if(i == 0 && commands.at(i).at(0) == "||") 
                    {
                        cout << "Syntax error near unexpected token \"||\"" << endl; 
                        error = true;
                        break;
                    }
                    else if(i == 0 && commands.at(i).at(0) == "&&") 
                    {
                        cout << "Syntax error near unexpected token \"&&\"" << endl; 
                        error = true;
                        break;
                    }
                    
                    else if(i == 0 && commands.at(i).at(0) == "()")
                    {
                        args.push_back(new Paren(0, 0, 0, commands.at(i) )); 
                        error = args.at(args.size() - 1)->get_error(); 
                    }
                    //SPECIAL CASE: First command is always run
                    else if(i == 0) 
                    {
                        args.push_back(new Semicolon_Connector(0, commands.at(i) )); 
                    }
                    else if(commands.at(i).at(0) == ";") 
                    {
                        if(i == j)
                        {
                            cout << "Syntax error" << endl;
                            error  = true;
                            break;
                        }
                        if(commands.at(i + 1).at(0) == "()")
                        {
                           args.push_back(new Paren(0, 0, 0, commands.at(i + 1) )); 
                           error = args.at(args.size() - 1)->get_error(); 
                        } 
                        else
                        {
                            args.push_back(new Semicolon_Connector(0, commands.at(i + 1))); 
                        } 
                    }
                    else if(commands.at(i).at(0) == "&&")
                    { 
                        if(i == j) 
                        {
                            
                            cout << "Syntax error" << endl;
                            error = true;
                            break; 
                        }
                        if(commands.at(i + 1).at(0) == "()") 
                        {
                            //Set is_and_1 == 1, prev_state = 0, 
                            //and passes vector<string> in
                            args.push_back(new Paren(1, 0, 0, commands.at(i + 1) )); 
                            //Checks if there was an error while parsing 
                            //commands inside the parentheses constructor
                            error = args.at(args.size() - 1)->get_error(); 
                        }
                        else
                        {
                            args.push_back(new AND_Connector(0, commands.at(i + 1) ));
                        }   
                    }
                    else if(commands.at(i).at(0) == "||")
                    {
                        if(i == j) 
                        {
                            cout << "Syntax error" << endl;
                            error = true;
                            break; 
                        }
                        if(commands.at(i + 1).at(0) == "()") 
                        {
                            //Sets is_or_1 = 1, prev_state = 0, 
                            //and passes vector<string> in
                            args.push_back(new Paren(0, 1, 0, commands.at(i + 1) ));
                            //Checks if there was an error while parsing
                            //commands inside the parentheses constructor
                            error = args.at(args.size() - 1)->get_error();   
                        }
                        else
                        {
                            args.push_back(new OR_Connector (0, commands.at(i + 1) ));
                        }   
                    }
                }
            } 

            if(error == false && commands.size() > 0)
            {
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
                    exitcheck = args.at(i)->get_exit(); 
                    if(exitcheck)
                    { 
                        break;
                    }  
                }
            // gets rid of out-of-bounds error
                args.at(i)->execute();
                if(!exitcheck)
                {
                    exitcheck = args.at(i)->get_exit(); 
                }
             }

            //Deallocates objects and removes pointers
                for(unsigned int i = 0; i < args.size(); i++)
                { 
                    delete args[i]; 
                } 
                args.clear();
            
        }
    } while(!exitcheck); 
    return 0; 
}     
