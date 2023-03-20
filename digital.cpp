#include <iostream>
#include "digital.h"

digital::digital(int reference_, std::string autor_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_,
  std::string format_, int size_, std::string link_)
  :sources{reference_,autor_,title_,addDate_,year_,totalNumber_,dispNumber_}{

  format = format_; // Title of the book's collection
  size = size_; // Editor's name;
  link = link_; // Breaf summary
}

void digital::showData(){
  std::cout << "This item (code " << reference << ") is a " << year <<
  " " << format << " file by " << autor << "\ncalled \"" << title <<
  "\navailable in " << link << ".\n";
};
