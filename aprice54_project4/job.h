#ifndef job_h
#define job_h

/*
 * class to define jobs for later projects *ignore*
 * 
 * 
 * */
#include <string>
#include <iostream>
using namespace std;

class job
{
public:
        string name;
        int memory;
        int timeTotal;
        int timeLeft;
        int pair1;
        int pair2;
        int virtualm;
        bool IO;
		int cTime;
		int cIOtime;
		int finTime;
		bool onDisk;


        job(string n, int tt, int mem, int p1, int p2);

		job(string n, int tt, int mem);        
};

#endif
