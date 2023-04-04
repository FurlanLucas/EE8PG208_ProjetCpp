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
#include <windows.h> 
#include "library.h"
#include "media/media.h"
#include "user/user.h"
#include "user/client.h"
#include "user/adm.h"

// Constant definitions --------------------------------------------------------
#define USERS_DIRNAME "userData"   // Folder name to be loaded (users' data)
#define ERROR_COLOR 4              // Color displayed in error messages
#define LOGIN_COLOR 2             // Display color for login (windons.h)
#define LOGOUT_COLOR 4             // Display color for logout (windons.h)


class app {

// Class member variables
private:
    //user *cUser;
    library *cLibrary;       // Currant library that is been used
    library *loadedLibrary;  // Loaded library with all items
    library *userItems;      // User landed items (loaded from file)
    user *cUser;             // Current user logged
    bool isLogged; // Boolean variable to control if there is a user logged
    bool isAdm;    // Boolean to check if it is a adm logged;7
    HANDLE  hConsole;        // To handle the display

// ----------------------------------------------------------------------------
// Class member functions
public:
    app(void);                       // Class constructor
    ~app();                          // Class destructor
    int menu(void);                  // Execute the menu (main part)

private:
    void displayMenuOptions(void);   // Display all possible options
    int search(void);                // Search for un item in the library
    void showItemDescription(void);  // Show an item's description
    int login(void);                 // Login of an user    
    void logout(void);               // Login of an user
    int takeItem(void);              // Take an item for a user
    void showMyItems(void);          // Function to show all items of a client
    void showClients(void);          // Show all clients in the currant library
    void displayInvalidChoice(void); // Display the text of a invalid choice
    void loadClientsItems(void);     // Load the client items base in int array
    int newUser(void);               // Function that creates a new user
    int newClientUser(void);         // Function that creates a new client
    int newAdmUser(void);            // Function that creates a new adm
};


#endif