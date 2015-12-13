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

void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,
     unordered_map<string, list<int> >& intAddressLink, unordered_map<string, list<int>::iterator> & intIterator);
void load(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void insertToLink(string key, int value, unordered_map<string, list<int> >& intAddressLink,
     unordered_map<string, list<int>::iterator> & intIterator);
void input(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void output(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void save(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void plusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void minusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void mult(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void incr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void decr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
bool equalL(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
bool greaterThan(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
bool lessThan(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap);
void moveupA(string key,unordered_map<string, list<int> >& intAddressLink,
        unordered_map<string, list<int>::iterator> & intIterator);
void movedownA(string key,unordered_map<string, list<int> >& intAddressLink,
        unordered_map<string, list<int>::iterator> & intIterator);
void loadA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,
        unordered_map<string, list<int> >& intAddressLink, unordered_map<string, list<int>::iterator> & intIterator);
void outputA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,
        unordered_map<string, list<int> >& intAddressLink, unordered_map<string, list<int>::iterator> & intIterator);
void  plusA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>&
        intRegisMap, unordered_map<string, list<int> >& intAddressLink, unordered_map<string,list<int>::iterator> & intIterator);
void increA(string key,unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator);
void decreA(string key,unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator);

void jump(string jump_name,ifstream& file);


void clearAll(unordered_map<string,int>& intRegisMap);

int main(){

    unordered_map<string,int> intVariaMap; //the key: variable name, value: type value
    //unordered_map<string, char> charVariaMap;

    unordered_map<string,int> intRegisMap;  //the key: register name, value: type value
   // unordered_map<string, char> charRegisMap;


    unordered_map<string, list<int> > intAddressLink; //linkList for memory
    //list<char> charMemoryLink; //linkList for memory

    //hashmap with key as strings and value of list int iterators
    unordered_map<string, list<int>::iterator > intIterators;



    ifstream file;
    file.open("Variable.txt");
    if(file.fail()){
        cout<<"Error opening file\n";
        exit(1);
    }
    loadInstructions(file, intVariaMap, intRegisMap, intAddressLink,  intIterators);
    file.close();

    return EXIT_SUCCESS;
}
void loadInstructions(ifstream& file, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap,  unordered_map<string, list<int> >& intAddressLink,
                      unordered_map<string, list<int>::iterator >& intIterator)
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
                        stringstream rows(row);
                        int rowi;
                        rows >> rowi;
                        intRegisMap.insert({variable, rowi});
                      // intRegisMap.insert({variable, stoi(row)});
                    }
                    else{
                        stringstream rows(row);
                        int rowi;
                        rows >> rowi;
                        intVariaMap.insert({variable, rowi});
                    //  intVariaMap.insert({variable,  stoi(row)});

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
                                   insertToLink(key,0,intAddressLink,intIterator);
                                }
                                else{
                                    stringstream var(row);
                                    int dat;
                                    var >> dat;
                                    if(var != 0)
                                        insertToLink(key,dat,intAddressLink, intIterator);
                                    else{
                                        cout<<"Error inserting to array, cannot convert to int: \"" <<row<<"\""<<endl;
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
                if(equalL(row,intVariaMap, intRegisMap)){
                    //if statement is truewe read second line
                }
                else{
                    //we dont read second line
                    getline(file,row);
                    if(row == "STOP"){
                        exit(0);
                    }
                }
            }

            else if(variable == "JUMP"){

               jump(row, file);
            }

            else if(variable == "LOADA"){
            loadA(row,intVariaMap, intRegisMap, intAddressLink, intIterator);
            }

            else if(variable == "PLUSA"){
                plusA(row,intVariaMap, intRegisMap, intAddressLink,intIterator);
            }
             else if(variable == "INCREA" ){
                 increA(row, intAddressLink, intIterator);
            }
            else if(variable == "DECREA"){
                 decreA(row, intAddressLink, intIterator);
            }

            else if(variable == "MOVEUPA"){
                moveupA(row,intAddressLink, intIterator);

            }

            else if(variable == "MOVEDOWNA"){
                 movedownA(row,intAddressLink, intIterator);
            }

            else if(variable == "OUTPUTA"){
                outputA(row,intVariaMap, intRegisMap, intAddressLink, intIterator);
            }

            else if(variable == "GREATER"){

                if(greaterThan(row,intVariaMap, intRegisMap)){
                    //if statement is truewe read second line
                }
                else{
                    //we dont read second line
                    getline(file,row);
                    if(row == "STOP"){
                        exit(0);
                    }
                }
            }
            else if(variable == "LESS"){
             if(lessThan(row,intVariaMap, intRegisMap)){
                    //if statement is truewe read second line
                }
                else{
                    //we dont read second line
                    getline(file,row);
                    if(row == "STOP"){
                        exit(0);
                    }
                }

            }
            else if(variable == "CLEARALL"){
            //this method clears all registers
                clearAll(intRegisMap);
            }
            else if(variable == "STOP"){
                exit(0);
            }
            else if(variable == "METHOD")
            {
                //
            }

            else {
            cout << "Error: wrong input \"" <<variable<<"\""<<endl;
            }
        }

}

void insertToLink(string key, int value, unordered_map<string, list<int> >& intAddressLink, unordered_map<string, list<int>::iterator> & intIterator){


    list<int> new_list;

    auto it = intAddressLink.find(key);

        if(it != intAddressLink.end()){
                    //found key
                new_list = it->second;
                new_list.push_back(value);
                it->second = new_list;
                auto ptr = intIterator.find(key);

            if(ptr != intIterator.end()){
            //it is the iterator for the linkedlist
            //ptr is the iterator for our iterator hashmap
                    ptr->second = (it->second).begin();
                }

            else{
                cout << "Error:"<<endl;
                exit(1);
            }

             //  for (list<int>::iterator its = new_list.begin(); its!=new_list.end(); ++its)
               // std::cout << 'w' << *its<<endl;
        }

        else{
    //key wasn't found create a new linkedlist
            new_list.push_back(value);
            list<int>::iterator it = new_list.begin();

            //cout << *(new_list.begin());
            intIterator.insert({key, new_list.begin()});
            intAddressLink.insert({key, new_list});
        }

}

void load(string data, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){


           int first_index = data.find(' ');
           string register1 = data.substr(0 , first_index);
           data = data.substr(first_index + 1, data.length() - first_index);

            //if in register
           if((register1 == "R1"|| register1 == "R2"|| register1 == "R3"|| register1 == "R4"|| register1 == "R5"||
              register1 == "R6"|| register1 == "R7"|| register1 == "R8"|| register1 == "R9"|| register1 == "R10"||
              register1 == "R11"|| register1 == "R12"|| register1 == "R13"|| register1 == "R14"||
              register1 == "R15"|| register1 == "R16")){
               // cout << "yes" << endl;


                //loads variable hashmap
                auto it = intVariaMap.find(data);
                int num = 0;
                if(it != intVariaMap.end()) //if found, the second variable carries int
                        num = it -> second;
                else{
                    cout<<"Error: undefined variable: \""<<data<<"\""<<endl;
                    exit(1);
                }

                //saving number to register
                auto its = intRegisMap.find(register1);
                if(its != intRegisMap.end()) //if register is found
                       its -> second = num; //value carries input
                else{
                    intRegisMap.insert({register1,num});
                }
            }

            else {
                cout << "Register: \"" << register1 << "\" does not exits" << endl;
                exit(1);
            }


}
void output(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //output will always have only one variable or register in the STR;

    if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
    //this means we output information from the register
    unordered_map<string,int>::const_iterator got = intRegisMap.find (str);

      if (got == intRegisMap.end() )
      //it didn't find it
        cout << "0"<<endl;
      else
        cout << got->second<<endl;
    }
    else{
    //this means that it saves in the variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);

      if (got == intVariaMap.end() ){
          cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
           exit(0);
      }
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
           cout<<"Error: undefined variable: \""<<register1<<"\""<<endl;
           exit(0);
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

   if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){//if register
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
          if ( got == intVariaMap.end() ){
           cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
          }
          else
             num = got->second;
        //save to register
      }
     if(!((variable.length() == 3 || variable.length() == 2) && variable[0] == 'R')){
      //save to variable
       auto it = intVariaMap.find(variable);
       if(it != intVariaMap.end())
            it->second = num;
        else{
            cout<<"Error: undefined variable: \""<<variable<<"\""<<endl;
            exit(1);
        }
     }
     else{
        cout<<"Error: undefined variable or can't save to register: \""<<variable<<"\""<<endl;
        exit(1);
     }
}

void plusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;




    //second variable will be access to add to first
     if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
        //access information from register
        unordered_map<string,int>::const_iterator got = intRegisMap.find (str);
          if ( got == intRegisMap.end() )//not found
                num = 0;
          else
             num = got->second;

      }
      else{
        //access information from variable
      unordered_map<string,int>::const_iterator got = intVariaMap.find (str);
          if ( got == intVariaMap.end() ){
             cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
          }
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first
        if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
        //save to register
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
        else{
            cout<<"Error: undefined variable: \""<<first_variable<<"\""<<endl;
            exit(1);
        }
    }
}
void minusS(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
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
          if ( got == intVariaMap.end() ){
             cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
          }
          else
             num = got->second;
        //save to register
      }

    //first variable will be access to add to first
        if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
        //save to variable
       auto it = intRegisMap.find(first_variable);
       if(it != intRegisMap.end())
            it->second = it->second - num;
       else{
            intRegisMap.insert({first_variable, (num*(-1))});
       }
      }
      else{
        //save to variable
       auto it = intVariaMap.find(first_variable);
       if(it != intVariaMap.end())
            it->second = it->second - num;
        else{
         cout<<"Error: undefined variable: \""<<first_variable<<"\""<<endl;
            exit(1);
        }
    }
}
void mult(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
    if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
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
          if ( got == intVariaMap.end() ){
           cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
          }
          else
             num = got->second;
        //save to register
      }


    //first variable will be access to add to first

     if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
        //save to register
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
        else{

         cout<<"Error: undefined variable: \""<<first_variable<<"\""<<endl;
            exit(1);
        }
    }
}

