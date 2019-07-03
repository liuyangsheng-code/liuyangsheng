#FileName: Makefile
#Compile cmd: make

CC  = gcc
CPP = g++
CXX = gcc
EXECUTABLE = metalCaculate

all     :  $(EXECUTABLE)
	rm -f *.o
clean   :
	rm -f *.o $(EXECUTABLE)
$(EXECUTABLE)	: main.o metal.o memberInfo.o
	$(CPP) -o $@ $^ -ljson

%.o     : %.cpp
	$(CPP)  -c $< -o $@

