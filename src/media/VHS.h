// VHS class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See media.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef VHS_H  // Header include check
#define VHS_H


// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include "media.h"

class VHS : public media {
protected:
  int timeDuration;       //  Time duration (seconds)
  std::string production; // Production's house name

public:
  VHS(int reference_, std::string author_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int timeDuration_,
    std::string production_);
  void showData();  // Display all data in the class (for debug only)
  std::string getFileInfo(void); // Get the info to be saved as a string
};

#endif
