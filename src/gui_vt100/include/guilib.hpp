#include <unistd.h>
#include <stdlib.h>
#include <termios.h>


#define CTRL_KEY(k) ((k) & 0x1f)

class VT100gui {
  struct termios orig_termios;
  
  
public:
  VT100gui();
  ~VT100gui();
  
  void exitException(const char *s);
  //void revertToNormalMode();
  //void startRawMode(); 
  void editorDrawRows();
  void editorRefreshScreen();
  char editorReadKey();


};
