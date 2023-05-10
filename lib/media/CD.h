// CD class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. See media.h for more information.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef CD_H  // Header include check
#define CD_H


// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include "media.h"


class CD : public media {
private:
    int timeDuration;       // Time duration (minutes)
    std::string production; // Production's house name
    int trackNumber;        // Number of tracks in the CD

public:
    CD(int reference_, std::string author_, std::string title_, int addDate_,
        int year_, int totalNumber_, int dispNumber_, int timeDuration_,
        std::string production_, int trackNumber_);
    void showData();  // Display all data in the class (for debug only)
    std::string getFileInfo(void); // Get the info to be saved as a string
    int searchFor(std::string toSearch); // Research the info required
};

#endif
