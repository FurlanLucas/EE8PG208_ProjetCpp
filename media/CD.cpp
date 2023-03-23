#include <iostream>
#include "CD.h"

CD::CD(int reference_, std::string autor_, std::string title_, int addDate_,
  int year_, int totalNumber_, int dispNumber_, int timeDuration_,
  std::string production_, int trackNumber_)
  : media{reference_,autor_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , timeDuration(timeDuration_)
  , production(production_)
  , trackNumber(trackNumber_){
}

void CD::showData(){
  std::cout << "This item (code " << reference << ") is a " << year <<
  " CD by " << autor << " called \"" << title << "\",\nproduced by " <<
  production << " with " << trackNumber << " tracks.\n";
};
