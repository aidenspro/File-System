#ifndef directory_h
#define directory_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <unistd.h>
#include "job.h"
#include "tFile.h"
#include "program.h"

using namespace std;
/*
 * The main building block for the file system
 * the class defines a directory as an object that holds files and other directories in vectors
 * many methods for getting and setting information within each directory
 *
*/
class directory{

	public:
        string name;
        string parentName;
        int dirNum;
        int fileNum;
        int pNum;
        int tNum;
		int printDepth;
        vector<directory> directories;
        vector<tFile> files;
        vector<program> programs;

        directory(string n, string p);
		void addDir(directory direct);
		void addFile(tFile addFile);
		void addProgram(program addProgram);
		
		string getParent();
		string getName();
		int getNumFiles();

		directory getDir(string name);
		tFile getFile(string name);
		directory findDir(string name, directory cDir);
		
		void listContents();
                
        bool contains(string name);
		void findAndReplace(program p);


        void toString();

        void toString2();

        string getFileInfo();

        string getInfo2();

		string plainName(string name);
};

#endif
