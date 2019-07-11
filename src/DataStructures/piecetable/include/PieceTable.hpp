#include<string>
#include<list>

using uint = unsigned int;

enum class Buffer:bool {
  Original,
  Add
};

class Piece {
  Buffer buffer;
  uint start;
  uint length;
  
public:
  Piece():buffer(Buffer::Add), start(0), length(0){};
  Piece(Buffer bN, uint s, uint l):buffer(bN),start(s), length(l){};
  ~Piece() {};
  
  auto getBuffName() const{
    return this->buffer;
  }
  
  void setBuffName(Buffer bufN) {
    this->buffer = bufN;
  }

  auto getLength() const {
    return this->length;
  }
  
  void setLength(uint len) {
    this->length = len;
  }

  auto getStart() const {
    return this->start;
  }
  
  void setStart(uint start) {
    this->start = start;
  }

  auto containsPoint(uint point) const {
    if(point < start || point > (start+length)) {
      return false;
    }
    return true;
  }
};

class PieceTable {
  std::list<Piece> table;
  std::string OrigBuf;
  std::string AddBuf;
  
public:
  PieceTable():OrigBuf(""),AddBuf(""){};
  
  PieceTable(std::string text):OrigBuf(text),AddBuf("") {
    Piece p(Buffer::Original,0,text.length());
    table.push_back(p);
  }

  //xxx delete the copy and move operators
  ~PieceTable() {
  }

  void add(std::string text, uint splitPoint);
  void del(uint start, uint end);
  void displayTable() const;
  void displayText() const;
};
