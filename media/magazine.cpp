#include <iostream>
#include "magazine.h"

magazine::magazine(int reference_, std::string autor_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
  std::string collection_, std::string summary_, std::string editor_,
  int artNumber_)
  : book{reference_, autor_, title_, addDate_, year_, totalNumber_, dispNumber_,
        pagesNumber_, collection_, summary_, editor_}
  , artNumber(artNumber_){
}

void magazine::showData(){
  std::cout << "This item (code " << reference << ") is a " << year <<
  " book by " << autor << " called \"" << title << "\",\npublished by " <<
  editor << " with " << pagesNumber << " pages. " << summary << ".\n";
};
