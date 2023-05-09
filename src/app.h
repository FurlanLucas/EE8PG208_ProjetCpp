// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
//
// Created by Lucas (new version)
// -----------------------------------------------------------------------------

#ifndef APP_H // Header include check
#define APP_H

// Includes --------------------------------------------------------------------
#include <chrono>
#include <conio.h>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h> 
#include "library.h"
#include "../lib/media/DVD.h"
#include "../lib/media/book.h"
#include "../lib/media/CD.h"
#include "../lib/media/digital.h"
#include "../lib/media/magazine.h"
#include "../lib/media/VHS.h"
#include "../lib/media/media.h"
#include "../lib/user/user.h"
#include "../lib/user/client.h"
#include "../lib/user/adm.h"

// Constant definitions --------------------------------------------------------
#define USERS_DIRNAME "../userData"  // Folder name to be loaded (users' data)
#define MAX_USERS 1000               // Max number of users to be loaded
#define ERROR_COLOR 4                // Color displayed in error messages
#define LOGIN_COLOR 2                // Display color for login (windons.h)
#define CONFIRMATION_COLOR 3         // Color for confirmation (attention) text
#define LOGOUT_COLOR 5               // Display color for logout (windons.h)
#define ATT_COLOR 5                  // Attention color (target library only)
#define CHAR_IGNORE 10000            // Characters to ignore after a cin read
#define SYMBOLS_PASSWORD "~`!@#$%^&*()_-+={[}]|:;'<,>.?/" // Symbols permited
#define MINIMUM_CHAR_PASSWORD 10     // Minimum number of characters in a password
#define HIDEN_CHAR '*'               // Character to be displayed in hiden password
#define ELAPSED_UPDATE_TIME_S 60*1   // Minimum elapsed time for an update

class app {

// Class member variables
private:
    //user *cUser;
    library *cLibrary;           // Currant library that is been used
    library *loadedLibrary;      // Loaded library with all items
    library *userItems;          // User landed items (loaded from file)
    std::vector<user*> allUsers; // Save all clients in the library
    user *cUser;                 // Current user logged
    bool isLogged; // Boolean variable to control if there is a user logged
    bool isAdm;                  // Boolean to check if it is a adm logged
    bool toBreak;                // Boolean variable to break the menu option
    HANDLE  hConsole;            // To handle the display
    std::chrono::time_point<std::chrono::system_clock> start;  // Start time 
    std::chrono::time_point<std::chrono::system_clock> lastUp; // Last update

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
    void showUsers(void);            // Show all users in the currant library
    void displayInvalidChoice(void); // Display the text of a invalid choice
    int newUser(void);               // Function that creates a new user
    int newClientUser(void);         // Function that creates a new client
    int newAdmUser(void);            // Function that creates a new adm
    int loadUsers(void);             // Function to load all user data
    int addItem(void);               // Function to create an item from user data
    int takeIntChoice(void);         // Function to receive the option from user
    std::string takeSingleInfo(std::string informationName, bool isInt = false);
    std::string takeSecretPassword(std::string informationName); // See doc.
    void forgotPassword(void);       // Function to reset a user password
    void removeItem(void);           // Function to remove an item
    void removeClient(void);         // Function to remove a client
    void returnItem(void);           // Function to return an item
    int update(void);                // Function to update the loaded library

};

#endif