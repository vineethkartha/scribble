#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <string>

#define CTRL_KEY(k) ((k) & 0x1f)

struct KEYS {
enum CODES{
  SAVE_DOC   = CTRL_KEY('s'),
  EXIT_TERM  = CTRL_KEY('q'),
  BACKSPACE  = 127,
  UP_ARROW   = 1000,
  DOWN_ARROW,
  LEFT_ARROW,
  RIGHT_ARROW
  };
};
class VT100gui {
  struct termios orig_termios;

  void getWinSize();
public:
  VT100gui();
  ~VT100gui();
  int rowSize;
  int colSize;
  void exitonException(const char *s);
  //void revertToNormalMode();
  //void startRawMode(); 
  void editorDrawRows();
  void editorRefreshScreen();
  int ReadKey();
  int VT100CommandProcess();
  int getCursorPosition(int *rows, int *cols);
  void statusBar(std::string, int rows);

};
