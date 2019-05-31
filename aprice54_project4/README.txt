
Tyler Price
project 4

					README File

Problems addressed:
	Project has been refactored post project 3 to address length issues
		all classes: directory tFile program job
		have been moved to seperate files

	More comments have been added everywhere
		more inline comments and header comments above all functions
	
	Figured out why project 3 return a slightly different output than the example provided:
		
		Reason: Misunderstood second parity bit
		i.e thought that a job went into IO when it itself reached a remaining time to run equal to the second parity bit
		Job first 4 3 2 1 would wait until 4--->1 then would enter IO

	problem has been addressed for project four and the sheduler now runs smoothly and accurately even when
	doing complex operations such as stepping, quiting the program, starting a new session and running to completion

complex operations such as the one above should now work taking virtual memory into account.
the program saves whether a programs memory is stored on disk and should fetch it at the approprate time
whether or not the FileSystem program is closed and opened during simulation.

The code to add virtual memory did not require any new methods, so all of the logic is coded within the step1 method 
and the If-elses in the startRUSH method



