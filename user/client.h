// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
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
    int numberOfLends;      // Number of items that the client took
    int **itemsReference;     // Reference for each item took;

// ----------------------------------------------------------------------------
// Class member functions
public:
    client(std::string name, std::string surName, std::string email);
    client(std::string fileName);
};



#endif