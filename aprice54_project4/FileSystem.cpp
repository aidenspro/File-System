/*
 * Tyler Price
 * Project 2
 * ITEC 371
*/

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
#include "directory.h"
using namespace std;
//----------------------------------------------Methods--------------------------//
void createFile(string fileName);
void createDir(string dirName);
string formatFileName(string name);
void readFile(string flag, char **argv);
void startRUSH(char **argv);
void pieceTogether();
void addToCurrent();
void createDirFromFile(string dirName,string parent);
void createPFile(string fileName,int mem, int cpu,int p1, int p2, int cCpu, bool addToQueue, bool onDisk);
void createRFile(string fileName,int mem, int cpu,int p1, int p2, int cCpu, bool addToQueue, bool onDisk);
void createTFile(string fileName,int size,string text);
void changeDirectory();
void helpRUSH();
void stepSimulation(int step);
void printQueue(int burst);
void runSimulation(int burst);
void updateJobs();
void step1(int burst);
string plainName(string fileName);
//----------------------------------------------Classes----------------------------//
/* 
 *All Classes have been moves to serperate files 
 * */
job getJob(string name);
bool checkOrder(vector<job> test);
vector<job> allJobs;
vector<job> jobsToRun;
job MRU(job cJob);
int cTime = 0;
int tMemory = 10;
int cMemory = 0;
int cFiles = 0;
int depthLevel = 0;
int burst = 2;
/*
 * used to remove the null terminators from file names to make the output of the system more readable
 * takes in a string of the fileName
*/
string plainName(string fileName){
        string name;
        string ext;
        char delim = '\0';
        char delim2 = '.';
        name = fileName.substr(0,fileName.find(delim));
        ext = fileName.substr(fileName.find(delim2),2);
        return name + ext;
}

//----------------------------------------------public Vectors------------------------------//
/*
 * the allDirs vector is very important to keeping track of directories that are currently in use
 * and making sure they do not become lost instance data
 *
 * Also the "current" directory keeps track of what directory is currently being examined at all times.
*/
directory findParent(directory child);
vector<tFile> allTFiles;
vector<program> allPFiles;
vector<directory> allDirs;
string rootName = "root.d";
directory root(formatFileName(rootName),"none");
directory current = root;
vector<int> cFile;
int cNum = -1;

//----------------------------------------------Written Methods------------------------------//
/*
 * this method basically compiles the list of directories in the allDirs vector and like a staircase puts them inside of eachother
 * in the right order, using the parent names of the directories as a destination to be put into
*/
void pieceTogether(){
                for(int i = allDirs.size()-1; i > -1 ; i--){
					for(int t = 0; t < allTFiles.size() ; t++){
												if(allTFiles[t].parentName == allDirs[i].name && !allDirs[i].contains(allTFiles[t].name)){
													allDirs[i].addFile(allTFiles[t]);
													if(allDirs[i].name == current.name)
														current = allDirs[i];
												}
					}
					for(int p = 0; p < allPFiles.size() ; p++){
										//cout << allPFiles[p].name << endl;
										if(allPFiles[p].parentName == allDirs[i].name && !allDirs[i].contains(allPFiles[p].name)){
													allDirs[i].addProgram(allPFiles[p]);
													
													if(allDirs[i].name == current.name)
														current = allDirs[i];												
												}else if (allPFiles[p].parentName == allDirs[i].name && allDirs[i].contains(allPFiles[p].name)){
														allDirs[i].findAndReplace(allPFiles[p]);
												}
					}
						for(int j = allDirs.size()-1; j > -1 ; j--){
                                
                                if(allDirs[i].getParent() == allDirs[j].getName()){
                                        if(!allDirs[j].contains(allDirs[i].getName()) && allDirs[j].getName() != allDirs[i].getName()){
                                        	allDirs[j].addDir(allDirs[i]);
											if(allDirs[j].name == current.name)
												current = allDirs[j];

											//cout << " added " << allDirs[i].getName() << " as a child to " << allDirs[j].getName() << endl;
                                        	//allDirs.erase(allDirs.begin() + i);
                                        }
                                }
                        }
                }
        }

