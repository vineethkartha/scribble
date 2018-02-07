#include "include/DocumentInterface.hpp"
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include <iostream>

int DocumentInterface::fileCounter = 0;

DocumentInterface::DocumentInterface() {
  fileName = fileName + std::to_string(fileCounter) + ".txt";
  fileCounter += 1;
  std::cout<<fileName; // debug statement
}

DocumentInterface::~DocumentInterface() {
  fileCounter = fileCounter?fileCounter -= 1:0;
}
