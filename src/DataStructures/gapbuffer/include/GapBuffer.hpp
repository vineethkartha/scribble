#include "../../include/DataStructureInterface.hpp"
#include <string>
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
/**
 * @brief This class represents the GapBuffer data structure
 * 
 * The Gap buffer https://en.wikipedia.org/wiki/Gap_buffer
 * is the base data structure used by scribble
 * This class implements the data structure.
 */

class GapBuffer:public DataStructureInterface {
  
  unsigned int gapSize;
  unsigned int insertCounter = 0;
  char *bufferStart;
  char *bufferEnd;
  char *gapStart;
  char *gapEnd;
  char *cursorPos;
  char *buffer;
public:
  /**
   *@brief Constructor
   */
  explicit GapBuffer(int gapSize);
  ~GapBuffer();

  /**
   * @name Insert
   * @brief This functions inserts the given character
   * This function checks if the buffer is full. If it is full
   * It resizes the buffer and inserts the character.
   * @param symbol
   */
  void Insert(char symbol) override;

  /**
   * @name Delete
   * @brief This function deletes the character at the current position.
   */
  void Delete() override;

  /**
   * @name Backspace
   * @brief This function deletes the character previous to the current position.
   */
  void Backspace() override;
  
  /**
   * @name MoveCursor
   * @brief This function moves the gap to wherever position mentioned.
   * Based on the paramter pos, the gap is moved either forward
   * or backward in the buffer. 
   * @param int pos
   */
  void MoveCursor(int pos) override;
  
  /**
   * @name ResizeBuffer
   * @brief When the buffer runs ou of space this function increases the buffer size.
   */
  void ResizeBuffer() override;
  
  /**
   * @name getContentOfBuffer
   * @brief This function returns the contents of the buffer.
   * @return std::string
   */
  std::string getContentOfBuffer() const override;
  
  void Debugprint();
};
