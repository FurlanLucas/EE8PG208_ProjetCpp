#ifndef CD_H
#define CD_H

#include <string>
#include "sources.h"

class CD : public sources {
private:
  int timeDuration; //  Time duration (seconds)
  std::string production; // Production's house name
  int trackNumber; // Number of tracks in the CD;

public:
  CD(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int timeDuration_,
    std::string production_, int trackNumber_);
  void showData();
};

#endif
