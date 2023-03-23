#include <iostream>
#include "digital.h"

digital::digital(int reference_, std::string autor_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_,
  std::string format_, int size_, std::string link_)
  : media{reference_,autor_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , format(format_)
  , size(size_)
  , link(link_){
}

void digital::showData(){
  std::cout << "This item (code " << reference << ") is a " << year <<
  " " << format << " file by " << autor << "\ncalled \"" << title <<
  "\navailable in " << link << ".\n";
};