void incr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

      //first variable will be access to add to first
        if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
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
        else{

         cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }
    }


}
void decr(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){
    //first variable will be access to add to first
     if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
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
        else{

         cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }
    }

}

bool equalL(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;



    //second variable will be access to add to first
      if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
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
          if ( got == intVariaMap.end() ){
             cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }
          else
             num = got->second;
        //save to register
      }

    //first variable will be access to add to first
     if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
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
        else{
         cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }

       }
    }

bool greaterThan(string str, unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){


        string first_variable;
        int first_index = str.find(' ');
        first_variable = str.substr(0, first_index);
        str = str.substr(first_index+1, str.length() - first_index);

        int num;

        //second variable will be access to add to first
          if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
            //access information from register
                unordered_map<string,int>::const_iterator variable = intRegisMap.find (str);
                if ( variable == intRegisMap.end() )
                    num = 0;
                else
                    num = variable->second;
            }

        else{
        //access information from variable
      unordered_map<string,int>::const_iterator variable = intVariaMap.find (str);
                if ( variable == intVariaMap.end() ){
                    cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
                    exit(1);
                }
                else
                    num = variable->second;
        //save to register
        }

    //first variable will be access to add to first
           if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
        //save to variable
                auto it = intRegisMap.find(first_variable);
                if(it != intRegisMap.end()){
                    return (it->second > num);
                }
                else
                {
                    cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
                    exit(1);
                }

        }

        else{
        //save to variable
            auto it = intVariaMap.find(first_variable);
            if(it != intVariaMap.end()){
                return (it->second > num);
            }
            else{
            cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }
    }
    //first variable will be access to add to first
}
bool lessThan(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap){


        string first_variable;
        int first_index = str.find(' ');
        first_variable = str.substr(0, first_index);
        str = str.substr(first_index+1, str.length() - first_index);
        int num;

    //second variable will be access to add to first
          if(str == "R1"|| str == "R2"|| str == "R3"|| str == "R4"|| str == "R5"||
              str == "R6"|| str == "R7"|| str == "R8"|| str == "R9"|| str == "R10"||
              str == "R11"|| str == "R12"|| str == "R13"|| str == "R14"||
              str == "R15"|| str == "R16"){
        //access information from register
                unordered_map<string,int>::const_iterator variable = intRegisMap.find (str);
                if ( variable == intRegisMap.end() )
                    num = 0;
                else
                    num = variable->second;
            }

        else{
        //access information from variable
                unordered_map<string,int>::const_iterator variable = intVariaMap.find (str);
                if ( variable == intVariaMap.end() ){
                    cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
                    exit(1);
                }
                else
                    num = variable->second;
        //save to register
      }


    //first variable will be access to add to first
        if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
        //save to variable
            auto it = intRegisMap.find(first_variable);
            if(it != intRegisMap.end()){
                return (it->second < num);
            }

      }
     else{
        //save to variable
            auto it = intVariaMap.find(first_variable);
            if(it != intVariaMap.end()){
                return (it->second < num);
            }
             else{
            cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
            exit(1);
        }
    }
    //first variable will be access to add to first

}
void  plusA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>&
    intRegisMap, unordered_map<string, list<int> >& intAddressLink, unordered_map<string,
    list<int>::iterator> & intIterator){

    string first_variable;
    int first_index = str.find(' ');
    int num = 0;
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    auto ptrMemory = intVariaMap.find(first_variable);
    auto ptr = intIterator.find(str);
    if(ptr != intIterator.end()){
        //iterator was found
        num = *(ptr->second);

        if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
               // cout << "yes" << endl;

        auto it = intRegisMap.find(first_variable);

        if(it != intRegisMap.end()){
            it->second += num;
        }
        else{
            intRegisMap.insert({first_variable, num});
        }

        }
        else if(ptrMemory != intVariaMap.end()){
            ptrMemory->second +=num;
        }
        else{
        cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
        exit(1);
        }
    }
    else{
        cout<<"Error: undefined variable: \""<<str<<"\""<<endl;
        exit(1);
    }
}


