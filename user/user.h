// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
//
// Created by Moussa
// Edited by Lucas (new version)
// -----------------------------------------------------------------------------

#ifndef USER_H // Header include check
#define USER_H

// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>

class user {

// Class member variables
protected:
    std::string name;
    std::string surName;
    std::string email;
    std::string password;

// ----------------------------------------------------------------------------
// Class member functions
public:
    user();                 // Class constructor
    user(std::string nom, std::string prenom, std::string login,
        std::string password_);
    std::string getName();          // Get user's name
    std::string getSurName();       // Get user's surname
    std::string getEmail();         // Get email
    int checkID(std::string email_, std::string password_); // Check credentials
    virtual int *getAttributes(void);

protected:
    std::string toUpperCase(std::string inputString);
};


#endif