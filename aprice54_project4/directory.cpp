
#include "directory.h"

/*
 * The main building block for the file system
 * the class defines a directory as an object that holds files and other directories in vectors
 * many methods for getting and setting information within each directory
 *
*/

	directory::directory(string n, string p){
                dirNum = 0;
                fileNum = 0;
                pNum = 0;
                tNum = 0;
                name = n;
				printDepth = 0;
                parentName = p;
        }
        void directory::addDir(directory direct){
                directories.push_back(direct);
                dirNum++;
                fileNum++;
        }
        void directory::addFile(tFile addFile){
                files.push_back(addFile);
                fileNum++;
                tNum++;
        }
        void directory::addProgram(program addProgram){
                programs.push_back(addProgram);
                fileNum++;
                pNum++;
        }

		string directory::getParent(){
                return parentName;
        }
        string directory::getName(){
                return name;
        }
        int directory::getNumFiles(){
                return fileNum;
        }
        directory directory::getDir(string name){
                for(int i = 0; i < directories.size(); i++){
                        if(directories[i].name == name){
                                return directories[i];

                        }
                }
		}
		tFile directory::getFile(string name){
                for(int i = 0; i < directories.size(); i++){
                        if(files[i].name == name){
                                return files[i];

                        }
                }
        }
		directory directory::findDir(string name, directory cDir){
		for(int j = 0; j < dirNum; j++){
                        if(directories[j].name == name)
                                 return directories[j];
						if(directories[j].dirNum > 0)
							directories[j].findDir(name,cDir);
                }
			return cDir;
	
		}
        void directory::listContents(){
                for(int j = 0; j < dirNum; j++)
                        cout << plainName(directories[j].name) << endl;
                for(int j = 0; j < tNum; j++)
                        cout << plainName(files[j].name) << endl;
                for(int j = 0; j < pNum; j++)
                        cout << plainName(programs[j].name) << endl;
        }
        bool directory::contains(string name){
                for(int j = 0; j < dirNum; j++){
                        if(directories[j].name == name)
                                return true;
				}
				for(int i = 0; i < tNum; i++){
                        if(files[i].name == name)
                                return true;
				}
				for(int k = 0; k < pNum; k++){
                        if(programs[k].name == name)
                                return true;
				}
			return false;
        }
		void directory::findAndReplace(program p){
					for(int k = 0; k < pNum; k++){
						
						if(programs[k].name == p.name)
							programs[k] = p;
			}
		}

        void directory::toString(){
				printDepth++;
                cout << "->"  << plainName(name) <<" contains " << fileNum << " Files" << endl;
                toString2();
                for(int j = 0; j < dirNum; j++){

                        cout << plainName(directories[j].name) << endl;
						//cout << "\t"*printDepth ;
                        directories[j].toString();
                }
                cout << "<-End" << plainName(name) << endl;
        }
        void directory::toString2(){
                for(int j = 0; j < tNum; j++)
                        files[j].toString();
                for(int j = 0; j < pNum; j++)
                        programs[j].toString();
        }
        string directory::getFileInfo(){
                stringstream info;
                info << name << '\0' << fileNum << '\0';
                info << getInfo2();
                for(int j = 0; j < dirNum; j++){
                        info << directories[j].getFileInfo();
                }
                info << "End" << name.substr(0,8) << '\0';
                return info.str();
        }
        string directory::getInfo2(){
                stringstream info;
                for(int j = 0; j < tNum; j++)
                        info <<  files[j].getInfo();
                for(int j = 0; j < pNum; j++)
                        info << programs[j].getInfo();

                return info.str();
        }

		string directory::plainName(string fileName){
        	string name;
        	string ext;
        	char delim = '\0';
        	char delim2 = '.';
        	name = fileName.substr(0,fileName.find(delim));
        	ext = fileName.substr(fileName.find(delim2),2);
        return name + ext;
}

						
				
