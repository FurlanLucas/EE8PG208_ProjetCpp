#ifndef SOURCE_H
#define SOURCE_H

#include <string>

class sources {
private:
  int reference;
  std::string autor;
  std::string title;
  int addDate;
  int year;
  int totalNumber;
  int dispNumber;

public:
  sources(int reference_, std::string autor_, std::string title_,
          int addDate_, int year_, int totalNumber_, int dispNumber_);
  void showTotalNumber();
  void showDispNumber();
  void displayData();

};

#endif
