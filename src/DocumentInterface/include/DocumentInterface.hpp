#include <fstream>
#include <memory>
class DataStructureInterface;

class DocumentInterface {
  std::fstream fileHandler;
  std::string fileName = "untitled";
  int dirtyFlag;
  bool fileNameisSet; 
  // make this unique ptr
  DataStructureInterface *contentBuffer;

public:
  static int fileCounter;
  DocumentInterface(); // make sure this opens as untitledxx
  DocumentInterface(std::string fileName); // make sure this opens with the specified file

  ~DocumentInterface();
  
  std::string getFileName() const;
  bool isDirtyState() const;
  bool getFileNameisSet() const;
  
  void NavigateBuffer(int cols, int rows);
  void SaveBufferToFile(std::string fName = "");
  void UpdateBuffer(int ch);
  void BackSpaceBuffer();
  std::string printGapBuffer();
};