void movedownA(string key, unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator){

        auto it = intAddressLink.find(key);
        if(it != intAddressLink.end()){

            list<int>::iterator its = (it->second).begin();
            auto ptr = intIterator.find(key);
            // advance(ptr->second,1);
            if(ptr != intIterator.end()){

              //  cout << *(ptr->second) << endl;
                for( list<int>::iterator its = (it->second).begin(); its != (it->second).end(); its++){
                if(its == ptr->second){
                    advance(its,1);
                    ptr->second = its;
                }
              }
            }
            else
                cout << "Error: Accessing the array \""<<key <<"\""<<endl;
    }
    else
        cout << "Error: Item was not defined \""<<key << endl;
}
void moveupA(string key,unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator){


           auto it = intAddressLink.find(key);
            if(it != intAddressLink.end()){

                list<int>::iterator its = (it->second).begin();
                auto ptr = intIterator.find(key);
                // advance(ptr->second,1);
                if(ptr != intIterator.end()){


                    for( list<int>::iterator its = (it->second).begin(); its != (it->second).end(); its++){
                    if(its == ptr->second){
                        ptr->second = prev(its);
                    }
                  }
                }
                else
                    cout << "Error: Accessing the array \""<<key<<"\""<<endl;
        }
        else
            cout << "Error: Item was not defined \""<<key <<"\""<<endl;
}

