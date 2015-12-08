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

#include <iostream>
#include <unordered_map>
#include <list>
#include <cstdlib>
#include <fstream>

using namespace std;

void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
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
                        intRegisMap.insert({variable,  stoi(row)});
                    }
                    else{
                       intVariaMap.insert({variable,  stoi(row)});
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

            cout<<row<<endl;
          }




}
