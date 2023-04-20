#include "VHS.h"

VHS::VHS(int reference_, std::string author_, std::string title_, int addDate_,
  int year_, int totalNumber_, int dispNumber_, int timeDuration_,
  std::string production_)
  : media{reference_,author_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , timeDuration(timeDuration_)
  , production(production_){
}

void VHS::showData(){
  // Function to display all the important info in class (for debug only).
  std::cout << "This item (code " << reference << ") is a " << year <<
  " CD by " << author << " called \"" << title << "\",\nproduced by " <<
  production << ".\n";
};


std::string VHS::getFileInfo(void){
  // This function returns a string that contains all important informations about
  // this article to be saved in a txt file. It's used in "toFile" function at 
  // "library" class.
  
  return "V\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
    + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
    std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
    std::to_string(timeDuration) + "\n" + production;
}