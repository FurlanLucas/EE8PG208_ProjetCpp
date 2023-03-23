#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "media.h"

class book : public media {
public:
  int pagesNumber; // Book page number
  std::string collection; // Title of the book's collection
  std::string editor; // Editor's name;
  std::string summary; // Breaf summary

public:
  book(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string collection_, std::string summary_, std::string editor_);
  void showData();
};

#endif
