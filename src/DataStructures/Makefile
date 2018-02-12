Includes = -I ./include -I ./gapbuffer/include
CXX = g++
CFLAGS = -std=c++11 -g

TestFiles = ./tests/unittest.cpp
# Libs=#whatever libraries you need to provide to g++
DataStructureInterface.o: DataStructureInterface.cpp
	$(CXX) $(CFLAGS) $(Includes) -c -o ../DataStructureInterface.o  DataStructureInterface.cpp

clean:
	rm *.o *.log
buildtests:$(TestFiles)
	$(CXX)  $(CFLAGS) -o unittest -lboost_unit_test_framework $(TestFiles)
runtest:unittest
	./unittest 
