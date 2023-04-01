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
#define ITEMS_DIRNAME "items"   // Folder name to be loaded
#define MAXITEMS 2000           // Max number of items in the library
#define CAR_TITLE 50            // Number of characters to display the item's name
#define CAR_AUTHOR 30           // Number of characters to display the item's author
#define CAR_TITLE_TXT 15        // Number of title characters present in file name
#define CAR_AUTHOR_TXT 10       // Number of author characters present in file name

class library {

// Class member variables
private:
  int itemsNumber; // Number of items in the library
  media **items;   // Pointer to a media obeject that point to the first item
  std::string dirName; // Name of the folder that contains the items


// ----------------------------------------------------------------------------
// Class member functions
public:
  library(void);                    // Constructor
  library(std::string folderName);  // Constructor if another folder name
  int addItem(void);                // Function to add item from a user input
  int getItemsNumber(void);         // Get the current items number
  library *search(std::string nameToSearch); // Search for a word or expression
  void showItems(void);             // Show all items in the library
  int save(void);             // Save all the items to the database in txt files
  int loadItems(void);              // Load items from a file
  int removeItem(int itemToRemove); // Function that removes an item
  int lendItem(int itemToLend);     // Function that lends an item
  void showItemDes(int itemToShow); // Function that returns an specific item

private:
  media * itemFromFile(std::string fileName); // Create a item from a fileName
  int toFile(media *item);                    // Save a item to a file
  int addItem(media *itemToAdd);              // Add a item to the library
};

#endif
