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
  int loadItems();
  int displayItems();
  //void getDispNumber();
  media * search(std::string fileName);
  int addItem();
  void showItems();

private:
  media * itemFromFile(std::string fileName);
};

#endif
