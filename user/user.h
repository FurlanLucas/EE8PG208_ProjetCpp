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
    user();
    user(std::string nom, std::string prenom, std::string login);
    std::string getName();
    std::string getSurName();
    std::string getEmail();
    int checkID(std::string email_, std::string password_);

};


#endif