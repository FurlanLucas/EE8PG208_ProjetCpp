#include <iostream>
#include "media/media.h"
#include "library.h"

int main(){
  std::cout << "Initializing main...\n\n";
  library myLibrary;

  if(!myLibrary.loadItems()) {
    std::cout << "Loaded sucessfully " << myLibrary.getItemsNumber() <<
      " items." << std::endl;
  }
  else{
    std::cout << "failled to load files." << std::endl;
  }
  myLibrary.showItems(); // Show the items

  // Add a new item and show
  myLibrary.addItem();
  myLibrary.showItems(); // Show the items


  // Do a research
  library * results = myLibrary.search("Introduction");
  results->showItems();

  library *results2 = results->search("loads");
  results2->showItems();

}
