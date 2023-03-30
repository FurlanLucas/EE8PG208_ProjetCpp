#include <iostream>
#include "media/media.h"
#include "library.h"

int main(){
  std::cout << "Initializing main...\n";
  library myLibrary;

  // Try to load the library
  // Load files
  if(!myLibrary.loadItems()) {
    std::cout << "Loaded sucessfully " << myLibrary.getItemsNumber() <<
      " items." << std::endl;
  }
  else{
    std::cout << "Failled to load files." << std::endl;
  }

  // Show the items
  myLibrary.showItems(); 
  myLibrary.addItem();
  myLibrary.showItems();

  // Do a research
  library * results = myLibrary.search("Introduction");
  results->showItems();

  library *results2 = results->search("loads");
  results2->showItems();

  // Save all items
  if(!myLibrary.save()) {
    std::cout << "Save sucessfully " << myLibrary.getItemsNumber() <<
      " items." << std::endl;
  }
  else{
    std::cout << "Failled to save files." << std::endl;
  }
}
