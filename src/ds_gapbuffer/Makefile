Includes = ./includes
CXX = g++
CFLAGS = -std=c++11 -g
OutputFileName= Scribble.out

TestFiles = ./tests/unittest.cpp
# Libs=#whatever libraries you need to provide to g++
Scribble: GapBuffer.o testMain.o guilib.o
	$(CXX) $(CFLAGS) -o Scribble GapBuffer.o testMain.o guilib.o
	$(MAKE) buildtests	
	$(MAKE) runtest

testMain.o:testMain.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o testMain.o testMain.cpp 
GapBuffer.o:GapBuffer.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o GapBuffer.o GapBuffer.cpp

guilib.o:guilib.cpp
	$(CXX) $(CFLAGS) -c -o guilib.o guilib.cpp

clean:
	rm *.o *.log
buildtests:$(TestFiles)
	$(CXX)  $(CFLAGS) -o unittest -lboost_unit_test_framework $(TestFiles)
runtest:unittest
	./unittest >report.log
