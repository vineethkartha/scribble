Includes = -I ./include 
CXX = g++
CFLAGS = -std=c++17 -g

TestFiles = ./tests/unittest.cpp
# Libs=#whatever libraries you need to provide to g++

GapBuffer.o:GapBuffer.cpp
	$(CXX) $(CFLAGS) $(Includes) -c -o ../../GapBuffer.o GapBuffer.cpp
	$(MAKE) buildtests		
	$(MAKE) runtest
clean:
	rm *.o *.log
buildtests:$(TestFiles)
	$(CXX)  $(CFLAGS) -o unittest -lboost_unit_test_framework $(TestFiles)
runtest:unittest
	./unittest 
