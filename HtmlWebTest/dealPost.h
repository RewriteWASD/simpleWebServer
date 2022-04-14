//
// Created by yangfu on 2022/4/14.
//

#ifndef HTMLWEBTEST_DEALPOST_H
#define HTMLWEBTEST_DEALPOST_H
#include <string>
#include<iostream>
using namespace std;
string* dealPost(char * buff){
    string str(buff);
    string *s=new string[2];
    int begin=str.find("username");
    int end=str.find("password");
    string name=str.substr(begin+9,end-begin-10);
    string passworld=str.substr(end+9);
    s[0]=name;
    s[1]=passworld;
    return s;
    //cout <<begin<<endl;
   // cout<<end<<endl;
    //cout << name<<endl;
    //cout << passworld<<endl;
}


#endif //HTMLWEBTEST_DEALPOST_H
