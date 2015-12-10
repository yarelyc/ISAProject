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
#include <string>
using namespace std;

void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void output(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void save(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void plusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void minusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void mult(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void incr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void decr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
bool equalL(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);


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

            first_index = row.find(' ');
            first_letter = row[0];
            row = row.substr(first_index+1, row.length() - first_index);

            first_index = row.find(' ');
            variable = row.substr(0, first_index);
            row = row.substr(first_index+1, row.length() - first_index);
            switch(first_letter){
                case 'i':
                    //int type variable declaration
                   if(variable.length() == 2 && variable[0] == 'R'){
                        //insert into register map
                        intRegisMap.insert({variable, stoi(row)});
                    }
                    else{
                      intVariaMap.insert({variable,  stoi(row)});
                    }
                    break;
                case 'c':
                    //char type variable declaration
                    break;
                case 'l':
                    //link list type variable declaratio
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

            }

            else if(variable == "INPUT"){

            }

            else if(variable == "OUTPUT"){
                output(row,intVariaMap, intRegisMap);
            }

            else if(variable == "SAVE"){
                save(row, intVariaMap, intRegisMap);
            }

            else if(variable == "PLUS"){
                    plusS(row,intVariaMap, intRegisMap);
            }

            else if(variable == "MINUS"){
                 minusS(row,intVariaMap, intRegisMap);
            }

            else if(variable == "MULT"){
                 mult(row,intVariaMap, intRegisMap);
            }

            else if(variable == "INCRE"){
                 incr(row,intVariaMap, intRegisMap);
            }

            else if(variable == "DECRE"){
                 decr(row,intVariaMap, intRegisMap);
            }

            else if(variable == "EQUAL"){
                equalL(row,intVariaMap, intRegisMap);
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




          }

}

void output(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //output will always have only one variable or register in the STR;

    if((str.length() == 3 || str.length() == 2) && str[0] == 'R'){
    //this means we output information from the register
    unordered_map<string,int>::const_iterator got = intRegisMap.find (str);

      if ( got == intRegisMap.end() )
        cout << "0"<<endl;
      else
        cout << got->second<<endl;
    }
    else{
    //this means that it saves in the variable
     unordered_map<string,int>::const_iterator got = intVariaMap.find (str);

      if ( got == intVariaMap.end() )
        cout << "0"<<endl;
      else
        cout << got->second<<endl;

    }


}
void save(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //saving to a variable from variable or register

    string variable;
    int first_index = str.find(' ');
    variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;

    if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() )
                num = 0;
          else
             num = got->second;
        //save to register
      }
     if(!((variable.length() == 3 || variable.length() == 2) && variable[0] == 'R')){
      //save to variable
       auto it = intVariaMap.find(variable);
       if(it != intVariaMap.end())
            it->second = num;
     }
     else{
        cout<<"Wrong input! Can only save to variable"<<endl;
     }



}

void plusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() )
                num = 0;
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first
      if(((first_variable.length() == 3 || first_variable.length() == 2) && first_variable[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(first_variable);
       if(it != intRegisMap.end())
            it->second += num;
       else{
            intRegisMap.insert({first_variable, num});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(first_variable);
       if(it != intVariaMap.end())
            it->second += num;
    }
}
void minusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() )
                num = 0;
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first
      if(((first_variable.length() == 3 || first_variable.length() == 2) && first_variable[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(first_variable);
       if(it != intRegisMap.end())
            it->second = it->second - num;
       else{
            intRegisMap.insert({first_variable, 0 - num});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(first_variable);
       if(it != intVariaMap.end())
            it->second = it->second - num;
    }
}
void mult(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() )
                num = 0;
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first
      if(((first_variable.length() == 3 || first_variable.length() == 2) && first_variable[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(first_variable);
       if(it != intRegisMap.end())
            it->second *= num;
       else{
            intRegisMap.insert({first_variable, 0});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(first_variable);
       if(it != intVariaMap.end())
            it->second *= num;
    }
}

void incr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

      //first variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(str);
       if(it != intRegisMap.end())
            it->second++;
       else{
            intRegisMap.insert({str, 0});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(str);
       if(it != intVariaMap.end())
            it->second++;
    }


}
void decr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //first variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(str);
       if(it != intRegisMap.end())
            it->second--;
       else{
            intRegisMap.insert({str, 0});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(str);
       if(it != intVariaMap.end())
            it->second--;
    }

}

bool equalL(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

 string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(((str.length() == 3 || str.length() == 2) && str[0] == 'R')){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() )
                num = 0;
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first
      if(((first_variable.length() == 3 || first_variable.length() == 2) && first_variable[0] == 'R')){
        //save to variable
       auto it = intRegisMap.find(first_variable);

       if(it != intRegisMap.end()){
            return (it->second == num);
       }

      }
      else{
        //save to variable
       auto it = intVariaMap.find(first_variable);
       if(it != intVariaMap.end()){
             return (it->second == num);
       }
    }
}

