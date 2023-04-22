// Library class for library software implementation. Presented at Bordeaux INP
// at EE8PG208 Projet C++
//
// Created by Moussa
// Edited by Lucas (new version)
// -----------------------------------------------------------------------------

#ifndef ADM_H // Header include check
#define ADM_H

// Includes --------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include "user.h"

class adm : public user {

// Class member variables
protected:


// ----------------------------------------------------------------------------
// Class member functions
public:
    adm(std::string name, std::string surName, std::string email,
        std::string password_, int reference_);
    adm(std::string fileName);
    void showClientsInfo(void);
};



#endif