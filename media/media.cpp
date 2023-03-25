#include "media.h"
#include <iostream>

media::media(){};

media::media(int reference_, std::string autor_, std::string title_,
    int addDate_, int year_, int totalNumber_, int dispNumber_)
    : reference(reference_)
    , autor(autor_)
    , title(title_)
    , addDate(addDate_)
    , year(year_)
    , totalNumber(totalNumber_)
    , dispNumber(dispNumber_)
    {};

void media::showDispNumber(){
  std::cout << "There are " << dispNumber << " units disponible." << "\n";
};

void media::showTotalNumber(){
  std::cout << "There are " << totalNumber << " in total." << "\n";
};

void media::displayDate(){
  std::cout << "The item was produced in " << year << ".\n";
};

void media::addItem(){
  totalNumber++;
  dispNumber++;
};

void media::removeItem(){
  if(totalNumber > 1){
    totalNumber--;
    dispNumber--;
  }
};

void media::lendItem(){
  if (dispNumber >= 1){
    dispNumber--;
  }
}

void media::returnItem(){
  dispNumber++;
}

int media::getDispNumber(){
  return dispNumber;
}
