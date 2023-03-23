#ifndef DIGITAL_H
#define DIGITAL_H

#include <string>
#include "media.h"

class digital : public media {
private:
  std::string format; // Title of the book's collection
  int size; // Editor's name;
  std::string link; // Breaf summary

public:
  digital(int reference_, std::string autor_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, std::string format_,
    int size, std::string link);
  void showData();
};

#endif
