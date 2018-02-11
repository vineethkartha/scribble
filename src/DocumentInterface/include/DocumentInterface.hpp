#include <fstream>

class GapBuffer;

class DocumentInterface {
  std::fstream fileHandler;
  std::string fileName = "untitled";
  int dirtyFlag;
  bool fileNameisSet;
  GapBuffer *gapBuff;

public:
  static int fileCounter;
  DocumentInterface(); // make sure this opens as untitledxx
  DocumentInterface(std::string fileName); // make sure this opens as untitledxx

  ~DocumentInterface();
  
  std::string getFileName() const;
  bool isDirtyState() const;
  bool getFileNameisSet() const;
  
  void NavigateBuffer(int cols, int rows);
  void SaveBufferToFile(std::string fName = "");
  void UpdateBuffer(int ch);
  std::string printGapBuffer();
};
