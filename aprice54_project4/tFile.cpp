#include "tFile.h"

/*
 * class to define text file objects
 * includes a few methods, such as toString and getName
*/
tFile::tFile(string n, string pName, string t, int s){
                name = n;
                text = t;
                size = s;
				parentName = pName;
        }
        string tFile::getName(){
                return name;
        }
        void tFile::toString(){
                cout << "\t" << plainName(name) << "\n\t[" << text << "]" <<endl;
        }
        string tFile::getInfo(){
                stringstream info;
                string infos;
                info << name << size << text << '\0';
                return info.str();
        }
		string tFile::plainName(string fileName){
        	string name;
        	string ext;
        	char delim = '\0';
        	char delim2 = '.';
        	name = fileName.substr(0,fileName.find(delim));
        	ext = fileName.substr(fileName.find(delim2),2);
        return name + ext;
		}


