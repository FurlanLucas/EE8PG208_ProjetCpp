#include "digital.h"

digital::digital(int reference_, std::string author_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_,
  std::string format_, int size_, std::string link_)
  : media{reference_,author_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , format(format_)
  , size(size_)
  , link(link_){
}

void digital::showData(){
  // Function to display all the important info in class (for debug only).
  std::cout << "This item (code " << reference << ") is a " << year <<
  " " << format << " file by " << author << "\ncalled \"" << title <<
  "\navailable in " << link << ".\n";
};


std::string digital::getFileInfo(void){
  // This function returns a string that contains all important informations about
  // this article to be saved in a txt file. It's used in "toFile" function at 
  // "library" class.
  
  return "d\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
    + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
    std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
    format + "\n" + std::to_string(size) + "\n" + link;
}