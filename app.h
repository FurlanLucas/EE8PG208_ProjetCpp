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
#include <dirent.h>
#include "library.h"
#include "media/media.h"
#include "user/user.h"
#include "user/client.h"
#include "user/adm.h"

// Constant definitions --------------------------------------------------------
#define USERS_DIRNAME "userData"   // Folder name to be loaded (users' data)


class app {

// Class member variables
private:
    //user *cUser;
    library *cLibrary;       // Currant library that is been used
    library *loadedLibrary;  // Loaded library with all items
    user *cUser;             // Current user logged
    bool isLogged; // Boolean variable to control if there is a user logged


// ----------------------------------------------------------------------------
// Class member functions
public:
    app(void);                       // Class constructor
    ~app();                      // Class destructor
    int takeItem(void);              // Take
    int menu(void);                  // Execute the menu (main part)
    int search(void);                // Search for un item in the library
    void showItemDescription(void);  // Show an item's description
    int login();                     // Login of an user

};


#endif