
#include "program.h"

/*
 * class to define program file objects
 * includes a few methods, such as toString and getName
*/

	program::program(string n, string pName, int c, int m,int p1,int p2,int cc,bool atq){
                name = n;
                mem = m;
                cpu = c;
				pair1 = p1;
				pair2 = p2;
				parentName = pName;
				cCpu = cc;
				addToQueue = atq;
				onDisk = false;
				
        }
	program::program(string n, string pName, int c, int m,int p1,int p2,int cc,bool atq,bool OD){
                name = n;
                mem = m;
                cpu = c;
				pair1 = p1;
				pair2 = p2;
				parentName = pName;
				cCpu = cc;
				addToQueue = atq;
				onDisk = OD;
        }
         string program::getName(){
                return name;
        }
        void program::toString(){
                cout << "\t" << plainName(name) << "\n\t[cpu: " << cpu << "\n\tmemory: " << mem << "]" << endl;
        }
        string program::getInfo(){
                stringstream info;
                info << name << cpu << '\0' << mem << '\0' << pair1 
					<< '\0' << pair2 << '\0' << cCpu << '\0' << addToQueue << '\0'<< onDisk << '\0';
                return info.str();
        }
		string program::plainName(string fileName){
        	string name;
        	string ext;
        	char delim = '\0';
        	char delim2 = '.';
       	 	name = fileName.substr(0,fileName.find(delim));
        	ext = fileName.substr(fileName.find(delim2),2);
        return name + ext;
		}

