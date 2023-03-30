// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef LIBRARY_H // Header include check
#define LIBRARY_H

// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include <typeinfo>
#include "media/DVD.h"
#include "media/book.h"
#include "media/CD.h"
#include "media/digital.h"
#include "media/magazine.h"
#include "media/VHS.h"

// Constant definitions --------------------------------------------------------
#define DIRNAME "items" // Folder name to be loaded
#define MAXITEMS 2000   // Max number of items in the library
#define CAR_TITLE 50    // Number of characters to display the item's name
#define CAR_AUTHOR 30   // Number of characters to display the item's author

class library {
// Class member variables

private:
  int itemsNumber; // Number of items in the library
  media * items;   // Pointer to a media obeject that point to the first item


// ----------------------------------------------------------------------------
// Class member functions

public:
  library(void);             // Constructor
  int addItem(void);         // Function to add item from a user input
  int getItemsNumber(void);  // Get the current items number
  int loadItems(void);       // Load items from a file
  library *search(std::string nameToSearch); // Search for a word or expression
  void showItems(void);      // Show all items in the library
  int save(void);            // Save all the items to the database in txt files

private:
  media * itemFromFile(std::string fileName); // Create a item from a fileName
  int toFile(media *item);                    // Save a item to a file
  int addItem(media *itemToAdd);              // Add a item to the library
};

#endif