/*
 * Searches the allDirs Vector to set the Current directory to the parent directory
 * takes in a directory
*/
directory findParent(directory child){
                        for(int j = allDirs.size()-1; j > -1 ; j--){
                                if(child.getParent() == allDirs[j].getName()){
                                        //cout << "leaving: "  <<  allDirs[j].getParent() << endl;
                                        return allDirs[j];
                                        break;
                                }
                }
}


/*
 * starts the system
 * and starts taking inputs based upon the flag entered
*/
void startRUIN(char **argv){
current = root;
allDirs.clear();
allDirs.push_back(current);
depthLevel = 0;
readFile("./RUSH",argv);
}
void helpRUSH(){
cout << "\t\t-----------------RUSH Help Menu-----------------" << endl;
cout << "Commands that can be used in RUSH:" << endl;
cout << " mkdir <Filename> : attemps to create a directory with the specified filename in the current diectory, then change to it" << endl;
cout << " addProgram <Filename> : attempts add a program given user information" << endl;
cout << " createTextfile <Filename> : attempts to create a new text file given user information." << endl;
cout << " cd <..> or <Filename> : attempts to change the current directory to the specified directory" << endl;
cout << " pwd <..> : attempts to change the current directory to the specified directory" << endl;

cout << " Quit : exits RUFS\n" << endl;
}




/*
 * Possibly the longest method in the program, it reads input from a file that has been written to using the file creator.
 * goes through the file and creates a directory structure of nested vectors based on the file contents
 *
 * takes in a flag (-r,RUSH) and a string for the file name
*/
void readFile(string flag, char** argv){
        int parNum = 0;
        string cParent;
        string line;
        string line2;
		string file = argv[1];
        vector<string> parents;
        vector<string> strings;
        string cDir;
        cout << "Opening: <" << file << "> ";
       // allDirs.clear();
        fstream readFile;
        readFile.open(file.c_str(),ios_base::in);
        if(readFile.is_open()){
                while(readFile.good()){
                        getline(readFile,line,'\0');
                        if(line.length() > 0){
                        strings.push_back(line);

                        }
                }
                cout << endl;
        }else{
                cout<< "that file does not exist" << endl;
                if(flag == "./RUSH")
                        cout << "Creating new File to open";
        }

                for(int i = 0; i < strings.size(); i++){
        if(strings[i] == ".d"){
                istringstream s3(strings[i+1]);
                s3 >> cFiles;
                cDir = strings[i-1] + strings[i];
                parents.push_back(formatFileName(cDir));
             
				}
        }
				
				for(int i = 0; i < strings.size(); i++){

        if(strings[i] == ".d"){
                istringstream s3(strings[i+1]);
                s3 >> cFiles;
                cDir = strings[i-1] + strings[i];
                createDirFromFile(formatFileName(cDir),parents[parNum]);
                if(formatFileName(cDir) != formatFileName("root.d")){
                        parNum++;
                }

        }
		
        if(strings[i] == ".t"){
                int size;
                istringstream s1(strings[i+1].substr(0,1));
                s1 >> size;	
                createTFile(formatFileName(strings[i-1] + strings[i]),size,strings[i+1].substr(1));	
        }

        if(strings[i] == ".p"){
                istringstream s2(strings[i+1]);
                istringstream s3(strings[i+2]);
				istringstream s4(strings[i+3]);
                istringstream s5(strings[i+4]);
				istringstream s6(strings[i+5]);
				istringstream s7(strings[i+6]);
				istringstream s8(strings[i+7]);	
				int cpu;
                int mem;
				int pair1;
				int pair2;
				int cCpu;
				bool atq;
				bool onDisk;
                s2 >> cpu;
                s3 >> mem;
				s4 >> pair1;
				s5 >> pair2;
				s6 >> cCpu;
				s7 >> atq;
				s8 >> onDisk;
			
				createPFile(formatFileName(strings[i-1]+strings[i]),cpu,mem,pair1,pair2,cCpu,atq,onDisk);
				

        }
        if(strings[i].substr(0,3) == "End"){
                parNum--;
        
		}else if(strings[i] == "cMem"){
                istringstream s9(strings[i+1]);	
				s9 >> cMemory;
		}else if(strings[i] == "tMem"){
                istringstream s9(strings[i+1]);	
				s9 >> tMemory;
		}else if(strings[i] == "burst"){
                istringstream s9(strings[i+1]);	
				s9 >> burst;
		}
		
        }
		        pieceTogether();
        readFile.close();
        if(flag == "-r"){
                cout << " In FileReader" <<endl;
                allDirs[0].toString();

        }else{
				current = allDirs[0];
                startRUSH(argv);
        }
}


