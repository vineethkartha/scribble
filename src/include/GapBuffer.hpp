/*
Initialise the gap buffer with a given size
initialise gap buffer with a given file

* AddChar()
* deleteChar()
* resizeBuffer()
* moveBuffer()

Start with the buffer size and gap size as same
Then keep adding the characters to the buffer
If the cursor is moved then the gapStart moves to the current point


Starting
[__________] -> Gapsize = buffer Size =10
Insert ABCD
ABCD[______] -> Gapstart = insertCounter = 4
Move Cursor before C
AB[______]CD ->GapStart = CurrentPointer
GapEnd = gapStart+ (gapSize-insertCounter)
 */
#include <string>
class GapBuffer {
  unsigned int gapSize = 100;
  unsigned int insertCounter = 0;
  char *bufferStart;
  char *bufferEnd;
  char *gapStart;
  char *gapEnd;
  char *cursorPos;
  char *buffer;
public:
  GapBuffer(int gapSize);
  //GapBuffer(FILE *fileH);
  //GapBuffer(FILE *file, int gapSize);
  ~GapBuffer();
  char* addChar(char c);
  void deleteChar(int pos);
  void resizeBuffer(unsigned int size);
  void MoveGap(int pos);
  std::string printBuffer();
  void Debugprint();
};
