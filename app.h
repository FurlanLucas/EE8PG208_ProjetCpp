// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
//
// Created by Lucas (new version)
// -----------------------------------------------------------------------------

#ifndef APP_H // Header include check
#define APP_H

// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include "library.h"
#include "media/media.h"

class app {

// Class member variables
protected:
    //user *cUser;
    library *cLibrary;       // Currant library that is been used
    library *loadedLibrary;  // Loaded library with all items

    

// ----------------------------------------------------------------------------
// Class member functions
public:
    app(void);                       // Class constructor
    int takeItem(void);              // Take
    int menu(void);                  // Execute the menu (main part)
    int search(void);                // Search for un item in the library
    void showItemDescription(void);  // Show an item's description

};


#endif