// Book class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See media.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef BOOK_H  // Header include check
#define BOOK_H


// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include "media.h"


class book : public media {
protected:
    int pagesNumber;        // Book page number
    std::string collection; // Title of the book's collection
    std::string editor;     // Editor's name
    std::string summary;    // Breaf summary

public:
    // Constructor
    book(int reference_, std::string author_, std::string title_, int addDate_,
        int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
        std::string collection_, std::string summary_, std::string editor_);
   void showData(); // Display all data in the class (for debug only)
   std::string getFileInfo(void); // Get the info to be saved as a string
   int searchFor(std::string toSearch); // Research the info required
};

#endif
