#ifndef PAPER_H
#define PAPER_H

#include <string>
#include "book.h"

class paper : public book {
private:
  int artNumber; // Number of articles that it contains.

public:
  paper(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string collection_, std::string summary_, std::string editor_,
    int artNumber_);
  void showData();
};

#endif