/*
 * adds the all the necessary null terminators for the name formatting 
 *
 * takes in a string of the unformatted name
 * returns the formatted string
*/
string formatFileName(string name){
        string formatted;
        string fileName;
        string extension;
        int period = name.find(".");
        extension = name.substr(period,2);
        fileName = name.substr(0,period);
        if(fileName.length() == 8 )

                fileName += '\0';
        for(int i = fileName.length(); i < 8; i++){
                fileName += '\0';
        }

        if(extension != (".d") && extension != (".p") && extension != (".t")){
                cout << extension << " is an incorrect extension" << endl;
                return "wrong";
        }

        extension += '\0';
        formatted = fileName + extension;
        return formatted;
}


//---------------------------------------------------------------FILE CREATION METHODS----------------------------------------------//

/*
 * creates a directory object and adds it to the main allDirs vector
 * prints that it was created to std output
*/
void createDir(string dirName){
        cout << "created -" << plainName(dirName) << "- in directory " << plainName(current.getName()) << endl; 
		allDirs.push_back((directory(dirName,current.getName())));
        //cout << " added " << plainName(current.getName()) <<  " with parent " << plainName(current.getParent()) << endl;
        cout << "currently in " << plainName(current.getName()) << endl;
        depthLevel++;
				
}
/*
 * this method is only used to update the current file once a textfile or program has been added to it
*/
void addToCurrent(){
        for(int i = allDirs.size()-1; i > -1 ; i--){
                if(allDirs[i].getName() == current.getName())
                        allDirs[i] = current;
        }
}
/*
 * creates either a textfile or program based on the extension and input entered
 * prompts user for all the information then adds the fileObject to a directory object
 *
 * takes in a stirng of the filename
*/
void createFile(string fileName){
        int period = fileName.find(".");
        string extension = "";
        extension = fileName.substr(period,2);
        if(extension == ".t"){
        string substance;
        int size = 0;
        cout << "enter File text" << endl;
        cin.ignore();
        getline(cin, substance);
        cout << "created -" << plainName(fileName) << "- in directory " << plainName(current.getName()) << endl;
        cout << "currently in " << plainName(current.getName()) << endl;
        substance += '\0';
		
		allTFiles.push_back(tFile(fileName,current.name,substance,size));
                
		
        }
        else if(extension == ".p"){
        int mem = 0;
        int cpu = 0;
        cout << "enter CPU requirements :> " ;
        cin >> cpu;
        cout << "enter Memory requirements :> " ;
        cin >> mem;
        cout << "created -" << plainName(fileName) << "- in directory " << current.getName() << endl;
        cout << "currently in " << plainName(current.getName()) << endl;
        
		allPFiles.push_back(program(fileName,current.name,cpu,mem,0,0,0,0));
        }
}

/*
 * The counterpart to the createDir method, this method does the same but with input read-in from a binary file
 *
 * takes in a string for the directory name, and a string for that directories parents name
*/
void createDirFromFile(string dirName,string parent){
        if(dirName == formatFileName("root.d"))
        current = (directory(dirName,"none"));
        else
                current = (directory(dirName,parent));

        allDirs.push_back(current);
        depthLevel++;

}
/*
 * uses information read in from the binary file to make a text File and add it to the correct directory object
 *
 * takes in a string of the filename, an integer of the file size, and a string of the text in the file
*/
void createTFile(string fileName,int size, string substance){

        allTFiles.push_back(tFile(fileName,current.name,substance,size));
		
}
/*
 * uses information read in from the binary file to make a program File and add it to the correct directory object
*/
void createPFile(string fileName,int cpu, int mem,int p1,int p2,int cCpu,bool addToQueue,bool onDisk){
	
        allPFiles.push_back(program(fileName,current.name,cpu,mem,p1,p2,cCpu,addToQueue,onDisk));
		job cJob = (job(plainName(fileName),cpu,mem,p1,p2));		
		allJobs.push_back(cJob);	
		//cout << "added " << cJob.name << endl;
			if(addToQueue == true){
			cJob.timeLeft = cCpu;

			if(onDisk == true){
			cJob.onDisk = onDisk;
			cJob.virtualm = 2;
			}

			jobsToRun.push_back(cJob);

		}
}
void createRFile(string fileName,int cpu, int mem,int p1, int p2, int cCpu,bool addToQueue,bool onDisk){
        if(current.getName() != formatFileName("root.d")){
        	current.addProgram(program(fileName,current.name,cpu,mem,p1,p2,cCpu,addToQueue,onDisk));
        	addToCurrent();
        	allDirs.push_back(current);
       	
		}else{
                allDirs[0].addProgram(program(fileName,current.name,cpu,mem,p1,p2,cCpu,addToQueue,onDisk));
                current = allDirs[0];
                
        }
		allPFiles.push_back(program(fileName,current.name,cpu,mem,p1,p2,cCpu,addToQueue,onDisk));
}

