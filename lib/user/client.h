// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++. The itemsLendedRef variable stores the reference code
// for all items that a client have taken. It is an array of n+1 variables, with
// n been the number of borows and the first element of the array is the number n:
//
//  itemsLendedRef[0] = n
//  itemsLendedRef[1] = 1st item reference
//  itemsLendedRef[2] = 2nd item reference
//         ...
//  itemsLendedRef[n+1] = nth item reference
//
// Created by Moussa
// Edited by Lucas (new version)
// -----------------------------------------------------------------------------

#ifndef CLIENT_H // Header include check
#define CLIENT_H

// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include "user.h"

class client : public user {

// Class member variables
protected:
    int *itemsLendedRef;     // Reference for each item took;

// ----------------------------------------------------------------------------
// Class member functions
public:
    client();
    client(std::string name, std::string surName, std::string email,
        std::string password_);
    client(std::string fileName);
    int *getAttributes(void);
};


#endif