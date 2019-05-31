#ifndef tFile_h
#define tFile_h
/*
 * Tyler Price
 * Project 4
 * ITEC 371
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;

/*
 * class to define text file objects
 * includes a few methods, such as toString and getName
*/
class tFile{
public:
        string parentName;
        string name;
        string text;
        int size;
        tFile(string n, string pName, string t, int s);

        string getName();
		void toString();
		string getInfo();
		string plainName(string name);
};

#endif
