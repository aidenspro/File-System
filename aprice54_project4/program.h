#ifndef program_h
#define program_h
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;
/*
 * class to define program file objects
 * includes a few methods, such as toString and getName
*/
class program{
        public:
        string name;
		string parentName;
        int mem;
        int cpu;
		int pair1;
		int pair2;
		int cCpu;
		bool addToQueue;
		bool onDisk;

		program(string n, string pName, int c, int m,int p1,int p2,int cc,bool atq,bool OD);
		program(string n, string pName, int c, int m,int p1,int p2,int cc,bool atq);
		string getName();
		void toString();
		string getInfo();
		string plainName(string name);
};
#endif
