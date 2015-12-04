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
#include <cstdlib>
#include <fstream>

using namespace std;
void loadInstructions(ifstream& file);
int main(){
    unordered_map<string,int> intVariaMap; //the key: variable name, value: type value
    //unordered_map<string, char> charVariaMap;

    unordered_map<string,int> intRegisMap;  //the key: register name, value: type value
   // unordered_map<string, char> charRegisMap;

    list<int> intMemoryLink; //linkList for memory
    //list<char> charMemoryLink; //linkList for memory


    ifstream file;
    file.open( "file.txt");
    loadInstructions(file);

    return EXIT_SUCCESS;
}
void loadInstructions(ifstream& file)
{

        string row;
         while ( !file.eof() && getline(file, row) != "STOP" ){

             getline(file, row );
             cout << row << endl;

         }

        file.close();

}
