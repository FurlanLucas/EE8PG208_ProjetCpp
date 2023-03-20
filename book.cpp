#include <iostream>
#include "book.h"

book::book(int reference_, std::string autor_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
  std::string colletion_, std::string summary_, std::string editor_)
  :sources{reference_,autor_,title_,addDate_,year_,totalNumber_,dispNumber_}{

  pagesNumber = pagesNumber_,
  collection = colletion_,
  editor = editor_,
  summary = summary_;
}

void book::showData(){
  std::cout << "This item (code " << reference << ") is a " << year <<
  " book by " << autor << " called \"" << title << "\", published by " <<
  editor << " with " << pagesNumber << " pages. " << summary << ".\n";
};
