fs3: FileSystem.o tFile.o program.o directory.o job.o
	g++ -o RUIN FileSystem.o tFile.o program.o job.o directory.o
tFile.o: tFile.cpp tFile.h
	g++ -c tFile.cpp
program.o: program.cpp program.h
	g++ -c program.cpp
job.o: job.cpp job.h
	g++ -c job.cpp
directory.o: directory.cpp directory.h tFile.h program.h
	g++ -c directory.cpp
FileSystem.o: FileSystem.cpp tFile.h job.h directory.h program.h         
	g++ -c FileSystem.cpp
clean: rm *.o
