#include<iostream>
#include<algorithm>
#include"PieceTable.hpp"

void PieceTable::add(std::string text, uint splitPoint) {
  if(table.empty()) {
    Piece p(Buffer::Add, 0, text.length());
    table.push_back(p);
  } else {
    auto PieceContainsPoint = [&splitPoint](Piece p) {
      if(p.containsPoint(splitPoint)) {
	return true;
      }
      splitPoint = splitPoint - p.getLength();
      return false;
    };
    
    auto itr = std::find_if(table.begin(), table.end(),PieceContainsPoint);
    
    if(itr->getStart() != splitPoint) {
      Piece p1(itr->getBuffName(),itr->getStart(),splitPoint);
      table.insert(itr,p1);
    }
    Piece p2(Buffer::Add,AddBuf.length(),text.length());
    table.insert(itr,p2);
    if((itr->getLength() - splitPoint) != 0) {
      Piece p3(itr->getBuffName(),splitPoint,(itr->getLength() - splitPoint));
      table.insert(itr,p3);
    }
    table.erase(itr);
  }
  AddBuf += text;
}

void PieceTable::del(uint start, uint end) {
  auto length = end - start;
  if(table.empty() || length == 0) {
    return;
  }

  auto itr1 = table.end();
  auto itr2 = table.end();
  
  for(auto itr = table.begin(); itr != table.end(); ++itr) {
    if(itr1 == table.end()) {
      if(itr->containsPoint(start)) {
	itr1 = itr;
      }else{
	start -= itr->getLength();
      }
    }
    if(itr2 == table.end()) {
      if(itr->containsPoint(end)) {
	itr2 = itr;
      }else{
	end -= itr->getLength();
      }
    }
    
  }
  auto PieceContainsPoint = [&start](Piece p) {
      if(p.containsPoint(start)) {
	return true;
      }
      start = start - p.getLength();
      return false;
  };

  auto itr = std::find_if(table.begin(), table.end(),PieceContainsPoint);
  
}

void PieceTable::displayTable() const{
  std::cout<<"\nBuff \t Start \t Length\n";
  for(const auto& pt: this->table) {
    std::cout<<static_cast<std::underlying_type<Buffer>::type>(pt.getBuffName())<<"\t "<<pt.getStart()<<"\t "<<pt.getLength()<<"\n";
  }
}

void PieceTable::displayText() const{
  for(const auto& pt: this->table) {
    if(pt.getBuffName() == Buffer::Original) {
      std::cout<<OrigBuf.substr(pt.getStart(),pt.getLength());
    } else {
      std::cout<<AddBuf.substr(pt.getStart(),pt.getLength());
    }
  }
}
 
