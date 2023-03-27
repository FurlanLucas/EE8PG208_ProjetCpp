#include "library.h"


library::library(void){
  // Class constructor, initialize the attributes with zeros items inside
  itemsNumber = 0;
  items = new media;
}


int library::loadItems(void){
  // Load items to the library if the total number of items to be read is less
  // than MAXITEMS defined in the header. This function overwrite all items
  // that were inside. The function will return 0 if the files were sucessfully
  // loaded and 1 in any other case.

  // Variable declarions
  DIR *folder;               // Folter variable to be loaded (see dirent.h)
  struct dirent *cfile;      // Pointer for the file in *folder (see dirent.h)
  folder = opendir(DIRNAME); // Open all files in the directory

  // Count the total number of items to load
  itemsNumber = 0;   // Items in the object will be overwrited
  while ((cfile = readdir(folder)) != NULL){itemsNumber++;}
  itemsNumber = itemsNumber - 2;  // Will not take the '.' and '..'

  // Check the number of number of items
  if (itemsNumber>MAXITEMS){
    std::cout << "That was not possible to load files: number of items " <<
      "exceed the maximum possible." << std::endl;
    return 1;
  }
  items = new media[itemsNumber]; // Create the new media pointer

  if (folder) { // If it is possible to opfile the directory
    // Reset the pointer to the first file and ignore '.' and '..'
    rewinddir(folder); cfile = readdir(folder); cfile = readdir(folder);

    // Open each one of the files and charges the info
    for(int i = 0;(cfile = readdir(folder)) != NULL; i++) {
      std::string fileName = (std::string)DIRNAME + "/" +
                             (std::string)cfile->d_name;
      items[i] = *itemFromFile(fileName);
    }
    closedir(folder); //close all directory
    return 0;
  }
  else { // If it was not possible to open the folder
    std::cout << "It was not possible to open the directory " << DIRNAME <<
      std::endl;
    return 1;
  }
}


media *library::itemFromFile(std::string fileName){
  // Function that creates a media pointer to a item loaded from 'fileName'.
  // This function is used at 'loadItems()', not for public use.

  // Possible variables to be loaded
  std::ifstream myfile;   // txt file to be open
  char itemType;          // Type of the item to be read
  int reference;          // Item's code of reference
  std::string autor;      // Autor
  std::string title;      // Ttem's name
  int addDate;            // Item's inclusion date
  int year;               // Item's year of creation
  int totalNumber;        // Total number of this item
  int dispNumber;         // Number of this item available
  int pagesNumber;        // Number of book pages
  std::string collection; // Name of the collection
  std::string editor;     // Editor's name
  std::string summary;    // Breaf summary of the book/magazine
  int artNumber;          // Number of articles in a magazine
  std::string production; // Productors' name
  int timeDuration;       // Time duration (min)
  int trackNumber;        // Number of tracks in DVD/CD
  std::string format;     // Format of the digital ressource;
  std::string link;       // Link for the digital ressource;
  int size;               // Size of the online ressource;

  // Open the file
  myfile.open(fileName);

  // Check if the folder was open
  if (myfile.is_open()) {
    myfile >> itemType; // Read the item type (first line)
    myfile >> reference; // Read the reference code (int)
    myfile.ignore(1, '\n'); getline(myfile, autor); // Read the autors name
    getline(myfile, title); // Read title
    myfile >> addDate; // Read the addition date
    myfile >> year; // Read the items year of creation
    myfile >> totalNumber; // Read the total number
    myfile >> dispNumber; // Read the available number

    // Check the type of file (first letter)
    switch(itemType){
      case('b'): // If it is a book
        myfile >> pagesNumber;
        myfile.ignore(1, '\n'); getline(myfile, collection);
        getline(myfile, editor);
        getline(myfile, summary);
        return new book(reference,autor,title,addDate,year,totalNumber,
          dispNumber,pagesNumber,collection,editor,summary);

      case('m'): // If it is a magazine
        myfile >> pagesNumber;
        myfile.ignore(1, '\n'); getline(myfile, collection);
        getline(myfile, editor);
        getline(myfile, summary);
        myfile >> artNumber;
        return new magazine(reference,autor,title,addDate,year,totalNumber,
          dispNumber,pagesNumber,collection,editor,summary,artNumber);

      case('C'): // If it is a CD
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        myfile >> trackNumber;
        return new CD(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production,trackNumber);

      case('d'): // If it is a digital ressource
        myfile.ignore(1, '\n'); getline(myfile, format);
        myfile >> size;
        myfile.ignore(1, '\n'); getline(myfile, link);
        return new digital(reference,autor,title,addDate,year,totalNumber,
          dispNumber,format,size,link);

      case('V'): // If it is a VHS
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        return new VHS(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production);

      case('D'): // If it is a DVD
        myfile >> timeDuration;
        myfile.ignore(1, '\n'); getline(myfile, production);
        myfile >> trackNumber;
        return new DVD(reference,autor,title,addDate,year,totalNumber,
          dispNumber,timeDuration,production,trackNumber);
    }

    myfile.close(); // Close the txt file
  }

  // If it was not possible to open the file
  std::cout << "It was not possible to open the " << fileName << " file.\n";
  return NULL;
}


int library::addItem(void){
  // Function to add a item to the library for a user.
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
  // Function to add an item to the library. Recives a 'media' pointer to be
  // added and returns 0 if the item was sucessfully added or 1 if any problem
  // ocurred. This function is to intern use only, for external (user) item
  // append, use the addItem(void).

  itemsNumber++; // Increment the number of items in the library
  media *newList = new media[itemsNumber]; // Create a new list of items

  // Copie all the old variables to the new vector
  for(int i=0; i<itemsNumber-1; i++)
    newList[i] = items[i];

  // Try to append the new value
  try{
    items = newList; // Replace the media pointer
    items[itemsNumber-1] = *itemToAdd; // Add the new item
    return 0;
  }
  catch(int error){
    std::cout << "Error appending the new value." << std::endl;
    return 1;
  }
}


void library::showItems(void){
  // Function to display main item information for all items in the library,
  // (any user may call).

  // Label display
  std::cout << "  N    Reference  \t Title \t\t\t\t\t Autor" <<
            "\t\t\t\t        Number \t\t Type" << std::endl;

  // Item display
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
  // Function to search an item. Recives a string 'name' to search for and
  // returns a library pointer to an new object made of the results. That makes
  // a new research possible within the previous results. If no result is found,
  // it return a library with 0 elements in side, then it is necessary to check
  // the result.

  // Creat a library for the results
  library *results = new library;

  // Search in currant library the matches
  for(int i=0; i<itemsNumber; i++){
    // if it is fund, add the item to results
    if(items[i].searchFor(nameToSearch))
      results->addItem(&items[i]);
  }

  return results; // Return results
}


int library::getItemsNumber(){
  // Function to get the currant itemsNumber variable.
  return itemsNumber;
}
