#ifndef MAGAZINE_H
#define MAGAZINE_H

#include <string>
#include "book.h"

class magazine : public book {
private:
  int artNumber; // Number of articles that it contains.

public:
  magazine(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string collection_, std::string summary_, std::string editor_,
    int artNumber_);
  void showData();
};

#endif
