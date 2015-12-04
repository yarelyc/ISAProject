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
