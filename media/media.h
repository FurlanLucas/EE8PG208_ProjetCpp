#ifndef SOURCE_H
#define SOURCE_H

#include <string>

class media {

// Public attribures for the class
protected:
  int reference; // Reference code for the item in the general lybrary
  std::string autor; // Autor's name
  std::string title; // Item'a name
  int addDate; // Item's date of addition (general library)
  int year; // Item's year of production/written/recording
  int totalNumber; // Total number of this item in the library
  int dispNumber; // Total number of this item that are available.

// Public methods for the class
public:
  media();
  media(int reference_, std::string autor_, std::string title_,
          int addDate_, int year_, int totalNumber_, int dispNumber_);
  void showTotalNumber();
  void showDispNumber();
  void displayDate();
  void addItem();
  void removeItem();
  void lendItem();
  void returnItem();
  int getDispNumber();
  int getTotalNumber();
  virtual void showData();
  std::string getAutor();
  std::string getTitle();
  int getReference();
  int searchFor(std::string toSearch);

};

#endif
