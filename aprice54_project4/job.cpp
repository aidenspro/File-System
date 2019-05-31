
#include "job.h"

using namespace std;
job::job(string n, int tt, int mem, int p1, int p2)
{
        virtualm = 0;
        name = n;
        IO = false;
        memory = mem;
        timeTotal = tt;
        timeLeft = tt;
        pair1 = p1;
        pair2 = p2;
		cTime = 0;
		cIOtime = 0;
		finTime = 0;
		onDisk = false;
}
job::job(string n, int tt, int mem)
{		
        virtualm = 0;
        name = n;
        IO = false;
        memory = mem;
        timeTotal = tt;
        timeLeft = tt;
        pair1 = 0;
        pair2 = 0;
		cTime = 0;
		cIOtime = 0;
		finTime = 0;
		onDisk = false;
}

        


