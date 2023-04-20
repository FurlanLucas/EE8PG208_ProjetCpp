#include "magazine.h"

magazine::magazine(int reference_, std::string author_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
  std::string collection_, std::string summary_, std::string editor_,
  int artNumber_)
  : book{reference_, author_, title_, addDate_, year_, totalNumber_, dispNumber_,
        pagesNumber_, collection_, summary_, editor_}
  , artNumber(artNumber_){
}

void magazine::showData(){
  // Function to display all the important info in class (for debug only).
  std::cout << "This item (code " << reference << ") is a " << year <<
  " book by " << author << " called \"" << title << "\",\npublished by " <<
  editor << " with " << pagesNumber << " pages. " << summary << ".\n";
};


std::string magazine::getFileInfo(void){
  // This function returns a string that contains all important informations about
  // this article to be saved in a txt file. It's used in "toFile" function at 
  // "library" class.
  
  return "m\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
    + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
    std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
    std::to_string(pagesNumber) + "\n" + collection + "\n" + summary + "\n" +
    editor + "\n" + std::to_string(artNumber);
}