//-----------------------------------------------------------------RUSH Methods--------------------------------------------------//
 /*
 * The Main method for RUSH, the information from the file has already been written in the program,
 * RUSH just takes your input and appends the data from the read in file.
 * Then at the end it saves the changes and re-writes the text files to add the new items.
*/
void startRUSH(char **argv){
		
		string fileName = argv[1];
               string command;
        string command2;
        ofstream newFile;
        
        int time = 0;
        newFile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
        cout << " in RUSH" <<endl;
        
        cout << "current Directory is: " << plainName(current.getName()) << endl;
        while(command != "Quit" &&  command != "quit" ){
       	//sleep(1);
		cout << "Enter Command:> ";
        cin >> command;
		cout << "" << endl;

        if(command == "ls"){//------------ ls : uses the listContents method in the current directory object, printing toStrings from files within the directory
				current.listContents();
        }else if(command == "pwd"){//----------------------pwd : Creates the path to the file by checking parents until there are no parents left
            directory fakeCurrent = current;  
			string path = current.name + "/";
			cout << "Path: ";
			do{
				for(int i = allDirs.size()-1; i > -1 ; i--){
					if(fakeCurrent.getParent() == allDirs[i].getName()){
					if(fakeCurrent.getParent() == allDirs[i].getName()){
						fakeCurrent = allDirs[i];
						path.insert(0,fakeCurrent.name + "/");
					}

				}
				}
			}while(fakeCurrent.getParent() != "none");
			cout << path << endl;
		
        }else if(command == "cd"){//--------------------------------cd : was large enough for it's own method below
                changeDirectory();
        }else if(command == "cat"){//--------------------------------cat : prints contents of specified textFile
                cin >> command2;
				for(int t = 0; t < allTFiles.size() ; t++){
					if(plainName(allTFiles[t].name) == command2){
						allTFiles[t].toString();

						}
					}
                
		        }else if(command == "mkdir"){//----------mkdir : uses the createDir method used to make all the other methods to add a new directory to current
                cin >> command2;
				if(command2.length() <= 8 ){
					command2 += ".d";
					createDir(formatFileName(command2));
			}else
					cout << "invalid directory name" << endl;

				pieceTogether();
                					
		}else if(command == "run"){//--------------run : runs all the programs that have been started, and added to the jobsToRun vector, runs until all jobs completed
			runSimulation(burst);
            cMemory = 0;
        }else if(command == "start"){//--------------------- start: <program name> : adds the specified program to the queue of programs to be ran by the run command
                cin >> command2;
                job mJob = getJob(command2 + ".p");
				if(mJob.memory > tMemory){ // check to see if the program uses too much memory
					cout << "Program not added: \n\tThe Program uses to much memory to be ran on the system" << endl;
				}				
				else{
					if(cMemory + mJob.memory <= tMemory){// check if there us enough memory to start the program 
                		cout << "added " << command2 << " to the simulation" << endl;
                		jobsToRun.push_back(mJob);
						cMemory += mJob.memory;			
                	}else{ // if there isn't assign it to vurtual memory
                        cout << "Not Enough memory allocated to add " << command2 << endl;
                        mJob.onDisk = true;
                        cout << "added " << command2 << " to the simulation" << endl;
                        jobsToRun.push_back(mJob);
                        jobsToRun[jobsToRun.size()-1].virtualm = 2;
                        cout << command2 << " will use " << mJob.memory << " virtual Memory" << endl;
                        cMemory = tMemory;
                	}
				}

        }else if(command == "setMemory"){// --------------setMemory: not yet useful 
                cin >> tMemory;
                cout << "set simulation memory to " << tMemory << endl;
        }else if(command == "getMemory"){//--------------------getMemory: not yet useful
                cout << tMemory - cMemory << " Memory Availiable " << tMemory << " total "<< cMemory << " used" <<  endl;
        }else if(command == "addProgram"){//-------------addProgram: creates a program to add to the current directory and a job that can be started and ran
            	cin >> command2;
				string pInput;   
				string sInput;
				int put;
				vector<int> v;
				
				getline(cin, pInput);
				
				if(pInput.size() == 4){
					v.push_back(pInput.at(1)-'0');
					v.push_back(pInput.at(3)-'0');

				}else if(pInput.size() == 8){
					v.push_back(pInput.at(1)-'0');
					v.push_back(pInput.at(3)-'0');
					v.push_back(pInput.at(5)-'0');
					v.push_back(pInput.at(7)-'0');	
				}


				string name;
				int timeRequirement;
                int memRequirement;
                int pair1;
                int pair2;
				timeRequirement = v[0];
				memRequirement = v[1];
				
              			if(v.size() == 4){
						pair1 = v[2];
						pair2 = v[3];
						cout << "added program: " << command2 << endl;    
						createRFile(formatFileName(command2 + ".p"), timeRequirement, memRequirement,pair1,pair2,timeRequirement,0,0);
                		allJobs.push_back(job(command2 + ".p",timeRequirement,memRequirement,pair1,pair2));
					}else if(v.size() == 2){

						cout << "added program: " << command2 << endl;
                		createRFile(formatFileName(command2 + ".p"), timeRequirement, memRequirement,0,0,timeRequirement,0,0);
                		allJobs.push_back(job(command2 + ".p",timeRequirement,memRequirement));
					}
				
               
        }else if(command == "step"){//-------------------- step <int steps> : steps the started jobs 1 unit X times where X is the input
				
				int steps;
				cin >> steps;
                cout << "stepping " <<  steps << " units" << endl;
				cout << "Starting Queue : " << endl;
				printQueue(1);
				for(int j = 0; j < steps ; j++){
					step1(burst);
				}
				updateJobs();
        }else if(command == "setBurst"){//------------------- setBurst: sets the burst amount, i.e the amount a progrtam is ran before being added to the back of the queue
                cin >> burst;
                cout << "set Burst for: " << burst << "units" << endl;

                
		}else if((command == "createTextfile" || command == "createTextFile")){//----------createTextfile or createTextFile : used the createFile method to add a new file to current
                string text;
                cin >> command2;
                createFile(formatFileName(command2));
				pieceTogether();				
		}else if((command == "help") || (command == "Help")){//--------------------Help or help : prints out a help menu
			helpRUSH();


        }else if(command == "quit" || command == "Quit"){// ---------------------Quit or quit : exits RUSH
                cout<< "exiting RUSH" << endl;
        }else
                cout<< "commmand not recognized" << endl;
        }
        pieceTogether();
		
		stringstream fin;
		fin << allDirs[0].getFileInfo() << '\0' << "cMem" << '\0' << cMemory << '\0' << 
			"tMem" << '\0' << tMemory << '\0' << "burst" << '\0' << burst << '\0'; // adds variables cMemory tMemeory and burst to the binary file
	 
		newFile << fin.str();
		
		newFile.close();
}
/*
 * Since CD had two parts it got it's own method
 * based on the input after cd(filename or ..) it either looks for the destination filename and moves current to that position
 * or it just changes you position to the parent of current, unless you are in root, or unable to locate the directory.
*/
void changeDirectory(){
        string command2;
        cin >> command2;
		string command;
		bool found = false;
                if(command2 != ".."){
			 	command = command2 + ".d";
                for(int i = allDirs.size()-1; i > -1 ; i--){
                                if(command == plainName(allDirs[i].getName())){
                                        current = allDirs[i];
                                        found = true;
                                }
                        }
                if(found == true){
                        cout << "changed Directory to: " << plainName(current.getName()) << endl;
                }else
                        cout << "Unable to locate Directory: " << command << endl;
                }else{
                        for(int i = allDirs.size()-1; i > -1 ; i--){
							if(current.getParent() == allDirs[i].getName()){			
                                        current = allDirs[i];
                                        found = true;
										break;				
							}
                        }
                if(found == true){
                        cout << "Moved up to: " << plainName(current.getName()) << endl;
                }else
                        cout << "Unable to locate Directory: " << command2 << endl;
                }
}
//--------------------------------------------------------------------------------------RATCH/RUIN METHODS------------------------------------------------------
vector<job> finished;// all finished vectors so they can be printed
vector<job> doingIO;
//gets a job from the allJobs vector by name
job getJob(string name){
	 string jName;	
		for(int i = 0; i < allJobs.size(); i++){		
		jName = allJobs[i].name;	
		//cout << jName << " " << jName.length() << " " <<   name << " " << name.length() << endl;
			if(jName == name){
                                return allJobs[i];
                        }
                }
        }

