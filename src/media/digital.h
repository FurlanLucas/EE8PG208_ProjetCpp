// Digital class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See media.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef DIGITAL_H  // Header include check
#define DIGITAL_H

// Includes --------------------------------------------------------------------
#include <iostream>
#include <string>
#include "media.h"

class digital : public media {
private:
  std::string format; // Format of the file (pdf, png, jpg, etc.)
  int size;           // Size of the file (bytes);
  std::string link;   // Acess link

public:
  digital(int reference_, std::string author_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, std::string format_,
    int size, std::string link);
  void showData(); // Display all data in the class (for debug only)
  std::string getFileInfo(void); // Get the info to be saved as a string
};

#endif
