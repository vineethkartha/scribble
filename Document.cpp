#include<iostream>
#include<vector>
class Document
{
private:
  std::vector<char> textBody;
  int cursorPosition;
  std::ofstream myfile;
public:
  Document()
  {
    this->cursorPosition=0;
  }
  void insert(char letter)
  {
    this->textBody.insert(this->textBody.begin()+cursorPosition,letter);
    this->cursorPosition++;
  }
  void deletel()
  {
    //TODO check if the cursor is at end of text document
    this->textBody.erase(this->textBody.begin()+this->cursorPosition);
  }
  void backspace()
  {
    this->cursorPosition--;
    this->textBody.erase(this->textBody.begin()+this->cursorPosition);
  }
  void save(char *name)
  {
    myfile.open(name);
    for(int i=0;i<textBody.size();i++)
      {
	myfile<<textBody[i];
      }
    myfile.close();
  }
  void display()
  {
    for(int i=0;i<textBody.size();i++)
      {
	std::cout<<textBody[i];
      }
  }
};
