// Magazine class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See book.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef MAGAZINE_H  // Header include check
#define MAGAZINE_H


// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include "book.h"

class magazine : public book {
private:
  int artNumber; // Number of articles that it contains.

public:
  magazine(int reference_, std::string author_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string collection_, std::string summary_, std::string editor_,
    int artNumber_);
  void showData();  // Display all data in the class (for debug only)
  std::string getFileInfo(void); // Get the info to be saved as a string
};

#endif