/*
 *Runs the simulation in steps of 1 until all jobs in the simulation have been finished
 	takes in an int representing how long a burst cycle lasts
 * 
 */
void runSimulation(int burst){
	
		cout << "Running Simulation to completion" << endl;
		cout << "Burst: " << burst << endl;
		cout << "Starting Queue: "  << endl;
			printQueue(0);
	while(jobsToRun.size() > 0 || doingIO.size() > 0 )//runs until there are no more jobs to run
		step1(burst);
	
	cTime = 0;
	updateJobs();
	finished.clear();
	jobsToRun.clear();// clears the Running jobs vector
	
}


/*
 * used mainly by the run method, but can be called with the 'step' keyword
 * steps the simulation 1 unit and prints the resulting queue
 	takes in an int representing how long a burst cycle lasts
 * 
 */
void step1(int burst){
	vector<job>::iterator it;
	bool justBegan = false;
	int f = 0;
		
		for(int i = 0; i < doingIO.size() ; i++){// advances jobs in IO
		it = doingIO.begin();
		
		
		doingIO[i].cIOtime += 1;

		if(doingIO[i].cIOtime == doingIO[i].pair2){// if the job has done enough IO
		doingIO[i].IO = false;
		doingIO[i].cIOtime = 0;
		cout << "\t<--" <<  doingIO[i].name << " Has finished IO " << endl;
		jobsToRun.push_back(doingIO[i]);
		doingIO.erase(it);
		}
		
		advance(it,1);
	}



		if(jobsToRun.size() > 0){
		if(jobsToRun[f].virtualm > 0){ // if current job is on disk
			jobsToRun[f].virtualm -= 1;
			cout << "\t\t" << jobsToRun[f].name << " : is fetching disk resources" << endl;	
			
				if(jobsToRun[f].virtualm == 1){// if the job is done fetching resources
					if(jobsToRun.size() > 1){	
						if(tMemory < cMemory + jobsToRun[f].memory){//swap memory from last in queue to disk
							jobsToRun[jobsToRun.size() -1].onDisk = true;
							jobsToRun[jobsToRun.size() -1].virtualm = 2;	
						}
						
					}
					jobsToRun[f].onDisk = false; // job is done fetching and is no longer on disk
				}
			
				}else{
				jobsToRun[f].timeLeft -= 1;
				}

		jobsToRun[f].cTime++;
		//cout << jobsToRun[f].timeLeft << jobsToRun[f].pair1 << endl;
	if(jobsToRun[f].pair1 != 0 && (cTime == jobsToRun[f].pair1)){// if the job is entering IO
		cout << "\t--> " << jobsToRun[f].name << " is entering IO for "
			<< jobsToRun[f].pair2 << " time units " << endl;
		jobsToRun[f].IO = true;
		doingIO.push_back(jobsToRun[f]);
		jobsToRun.erase(jobsToRun.begin());
		justBegan = true;

	}else if(jobsToRun[f].timeLeft <= 0){ // if the job is done
		
		jobsToRun[f].finTime = cTime + 1;
		cMemory - jobsToRun[f].memory;
		finished.push_back(jobsToRun[f]);
		jobsToRun.erase(jobsToRun.begin());
	}else if(jobsToRun[f].cTime == burst){//if the job has ran for the burst time
		jobsToRun[f].cTime = 0;
		jobsToRun.push_back(jobsToRun[f]);
		jobsToRun.erase(jobsToRun.begin());
		

	}
		}
			
	
	cTime++;
	printQueue(1);//prints the queue after the step

}
/*
 * called by the step1 method
 * prints the current state of the queue after each iteration of the step1 method
 * takes in an int representing the burst size
 */
