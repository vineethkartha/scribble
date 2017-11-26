Includes = ./includes
CXX = g++
CFLAGS = -std=c++11 -g
OutputFileName= Scribble.out
# Libs=#whatever libraries you need to provide to g++
Scribble: GapBuffer.o testMain.o
	$(CXX) $(CFLAGS) -o Scribble GapBuffer.o testMain.o

testMain.o:testMain.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o testMain.o testMain.cpp 
GapBuffer.o:GapBuffer.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o GapBuffer.o GapBuffer.cpp
clean:
	rm *.o
runtests:
	$(CXX) ./test/sampleTest.cpp -DSTAND_ALONE -lboost_unit_test_framework -o tests
