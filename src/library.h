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
#include <vector>
#include <typeinfo>
#include "../lib/media/DVD.h"
#include "../lib/media/book.h"
#include "../lib/media/CD.h"
#include "../lib/media/digital.h"
#include "../lib/media/magazine.h"
#include "../lib/media/VHS.h"

// Constant definitions --------------------------------------------------------
#define ITEMS_DIRNAME "../items"   // Folder name to be loaded
#define MAXITEMS 2000           // Max number of items in the library
#define CAR_TITLE 50            // Number of characters to display the item's name
#define CAR_AUTHOR 30           // Number of characters to display the item's author
#define CAR_TITLE_TXT 15        // Number of title characters present in file name
#define CAR_AUTHOR_TXT 10       // Number of author characters present in file name

class library {

// Class member variables
private:
    std::string dirName; // Name of the folder that contains the items
    std::vector<media*> items; // Vector of media pointers
    
// ----------------------------------------------------------------------------
// Class member functions
public:
    library(std::string folderName=ITEMS_DIRNAME); // Constructor with folder name
    int getItemsNumber(void);         // Get the current items number
    int lendItem(int itemToLend);     // Function that lends an item
    int loadItems(void);              // Load items from a file
    int save(void);             // Save all the items to the database in txt files
    library *search(std::string nameToSearch); // Search for a word or expression
    library *partition(int *refInputs); // Take a part of the library given by ref.
    void showItems(void);             // Show all items in the library
    void showItemDes(int itemToShow); // Function that returns an specific item
    int removeItem(int itemToRemove); // Removes an item 
    int deleteItem(int itemToRemove); // Removes an item 
    int addItem(media *itemToAdd, bool toSave=false);    // Add a new item
    int addItem(int itemToIncrease);   // Add a exist item (increase num.)
    int getItemsReference(int item);   // Function that returns an item ref.
    int getPositionByReference(int reference); // Returns the item position
    int getLendsNumber(int item);      // Get the number of lends
    void returnItem(int item);         // Return one item by a user
private:  
    media * itemFromFile(std::string fileName); // Create a item from a fileName
    int toFile(media *item);                    // Save a item to a file
  
};

#endif
