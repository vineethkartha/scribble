#include <fstream>

class GapBuffer;

class DocumentInterface {
  std::ofstream fileHandler;
  std::string fileName = "untitled";
  GapBuffer *gapBuff;

public:
  static int fileCounter;
  DocumentInterface(); // make sure this opens as untitledxx
  //  Document(std::string fName); 

  ~DocumentInterface();
};
