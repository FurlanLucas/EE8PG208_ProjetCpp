#ifndef LIBRARY_H
#define LIBRARY_H

#define DIRNAME "items"
#define MAXITEMS 2000

#include <string>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include <vector>
#include <typeinfo>
#include "media/DVD.h"
#include "media/book.h"
#include "media/CD.h"
#include "media/digital.h"
#include "media/magazine.h"
#include "media/VHS.h"

class library {
public:
  int itemsNumber;
  media * items;

public:
  library();
  int loadItems();
  int displayItems();
  int addItem();
  void showItems();
  library *search(std::string nameToSearch);
  
private:
  media * itemFromFile(std::string fileName);
  int addItem(media *itemToAdd);
};

#endif