void printQueue(int burst){
	int pos = 0;
	bool stillIO = false;
	if(doingIO.size() > 0) // if there are jobs still doing IO
		stillIO = true;
	//cTime += burst;
	cout << "--------Current time <" << cTime << ">" << endl; 
	if(jobsToRun.size() > 0){ // if the running jobs queue is empty
	
	for(int i = 0; i < jobsToRun.size(); i++){
	if(jobsToRun[i].IO == false){//only prints jobs that aren't doing IO, jobs doing IO are still in the queue, just ignored
		if(pos == 0){
		cout << "\tRunning Job" << " : " 
		<< jobsToRun[i].name << " Has " << jobsToRun[i].timeLeft << " time remaining ";
		}else if(pos == 1){
		cout << "\tThe Queue is:\n" << "\tPosition: " << pos - 1 << " : " 
		<< jobsToRun[i].name << " Has " << jobsToRun[i].timeLeft << " time remaining ";
		}else{
		cout << "\tPosition: " << pos - 1 << " : " 
		<< jobsToRun[i].name << " Has " << jobsToRun[i].timeLeft << " time remaining ";
		}
		if(jobsToRun[i].onDisk){
		cout << "and is using " << jobsToRun[i].memory << " disk resources " << endl;
		}else{
		cout << "and is using " << jobsToRun[i].memory << " memory resources " << endl;
		}
		pos++;
	}else
		stillIO = true;
	}

	if(doingIO.size()> 0){// print jobs in IO
		cout << "\t\tJobs doing IO : \n" ;
		for(int i = 0; i < doingIO.size(); i++)
			cout << "\t\t" << doingIO[i].name << " : time Left : "
				 << doingIO[i].pair2 - doingIO[i].cIOtime  << endl; ; 

	}
	
	if(finished.size()> 0){ // print jobs that are finished
		cout << "\t\tFinished Jobs : \n" ;
		for(int i = 0; i < finished.size(); i++)
			cout << "\t\t" << finished[i].name << " " << finished[i].timeTotal 
				<< " " << finished[i].finTime << endl;; 

	}
	
	}else if(stillIO == false){// print the end result
		cout << "\t All jobs complete. " << endl;
		for(int i = 0; i < finished.size(); i++)
			cout << "\t\t" << finished[i].name << " " << finished[i].timeTotal 
				<< " " << finished[i].finTime  << endl;
	}
	else{
		cout << "\t waiting on programs to finish IO "<< endl;
		
	}
	cout << endl;
}

