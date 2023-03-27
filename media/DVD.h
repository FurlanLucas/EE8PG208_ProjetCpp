// DVD class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See VHS.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef DVD_H  // Header include check
#define DVD_H


// Includes --------------------------------------------------------------------
#include <iostream>
#include <string>
#include "VHS.h"


class DVD : public VHS {
private:
  int trackNumber; // Book pages number

public:
  DVD(int reference_, std::string autor_, std::string title_, int addDate_,
      int year_, int totalNumber_, int dispNumber_, int timeDuration_,
      std::string production_, int trackNumber_);
  void showData();  // Display all data in the class (for debug only)
};

#endif
