#include "CD.h"

CD::CD(int reference_, std::string author_, std::string title_, int addDate_,
  int year_, int totalNumber_, int dispNumber_, int timeDuration_,
  std::string production_, int trackNumber_)
  : media{reference_,author_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , timeDuration(timeDuration_)
  , production(production_)
  , trackNumber(trackNumber_){
}

void CD::showData(){
  // Function to display all the important info in class (for debug only).
  std::cout << "This item (code " << reference << ") is a " << year <<
  " CD by " << author << " called \"" << title << "\",\nproduced by " <<
  production << " with " << trackNumber << " tracks.\n";
};


std::string CD::getFileInfo(void){
  // This function returns a string that contains all important informations about
  // this article to be saved in a txt file. It's used in "toFile" function at 
  // "library" class.
  
  return "C\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
    + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
    std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
    std::to_string(timeDuration) + "\n" + production + "\n" + std::to_string(trackNumber);
}
