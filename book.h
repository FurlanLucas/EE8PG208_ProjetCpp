#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "sources.h"

class book : public sources {
private:
  int pagesNumber; // Book page number
  std::string collection; // Title of the book's collection
  std::string editor; // Editor's name;
  std::string summary; // Breaf summary

public:
  book(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string colletion_, std::string summary_, std::string editor_);
  void showData();
};

#endif