void loadA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>&
    intRegisMap, unordered_map<string, list<int> >& intAddressLink, unordered_map<string,
    list<int>::iterator> & intIterator){

    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);
    int num;

     auto it = intIterator.find(str);
     //this checks if third variable is a link
     if(it != intIterator.end()){
        num = *(it->second);
    }
    else{
        cout<<"Error: undefined link: \""<<str<<"\""<<endl;
        exit(1);
    }

    //checks if
     if(first_variable == "R1"|| first_variable == "R2"|| first_variable == "R3"|| first_variable == "R4"|| first_variable == "R5"||
              first_variable == "R6"|| first_variable == "R7"|| first_variable == "R8"|| first_variable == "R9"|| first_variable == "R10"||
              first_variable == "R11"|| first_variable == "R12"|| first_variable == "R13"|| first_variable == "R14"||
              first_variable == "R15"|| first_variable == "R16"){
               // cout << "yes" << endl;

        auto it = intRegisMap.find(first_variable);

        if(it != intRegisMap.end()){
            //it was found
            it->second = num;
        }
        else{
            intRegisMap.insert({first_variable, num});
        }

    }
    else{
        cout<<"Error: undefined register: \""<<first_variable<<"\""<<endl;
         exit(1);
        }
}

void outputA(string str,unordered_map<string,int>& intVariaMap, unordered_map<string,int>& intRegisMap, unordered_map<string, list<int> >& intAddressLink, unordered_map<string, list<int>::iterator> & intIterator){
    string first_variable;
    int first_index = str.find(' ');
    first_variable = str.substr(0, first_index);
    str = str.substr(first_index+1, str.length() - first_index);

     auto it = intIterator.find(str);
     //this checks if third variable is a link
     if(it != intIterator.end()){
        cout<<*(it->second) << endl;

    }
    else{
        cout<<"Error: undefined link: \""<<str<<"\""<<endl;
        exit(1);
    }

}