//Assigns the programs corresponding to jobs their new
//time left for computation, so programs can be partly
//computed, saved and then ran in a different session
void updateJobs(){
	if(jobsToRun.size() > 0) // if there are still jobs to be ran update their info
	for(int i = 0 ; i<jobsToRun.size(); i++){
		
		for(int j = 0; j < allPFiles.size(); j++){
			
			if(jobsToRun[i].name == plainName(allPFiles[j].name)){
				allPFiles[j].addToQueue = true;
				allPFiles[j].cCpu = jobsToRun[i].timeLeft;
				allPFiles[j].onDisk = jobsToRun[i].onDisk;
			}
		}

	}
	if(finished.size()>0) // if there are finished jobs update their info
	for(int i = 0 ; i<finished.size(); i++){
		
		for(int j = 0; j < allPFiles.size(); j++){
			
			if(finished[i].name == plainName(allPFiles[j].name)){
				allPFiles[j].addToQueue = false;
				allPFiles[j].cCpu = jobsToRun[i].timeTotal;
				allPFiles[j].onDisk = false;
			}
		}

	}
}

/*
 * Main Method , starts the RUFS program -------------------------------------------------Main Method------------------------------------------------
*/
int main(int argc, char **argv){
        startRUIN(argv);
        return 0;
}

