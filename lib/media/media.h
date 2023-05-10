// Media main class for library software implementation. Presented at Bordeaux
// INP at EE8PG208 Projet C++.
//
// Created by Lucas Furlan
// -----------------------------------------------------------------------------

#ifndef SOURCE_H
#define SOURCE_H

#include <string>
#include <iostream>

class media {

// Atributes for the class -----------------------------------------------------
protected:
    int reference;      // Reference code for the item in the general lybrary
    std::string author; // Autor's name
    std::string title;  // Item'a name
    int addDate;        // Item's date of addition (general library)
    int year;           // Item's year of production/written/recording
    int totalNumber;    // Total number of this item in the library
    int dispNumber;     // Total number of this item that are available.

// Methodes for the class ------------------------------------------------------
public:
    // Constructors
    media();
    media(int reference_, std::string author_, std::string title_,
          int addDate_, int year_, int totalNumber_, int dispNumber_);

    // Get member methods
    int getDispNumber(void);     // Get the available number
    int getTotalNumber(void);    // Get the total number of the article
    std::string getAuthor(void); // Get the autor's name
    std::string getTitle(void);  // Get the title's name
    int getReference(void);      // Get the code referece
    int getYear(void);           // Get the year of the items creation/production

    // For user methods
    void addItem(void);     // Add a new item (increase the totalNumber)
    int  removeItem(void);  // Remove a item (decrease the totalNumber)
    int  lendItem(void);    // Lend a item to a user (decrease the dispNumber)
    void returnItem(void);  // Return a item (increase the dispNumber)

    // Virtual methods
    virtual void showData(void){}; // Show data in the class (for children imp.)  
    virtual int searchFor(std::string toSearch); // Search for a name in the class info.
    virtual std::string getFileInfo(void); // Get the important file infos to save

protected:
    std::string toLowercase(std::string inputString); // Transform to lowecase

};

#endif
