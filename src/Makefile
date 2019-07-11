Includes = ./includes
CXX = g++
CFLAGS = -std=c++1y -g
OutputFileName= Scribble.out


# Libs=#whatever libraries you need to provide to g++
Scribble: DataStructureInterface.o PieceTable.o GapBuffer.o testMain.o vt100terminal.o DocumentInterface.o
	$(CXX) $(CFLAGS) -o Scribble DataStructureInterface.o GapBuffer.o testMain.o vt100terminal.o DocumentInterface.o PieceTable.o

PieceTable.o:DataStructures/piecetable/PieceTable.cpp
	$(MAKE) -C DataStructures/piecetable
GapBuffer.o:DataStructures/gapbuffer/GapBuffer.cpp
	$(MAKE) -C DataStructures/gapbuffer
testMain.o:testMain.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o testMain.o testMain.cpp
DataStructureInterface.o:DataStructures/DataStructureInterface.cpp
	$(MAKE) -C DataStructures
DocumentInterface.o:DocumentInterface/DocumentInterface.cpp 
	$(MAKE) -C DocumentInterface
vt100terminal.o:GUI/vt100/vt100terminal.cpp
	$(MAKE) -C GUI/vt100

clean:
	rm *.o *.log
