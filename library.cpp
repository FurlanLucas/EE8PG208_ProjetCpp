#include "library.h"


library::library(){
  itemsNumber = 0;
  items = new media;
}


int library::loadItems(){
  // Variable declarions
  DIR *folder;
  struct dirent *cfile; // pointer for the currant file in the directory
  folder = opendir(DIRNAME); // Open all files in the directory

  // Count the total number of items to load
  itemsNumber = 0;
  while ((cfile = readdir(folder)) != NULL){itemsNumber++;}
  itemsNumber = itemsNumber - 2;
  items = new media[itemsNumber];

  // If it is possible to opfile the directory
  if (folder) {
    // Reset the pointer to the first file
    rewinddir(folder); cfile = readdir(folder); cfile = readdir(folder);

    // Opfile each one of the files and charges the info
    for(int i = 0;(cfile = readdir(folder)) != NULL; i++) {
      std::string fileName = (std::string)DIRNAME + "/" +
                             (std::string)cfile->d_name;
      items[i] = *itemFromFile(fileName);
    }
    closedir(folder); //close all directory
    return 0;
  }
  else {
    return 1;
  }
}


media *library::itemFromFile(std::string fileName){
  // Variables
  std::ifstream myfile; // txt file to be open
  char itemType; // type of the item to be read
  int reference; // item's code of reference
  std::string autor; // autor
  std::string title; // item's name
  int addDate; // Item's inclusion date
  int year; // Item's year of creation
  int totalNumber; // total number of this item
  int dispNumber; // number of this item available
  int pagesNumber; // number of book pages
  std::string collection; // Name of the collection
  std::string editor; // editor's name
  std::string summary; // breaf summary of the book/magazine
  int artNumber; // Number of articles in a magazine
  std::string production; // Productors' name
  int timeDuration; // Time duration (min)
  int trackNumber; // Number of tracks in DVD/CD
  std::string format; // format of the digital ressource;
  std::string link; // Link for the digital ressource;
  int size; // Size of the online ressource;

  // Open and read the first line
  myfile.open(fileName);
  if (myfile.is_open()) {
    myfile >> itemType;
    myfile >> reference;
    myfile.ignore(1, '\n'); getline(myfile, autor);
    getline(myfile, title);
    myfile >> addDate;
    myfile >> year;
    myfile >> totalNumber;
    myfile >> dispNumber;

    switch(itemType){
      case('b'):
        myfile >> pagesNumber;
        myfile.ignore(1, '\n'); getline(myfile, collection);
        getline(myfile, editor);
        getline(myfile, summary);
        return new book(reference,autor,title,addDate,year,totalNumber,
          dispNumber,pagesNumber,collection,editor,summary);

      case('m'):
        myfile >> pagesNumber;
        myfile.ignore(1, '\n'); getline(myfile, collection);
        getline(myfile, editor);
        getline(myfile, summary);
        myfile >> artNumber;
        return new magazine(reference,autor,title,addDate,year,totalNumber,
          dispNumber,pagesNumber,collection,editor,summary,artNumber);

      case('C'):
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        myfile >> trackNumber;
        return new CD(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production,trackNumber);

      case('d'):
        myfile.ignore(1, '\n'); getline(myfile, format);
        myfile >> size;
        myfile.ignore(1, '\n'); getline(myfile, link);
        return new digital(reference,autor,title,addDate,year,totalNumber,
          dispNumber,format,size,link);

      case('V'):
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        return new VHS(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production);

      case('D'):
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        myfile >> trackNumber;
        return new DVD(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production,trackNumber);
    }
    myfile.close();
  }
  return 0;
}


int library::addItem(){
  try{
    // create the new element (test)
    media newElement = *itemFromFile("items/favor.txt");
    addItem(&newElement);
    return 0;
  }
  catch(int myNumber){
    std::cout << "Error appending the new value." << std::endl;
    return 1;
  }
}


int library::addItem(media *itemToAdd){
  itemsNumber++; // increment the number of items in the library
  media *newList = new media[itemsNumber]; // create a new list of items

  for(int i=0; i<itemsNumber-1; i++)
    newList[i] = items[i];

  try{

    items = newList;
    items[itemsNumber-1] = *itemToAdd;
    return 0;
  }
  catch(int myNumber){
    std::cout << "Error appending the new value." << std::endl;
    return 1;
  }
}


void library::showItems(){
  std::cout << "  N    Reference  \t Title \t\t\t\t\t Autor" <<
            "\t\t\t\t        Number \t\t Type" << std::endl;
  for(int i=0; i<itemsNumber;i++){
    std::string title = items[i].getTitle() + "                             " +
                                              "                             " ;
    std::string autor = items[i].getAutor() + "                             " +
                                              "                             " ;
    std::cout << " [" << i+1 << "]\t"<< items[i].getReference() << "\t" <<
      title.substr(0, 40) << "\t" << autor.substr(0, 40) << "   " <<
      items[i].getDispNumber() << "/" << items[i].getTotalNumber() << "\t\t" <<
      typeid(items[i]).name() << std::endl;
  }

  std::cout << "\n\n";
}


library *library::search(std::string nameToSearch){
  // Creat a library for the results
  library *results = new library;

  // Search in currant library the matches
  for(int i=0; i<itemsNumber; i++){
    // if it is fund, add the item to results
    if(items[i].searchFor(nameToSearch)){
      std::cout << "ITEM FOUND\n\n";
      results->addItem(&items[i]);
    }
  }

  // Return results
  return results;
}
