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

int media::getTotalNumber(){
  return TotalNumber;
}

void media::showData(){}

std::string media::getAutor(){
  return autor;
}

std::string media::getTitle(){
  return title;
}

int media::getReference(){
  return reference;
}


int media::searchFor(std::string toSearch){
  std::size_t foundAutor = autor.find(toSearch);
  std::size_t foundTitle = title.find(toSearch);
  if(foundTitle!=std::string::npos || foundAutor!=std::string::npos){
    return 1;
  } else {
    return 0;
  }
}
