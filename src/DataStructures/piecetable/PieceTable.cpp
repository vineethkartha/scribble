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


/*
  For deleting we have three possibilities
  1. Either an entire piece can be deleted
     This can happen if the start and end coincide with the start and end of a piece
     Then delete that entry from the piece table
  2. the deleted portion is a subset of a piece
     In this case split the piece into two pieces
  3. Deleted portion spans across multiple pieces
     In this scenario split the truncate the start and end pieces and delete everything in between
 */


void PieceTable::del(uint start, uint end) {
  auto length = end - start;
  if(table.empty() || length == 0) {
    return;
  }

  auto itr1 = table.end();
  auto itr2 = table.end();

  auto PieceContainsStart = [&start](Piece p) {
      if(p.containsPoint(start)) {
          return true;
      }
      start = start - p.getLength();
      return false;
  };

  
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

  // case 1
  if(itr1->getStart() == start && itr1->getLength() == end - start) {
      table.erase(itr1);
      //return;
  }
  // case 2
  else {
      
  }

  // case 3
}

void PieceTable::displayTable() const{
  std::cout<<"\nBuff \t Start \t Length\n";
  for(const auto& pt: this->table) {
    std::cout<<static_cast<std::underlying_type<Buffer>::type>(pt.getBuffName())<<"\t "<<pt.getStart()<<"\t "<<pt.getLength()<<"\n";
  }
  std::cout<<OrigBuf<<"\n"<<AddBuf;
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
 
