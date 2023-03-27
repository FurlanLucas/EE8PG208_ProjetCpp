#include "book.h"

book::book(int reference_, std::string autor_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
  std::string collection_, std::string summary_, std::string editor_)
  : media{reference_,autor_,title_,addDate_,year_,totalNumber_,dispNumber_}
  , pagesNumber(pagesNumber_)
  , collection(collection_)
  , editor(editor_)
  , summary(summary_){

}

void book::showData(){
  // Function to display all the important info in class (for debug only).
  std::cout << "This item (code " << reference << ") is a " << year <<
  " book by " << autor << " called \"" << title << "\",\npublished by " <<
  editor << " with " << pagesNumber << " pages. " << summary << ".\n";
};