void increA(string key, unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator){

        auto it = intAddressLink.find(key);
        if(it != intAddressLink.end()){

            list<int>::iterator its = (it->second).begin();
            auto ptr = intIterator.find(key);

            if(ptr != intIterator.end()){

                for( list<int>::iterator its = (it->second).begin(); its != (it->second).end(); its++){
                if(its == ptr->second){

                    ptr->second= its;
                    *its = *its + 1;
                }
              }
            }
            else
                cout << "Error: Accessing the array \""<<key <<"\""<<endl;
    }
    else
        cout << "Error: Item was not defined \""<<key <<"\""<<endl;
}
void decreA(string key, unordered_map<string, list<int> >& intAddressLink,
                  unordered_map<string, list<int>::iterator> & intIterator){

        auto it = intAddressLink.find(key);
        if(it != intAddressLink.end()){

            list<int>::iterator its = (it->second).begin();
            auto ptr = intIterator.find(key);

            if(ptr != intIterator.end()){

                for( list<int>::iterator its = (it->second).begin(); its != (it->second).end(); its++){
                if(its == ptr->second){

                    ptr->second= its;
                    *its = *its - 1;
                }
              }
            }
            else
                cout << "Error: Accessing the array \""<<key <<"\""<<endl;
    }
    else
        cout << "Error: Item was not defined \""<<key <<"\""<<endl;
}

void jump(string jump_name,ifstream& file){

        file.close();
        file.open("Variable.txt");

        if(file.fail()){
            cout<<"Error opening file\n";
            exit(1);
        }

        string variable;
        string row = " ";
        string first_word = "";
        int first_index = 0;
        char first_letter;

         while (getline(file,row) || first_word == "STOP"){

             first_index = row.find(' ');
             //first word is method
            first_word = row.substr(0,first_index);

            //row is are method name
            row = row.substr(first_index+1, row.length() - first_index);

            if(row == jump_name && first_word == "METHOD")
            {
                return;
            }

        }
        cout << "METHOD " << jump_name << " not found. "<< endl;
}
void clearAll(unordered_map<string,int>& intRegisMap){

    //clears all registers 1-16;
    for(int i = 1; i <= 16; i++){
        string str;
        ostringstream convert;
        convert << i;
        str = convert.str();
        str = "R"+str;
        auto it = intRegisMap.find(str);
        if(it != intRegisMap.end()){
            it->second = 0;
        }
        else{
            intRegisMap.insert({str, 0});
        }
    }

}
