#ifndef DVD_H
#define DVD_H

#include <string>
#include "VHS.h"

class DVD : public VHS {
private:
  int trackNumber; // Book page number

public:
  DVD(int reference_, std::string autor_, std::string title_, int addDate_,
      int year_, int totalNumber_, int dispNumber_, int timeDuration_,
      std::string production_, int trackNumber_);
  void showData();
};

#endif
