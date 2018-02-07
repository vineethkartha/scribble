
class Document {
  FILE *fileHandler;
  std::string fileName = "untitled";
  GapBuffer gapBuff(1000);

public:
  Document(); // make sure this opens as untitledxx

  // Check if this file is already opened ,
  // if opened point to that instead of creating a new object
  Document(std::string fName); 

  ~Document();
}
