Includes = ./includes
CXX = g++
CFLAGS = -std=c++11 -g
OutputFileName= Scribble.out


# Libs=#whatever libraries you need to provide to g++
Scribble: GapBuffer.o testMain.o vt100terminal.o
	$(CXX) $(CFLAGS) -o Scribble GapBuffer.o testMain.o vt100terminal.o

testMain.o:testMain.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o testMain.o testMain.cpp 

GapBuffer.o:DataStructures/gapbuffer/GapBuffer.cpp
	$(MAKE) -C DataStructures/gapbuffer
vt100terminal.o:GUI/vt100/vt100terminal.cpp
	$(MAKE) -C GUI/vt100

clean:
	rm *.o *.log
