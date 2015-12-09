// ********************************************************
// Name: ISA.cpp
//
// Summary: This file
//
// Author: Yarely Chino & Araceli
// Created: 12/ 01/2015
// Modifications:
//
// *******************************************************
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <list>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void load(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);

int main(){

    unordered_map<string,int> intVariaMap; //the key: variable name, value: type value
    //unordered_map<string, char> charVariaMap;

    unordered_map<string,int> intRegisMap;  //the key: register name, value: type value
   // unordered_map<string, char> charRegisMap;

    list<int> intMemoryLink; //linkList for memory
    //list<char> charMemoryLink; //linkList for memory



    ifstream file;
    file.open("Variable.txt");
    if(file.fail()){
        cout<<"Error opening file\n";
        exit(1);
    }
    loadInstructions(file, intVariaMap, intRegisMap);
    file.close();

//finds your variables and values
     unordered_map<string,int>::const_iterator got = intVariaMap.find ("num");

      if ( got == intVariaMap.end() )
        cout << "not found";
      else
        cout << got->first << " is " << got->second;

    return EXIT_SUCCESS;
}
void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap)
{
        int first_index;
        string variable;
        char first_letter;
        string row = " ";

         while (getline(file,row) && row != "START")
         {
            cout<<"end:"<<row<<endl;
            first_index = row.find(' ');
            first_letter = row[0];
            row = row.substr(first_index+1, row.length() - first_index);

            first_index = row.find(' ');
            variable = row.substr(0, first_index);
            row = row.substr(first_index+1, row.length() - first_index);
            switch(first_letter){
                case 'i':
                    //int type variable declaration
                    cout<<"int"<<endl;
                    if(variable.length() == 2 && variable[0] == 'R'){
                        //insert into register map
                      // intRegisMap.insert({variable, stoi(row)});
                    }
                    else{
                    //  intVariaMap.insert({variable,  stoi(row)});
                    }
                    break;
                case 'c':
                    //char type variable declaration
                    cout<<"char"<<endl;
                    break;
                case 'l':
                    //link list type variable declaration
                    cout<<"link"<<endl;
                    break;
                 default :
                        cout<<endl;
            }
            // cout << row << endl;

         }

          while (getline(file,row)){


            first_index = row.find(' ');
            variable = row.substr(0, first_index);
            row = row.substr(first_index+1, row.length() - first_index);

            if(variable == "LOAD"){


                load(row, intVariaMap, intRegisMap);
            }

            else if(variable == "INPUT"){

            }

            else if(variable == "OUTPUT"){

            }

            else if(variable == "SAVE"){

            }

            else if(variable == "PLUS"){

            }

            else if(variable == "MINUS"){

            }

            else if(variable == "MULT"){

            }

            else if(variable == "INCRE"){

            }

            else if(variable == "DECRE"){

            }

            else if(variable == "EQUAL"){

            }

            else if(variable == "JUMP"){

            }

            else if(variable == "EQUAL"){

            }

            else if(variable == "IFTHEN"){

            }

            else if(variable == "LOADA"){

            }

            else if(variable == "PLUSA"){

            }

            else if(variable == "INCREA"){

            }

            else if(variable == "DECREA"){

            }

            else if(variable == "OUTPUTA"){

            }

            else {cout << "Wrong input" << endl;}


          }

}
void load(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){


           int first_index = data.find(' ');
           string register1 = data.substr(0 , first_index);
           data = data.substr(first_index + 1, data.length() - first_index);



           if(register1 == "R1"|| register1 == "R2"|| register1 == "R3"|| register1 == "R4"|| register1 == "R5"||
              register1 == "R6"|| register1 == "R7"|| register1 == "R8"|| register1 == "R9"|| register1 == "R10"||
              register1 == "R11"|| register1 == "R12"|| register1 == "R13"|| register1 == "R14"||
              register1 == "R15"|| register1 == "R16"){

               // cout << "yes" << endl;
                 stringstream var(data);
                 int dat;
                 var >> dat;

                //if((intRegisMap.find(register1, dat)== 0)
                auto it = intVariaMap.find(data);
                int num = 0;
                if(it != intVariaMap.end())
                        num = it -> second;

                auto its = intRegisMap.find(register1);
                int num1 = 0;
                if(its != intRegisMap.end())
                        num1 = its -> second;
                else
                    intRegisMap.insert({register1, num1});

              }

            else {
                cout << "Register: " << register1 << " does not exits" << endl;
            }


            cout << data << endl;
            cout << register1 << endl;

}
