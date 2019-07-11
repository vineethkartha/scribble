Includes = -I ./include 
CXX = g++
CFLAGS = -std=c++1y -g

#TestFiles = ./tests/unittest.cpp
# Libs=#whatever libraries you need to provide to g++

PieceTable.o:PieceTable.cpp
	$(CXX) $(CFLAGS) $(Includes) -c -o ../../PieceTable.o PieceTable.cpp
#	$(MAKE) buildtests		
#	$(MAKE) runtest
clean:
	rm *.o *.log
buildtests:$(TestFiles)
	$(CXX)  $(CFLAGS) -o unittest -lboost_unit_test_framework $(TestFiles)
runtest:unittest
	./unittest 
