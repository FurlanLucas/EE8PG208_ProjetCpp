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

// Constant definitions --------------------------------------------------------
#define CAR_NAME_TXT 10          // Number of name/surname character to save


class user {

// Class member variables
protected:
    std::string name;
    std::string surName;
    std::string email;
    std::string password;
    int reference;

// ----------------------------------------------------------------------------
// Class member functions
public:
    user(void);                         // Class constructor
    user(std::string nom, std::string prenom, std::string login,
        std::string password_, int reference_);
    std::string getName(void);          // Get user's name
    std::string getSurName(void);       // Get user's surname
    std::string getEmail(void);         // Get email
    int getReference(void);             // Get user reference
    int checkID(std::string email_, std::string password_); // Check credentials
    virtual int *getAttributes(void);
    virtual int save(std::string dirName); // Function to save the user info 
    virtual int returnItem(int reference);

protected:
    std::string toUpperCase(std::string inputString);
};


#endif