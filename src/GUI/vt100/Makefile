Includes = ./includes
CXX = g++
CFLAGS = -std=c++1y -g


#TestFiles = ./tests/unittest.cpp
# Libs=#whatever libraries you need to provide to g++

vt100terminal.o:vt100terminal.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o ../../vt100terminal.o vt100terminal.cpp

clean:
	rm *.o *.log
buildtests:$(TestFiles)
	$(CXX)  $(CFLAGS) -o unittest -lboost_unit_test_framework $(TestFiles)
runtest:unittest
	./unittest >report.log
