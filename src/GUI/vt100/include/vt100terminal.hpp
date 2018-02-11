#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <string>

#define CTRL_KEY(k) ((k) & 0x1f)

struct KEYS {
enum CODES{
  SAVE_DOC   = CTRL_KEY('s'),
  OPEN_DOC   = CTRL_KEY('o'),
  EXIT_TERM  = CTRL_KEY('q'),
  BACKSPACE  = 127,
  UP_ARROW   = 1000,
  DOWN_ARROW,
  LEFT_ARROW,
  RIGHT_ARROW
  };
};

class VT100gui {
  int numOfRows;
  int numOfCols;
  int currRow;
  int currCol;
  struct termios orig_termios;

  void editorDrawRows();
  void getWinSize();
  void exitonException(const char *s);
  void CommandWriterHelper(const std::string command);
  void statusBar(std::string fName, bool dirty);
  int ReadKey();
  int getCursorPosition();

public:
  VT100gui();
  ~VT100gui();
  void clearScreen();
  void editorRefreshScreen(std::string fName, bool dirty);
  void writeContent(std::string content);
  void DrawCursor(int row, int column);

  int VT100CommandProcess();
  int getRow() const;
  int getColumn() const;

  std::string commandInputs();
};
