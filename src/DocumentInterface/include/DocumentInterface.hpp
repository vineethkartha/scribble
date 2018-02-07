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
  void NavigateBuffer(int cols, int rows);
  void SaveBufferToFile();
  void OpenFileToBuffer();
  void UpdateBuffer(int ch);
  std::string printGapBuffer();
};
