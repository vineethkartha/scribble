
class DocumentInterface;
class Command {
public:
  virtual void execute(int ch) = 0;
};

class UpdateBufferCommand :public Command {
public:
  UpdateBufferCommand(DocumentInterface *doc):mD(doc){}
  void execute(int ch) {
    mD->UpdateBuffer(ch);
  }
private:
  DocumentInterface *mD;
};
