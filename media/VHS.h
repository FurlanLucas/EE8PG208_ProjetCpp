#ifndef VHS_H
#define VHS_H

#include <string>
#include "media.h"

class VHS : public media {
private:
  int timeDuration; //  Time duration (seconds)
  std::string production; // Production's house name

public:
  VHS(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int timeDuration_,
    std::string production_);
  void showData();
};

#endif
