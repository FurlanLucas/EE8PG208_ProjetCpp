#include "sources.h"
#include <iostream>

sources::sources(int reference_, std::string autor_, std::string title_,
    int addDate_, int year_, int totalNumber_, int dispNumber_)
    : reference(reference_)
    , autor(autor_)
    , title(title_)
    , addDate(addDate_)
    , year(year_)
    , totalNumber(totalNumber_)
    , dispNumber(dispNumber_)
    {};

void sources::showDispNumber(){
  std::cout << "There are " << dispNumber << " units disponible." << "\n";
};

void sources::showTotalNumber(){
  std::cout << "There are " << totalNumber << " in total." << "\n";
};

void sources::displayDate(){
  std::cout << "The item was produced in " << year << ".\n";
};
