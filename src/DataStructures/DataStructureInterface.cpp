//#include "include/DataStructureInterface.hpp"
#include "gapbuffer/include/GapBuffer.hpp"

DataStructureInterface* DataStructureInterface::CreateDS(int choice) {
  if(choice == 1)
    return (new GapBuffer(100));
  return nullptr;
}
