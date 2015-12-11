// ********************************************************
// Name: ISA.cpp
//
// Summary: This file
//
// Author: Yarely Chino & Araceli
// Created: 12/ 01/2015
// Modifications:
// *******************************************************
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <list>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,  unordered_map<string, list<int> >& intAddressLink);
void load(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void insertToLink(string key, int value, unordered_map<string, list<int> >& intAddressLink);
void input(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
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


    unordered_map<string, list<int> > intAddressLink; //linkList for memory
    //list<char> charMemoryLink; //linkList for memory



    ifstream file;
    file.open("Variable.txt");
    if(file.fail()){
        cout<<"Error opening file\n";
        exit(1);
    }
    loadInstructions(file, intVariaMap, intRegisMap, intAddressLink);
    file.close();


    return EXIT_SUCCESS;
}
void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,  unordered_map<string, list<int> >& intAddressLink)
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
                    //hashmap of lists
                    {
                    bool isLink = true;
                    string key = row;
                    while(isLink){
                            getline(file,row);
                            if(row.find("end") != string::npos){
                                isLink = false;
                            }
                            else{
                            first_index = row.find("int ");//"    int 25"
                            row = row.substr(first_index+4,row.length()-(first_index + 4));
                            if(row.length() == 1 && row[0] == '0'){
                                //means its a zero
                               insertToLink(key,0,intAddressLink);
                            }
                            else{
                                stringstream var(row);
                                int dat;
                                var >> dat;
                                if(var != 0)
                                    insertToLink(key,dat,intAddressLink);
                                else{
                                    cout<<"Error inserting to array, cannot convert to int: " <<row<<endl;
                                    exit(1);
                                }
                            }
                            }

                    }
                    }
                    break;
                 default:
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
                input(row, intVariaMap, intRegisMap);
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
            else {cout << "Wrong input" << endl;}
          }
}

void insertToLink(string key, int value, unordered_map<string, list<int> >& intAddressLink){


    list<int> new_list;

    auto it = intAddressLink.find(key);
    if(it != intAddressLink.end()){
    //found key
     new_list = it->second;
     new_list.push_back(value);
     it->second = new_list;
     /*
       for (list<int>::iterator its = new_list.begin(); its!=new_list.end(); ++its)
        std::cout << ' ' << *its<<endl;*/
    }
    else{
    //key wasn't found
    new_list.push_front(value);
    intAddressLink.insert({key, new_list});

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

                //loads variable hashmap
                auto it = intVariaMap.find(data);
                int num = 0;
                if(it != intVariaMap.end()){
                    num = it -> second;
                }
                auto its = intRegisMap.find(register1);
                if(its != intRegisMap.end())
                        its -> second = num;
                else
                    intRegisMap.insert({register1, num});

              }

            else {
                cout << "Register: " << register1 << " does not exits" << endl;

            }

}
void output(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //output will always have only one variable or register in the STR;

    if((str.length() == 3 || str.length() == 2) && str[0] == 'R'){
    //this means we output information from the register
    unordered_map<string,int>::const_iterator got = intRegisMap.find (str);

      if ( got == intRegisMap.end() )
      //it didn't find it
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

void input(string register1, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    string num;
    cin>>num;


    if(register1 == "R1"|| register1 == "R2"|| register1 == "R3"|| register1 == "R4"|| register1 == "R5"||
              register1 == "R6"|| register1 == "R7"|| register1 == "R8"|| register1 == "R9"|| register1 == "R10"||
              register1 == "R11"|| register1 == "R12"|| register1 == "R13"|| register1 == "R14"||
              register1 == "R15"|| register1 == "R16"){
               // cout << "yes" << endl;
         stringstream var(num);
        int dat;
        var >> dat;
        auto it = intRegisMap.find(register1);

        if(it != intRegisMap.end()){
            //it was found
            it->second = dat;
        }
        else{
             intRegisMap.insert({register1,dat});
        }

    }

    else {
     //Input to variable
     stringstream var(num);
        int dat;
        var >> dat;
        auto it = intVariaMap.find(register1);

        if(it != intVariaMap.end()){
            //it was found
            it->second = dat;
        }
        else{
             intVariaMap.insert({register1,dat});
        }


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
        //cout<<"Wrong input! Can only save to variable"<<endl;
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
