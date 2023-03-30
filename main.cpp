#include <iostream>
#include "media/media.h"
#include "library.h"

int main(){
  std::cout << "Initializing main...\n";
  library myLibrary;

  // Try to load the library
  if(!myLibrary.loadItems()) {
    std::cout << "Loaded sucessfully " << myLibrary.getItemsNumber() <<
      " items." << std::endl;
  }
  else{
    std::cout << "Failled to load files." << std::endl;
  }
  myLibrary.showItems(); 


  // Remove all items
  if(!myLibrary.removeItem(7)) {
    std::cout << "Removed sucessfully 1 items." << std::endl;
  }
  else{
    std::cout << "Failled to remove files." << std::endl;
  }
  myLibrary.showItems();


  // Do a research
  library * results1 = myLibrary.search("Introduction");
  results1->showItems();

  library *results2 = results1->search("loads");
  results2->showItems();


  // Save all items
  if(!myLibrary.save()) {
    std::cout << "Save sucessfully " << myLibrary.getItemsNumber() <<
      " items." << std::endl;
  }
  else{
    std::cout << "Failled to save files." << std::endl;
  }

  return 0;
}
