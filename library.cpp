#include "library.h"


library::library(void) 
    : dirName(ITEMS_DIRNAME)
    , itemsNumber(0) {
    // Class constructor, initialize the attributes with zeros items inside.
    items = new media*; 
}


library::library(std::string folderName) 
    : dirName(folderName)
    , itemsNumber(0) {
    // Class constructor, initialize the attributes with zeros items inside.
    items = new media*; 
}


int library::loadItems(void){
    // Load items to the library if the total number of items to be read is less
    // than MAXITEMS defined in the header. This function overwrite all items
    // that were inside. The function will return 0 if the files were sucessfully
    // loaded and 1 in any other case.

    // Variable declarions
    DIR *folder;               // Folter variable to be loaded (see dirent.h)
    struct dirent *cfile;      // Pointer for the file in *folder (see dirent.h)
    folder = opendir(dirName.c_str()); // Open all files in the directory

    if (!folder) {// If it is possible to opfile the directory
        std::cout << "Error in 'library::loadItems(void)' function. " << 
            "It was not possible to open the directory " << dirName <<
            "." << std::endl;
        return 1;
    }

    // Count the total number of items to load
    itemsNumber = 0;   // Items in the object will be overwrited
    while ((cfile = readdir(folder)) != NULL){ itemsNumber++; }
    itemsNumber = itemsNumber - 2;  // Will not take the '.' and '..'

    // Check the number of number of items
    if (itemsNumber>MAXITEMS){
        std::cout << "Error in 'library::loadItems(void)' function. " << 
            "Impossible to load files: number of items " <<
            "exceed the maximum possible." << std::endl;
        return 1;
    }
    items = new media*[itemsNumber];

    // Reset the pointer to the first file and ignore '.' and '..'
    rewinddir(folder); cfile = readdir(folder); cfile = readdir(folder);

    // Open each one of the files and charges the info
    for(int i = 0;(cfile = readdir(folder)) != NULL; i++) {
        std::string fileName = dirName + "/" + (std::string)cfile->d_name;
          items[i] = itemFromFile(fileName);
    }
    closedir(folder); //close all directory
    return 0;

}


media *library::itemFromFile(std::string fileName){
    // Function that creates a media pointer to a item loaded from 'fileName'.
    // This function is used at 'loadItems()', not for public use.

    // Possible variables to be loaded
    std::ifstream myfile;   // txt file to be open
    char itemType;          // Type of the item to be read
    int reference;          // Item's code of reference
    std::string author;     // Autor
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
        myfile.ignore(1, '\n'); getline(myfile, author); // Read the autors name
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
            return new book(reference,author,title,addDate,year,totalNumber,
            dispNumber,pagesNumber,collection,editor,summary);
  
        case('m'): // If it is a magazine
            myfile >> pagesNumber;
            myfile.ignore(1, '\n'); getline(myfile, collection);
            getline(myfile, editor);
            getline(myfile, summary);
            myfile >> artNumber;
            return new magazine(reference,author,title,addDate,year,totalNumber,
                dispNumber,pagesNumber,collection,editor,summary,artNumber);

        case('C'): // If it is a CD
            myfile >> timeDuration;
            myfile.ignore(1, '\n'); getline(myfile, production);
            myfile >> trackNumber;
            return new CD(reference,author,title,addDate,year,totalNumber,
                dispNumber,timeDuration,production,trackNumber);

        case('d'): // If it is a digital ressource
            myfile.ignore(1, '\n'); getline(myfile, format);
            myfile >> size;
            myfile.ignore(1, '\n'); getline(myfile, link);
            return new digital(reference,author,title,addDate,year,totalNumber,
                dispNumber,format,size,link);

        case('V'): // If it is a VHS
            myfile >> timeDuration;
            myfile.ignore(1, '\n'); getline(myfile, production);
            return new VHS(reference,author,title,addDate,year,totalNumber,
                dispNumber,timeDuration,production);

        case('D'): // If it is a DVD
            myfile >> timeDuration;
            myfile.ignore(1, '\n'); getline(myfile, production);
            myfile >> trackNumber;
            return new DVD(reference,author,title,addDate,year,totalNumber,
               dispNumber,timeDuration,production,trackNumber);
        }

        myfile.close(); // Close the txt file
    }

    // If it was not possible to open the file
    std::cout << "Error in 'library::itemFromFile(std::string fileName)'" << 
        "function. It was not possible to open the " << fileName << " file.\n";
    return NULL;
}


int library::addItem(void){
    // Function to add a item to the library. Creates another vector of items and
    // replaces the old one.

    try{
        // create the new element (test)
        media newElement = *itemFromFile("items/favor.txt");
        addItem(&newElement);
        return 0;
    }
    catch(int myNumber){
        std::cout << "Error in 'library::addItem(void)' function. " << 
            "Could not append the new value." << std::endl;
        return 1;
    }
}


int library::addItem(media *itemToAdd){
    // Function to add an item to the library. Recives a 'media' pointer to be
    // added and returns 0 if the item was sucessfully added or 1 if any problem
    // ocurred. This function is to intern use only, for external (user) item
    // append, use the addItem(void).

    itemsNumber++; // Increment the number of items in the library
    media **newList = new media*[itemsNumber]; // Create a new list of items

    // Copie all the old variables to the new vector
    for(int i=0; i<itemsNumber-1; i++){
        newList[i] = items[i];
    }

    // Try to append the new value
    try{
        items[itemsNumber-1] = itemToAdd; // Add the new item
        delete[] newList;
        return 0;
    }
    catch(int error){
        std::cout << "Error in 'library::addItem(media *itemToAdd)' function. " << 
            "Could not append the new value." << std::endl;
        delete[] newList;
        return 1;
    }
}


void library::showItems(void){
    // Function to display main item information for all items in the library,
    // (any user may call).

    if(itemsNumber==0){
        std::cout << "Error in 'library::showitems(void)' function. " << 
            "It is not possible to show items within a empty library.\n";
        return;
    }

    // Label display
    std::cout << "\n\n  N \t Reference \t Title \t\t\t\t\t\t\t Autor \t\t\t\t\t" <<
        "Number \t Year \t Type" << std::endl;
    

    // Item display
    for(int i=0; i<itemsNumber;i++){
        std::string title = items[i]->getTitle() +
        "                                                              " ;
        std::string author = items[i]->getAuthor() +
        "                                                              " ;
        std::string type = typeid(*(items[i])).name();
        std::cout << " [" << i+1 << "] \t "<< items[i]->getReference() << " \t "
          << title.substr(0, CAR_TITLE) << " \t " << author.substr(0, CAR_AUTHOR)
          << " \t" << items[i]->getDispNumber() << "/" << items[i]->getTotalNumber()
          << " \t " << items[i]->getYear() << " \t " << type.substr(1, 8) << "\n";
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
        if(items[i]->searchFor(nameToSearch))
          results->addItem(items[i]);
    }

    return results; // Return results
}


int library::getItemsNumber(void){
    // Function to get the currant itemsNumber variable.
    return itemsNumber;
}


int library::save(void){
    // Function to save each item in the library to a separate txt file. The function
    // will return 0 if it was sucessfully executed and 1 if it was not.

    for (int i=0; i<itemsNumber; i++){
        // Check if a file has not been saved correctly
        if(toFile(items[i])){
            std::cout << "Error in 'library::save(void)' function. " <<
            "It was not possible to save the " << i << "th item." << std::endl;
            return 1;
        }
    }

    // If it reaches that line, all items were well saved.
    return 0;
}


int library::toFile(media *item){
    // Function that saves a item in a file. Recives a pointer to a item that is to
    // be saved in a txt format and returns 0 if the item was sucessfully saved or 
    // 1 if it was not.

    // Item file name
    std::string fileName = dirName + "/" + std::to_string(item->getReference()) + 
        "_" +  item->getTitle().substr(0, CAR_TITLE_TXT) +  "_" + 
        item->getAuthor().substr(0, CAR_AUTHOR_TXT);

    // Out file  
    std::ofstream outFile;
    outFile.open(fileName + ".txt");

    // Check if the file has been opened
    if(!outFile){
        std::cout << "Error in 'library::toFile(media *item)' function. "
            "File " << fileName << " could not be opened." << std::endl;
        return 1;
    }

    // Write to the out file   
    outFile << item->getFileInfo() << std::endl;

    // Output return
    return 0;
}


int library::removeItem(int itemToRemove){
    // This function creates a new items list of medias without a especific
    // item given by its positin in the corrent library, i.e. "itemToRemove". 
    // Returns 0 if the function was executed sucessfully or 1 if it was not.

    // Check it the item existes
    if (itemToRemove>itemsNumber-1){
        std::cout << "Error in 'library::removeItem(int itemToRemove)'" << 
            " function. There is no item n. " << itemToRemove << 
            " in the library." << std::endl;
        return 1;
    }

    // Creates the new vector
    itemsNumber--;
    media **newList = new media*[itemsNumber]; // Create a new list of items

    // Removes the file from the current directory
    std::string fileName = dirName + "/" + 
        std::to_string(items[itemToRemove]->getReference()) + "_" +  
        items[itemToRemove]->getTitle().substr(0, CAR_TITLE_TXT) +  "_" + 
        items[itemToRemove]->getAuthor().substr(0, CAR_AUTHOR_TXT) + ".txt";
    if(remove(fileName.c_str()) != 0){
        std::cout << "Error in 'library::removeItem(int itemToRemove)'" << 
            " function. It was not possible to remove the file." << std::endl;
        return 1;
    }

    // Copy all items to the new array
    try{
        int j=0;
        for(int i=0; i<itemsNumber+1; i++){
            if(i==itemToRemove)
                continue;
            newList[j] = items[i];
            j++;
        }
        items = newList;
        delete[] newList;
    }
    catch(int error){
        std::cout << "Error in 'library::removeItem(int itemToRemove)'" << 
            " function. It was not possible to copy the library." << std::endl;
        return 1;
    }

    // Ending
    return 0;
}


int library::lendItem(int itemToLend){
    if(!items[itemToLend]->lendItem())
        return 0;
    else{
        std::cout << "Error in 'library::lendItem(int itemToLend)'" << 
            " function. There are no more articles available." << std::endl;
        return 1;
    }
}


void library::showItemDes(int itemToShow){
    // This function just returns display the description of an item
    items[itemToShow]->showData();
}


library *library::partition(int *refInputs){
    // This function take a part of the current library and returns
    // as a library pointer. The

    // Declares the new library
    library *myPartition = new library;
    int maxItems = refInputs[0];

    // Search in the library
    for(int i=0; i<itemsNumber; i++){
        // Search of the item
        for(int j=1; j<=maxItems; j++){
            // Test if the item is required
            if(items[i]->getReference()==refInputs[j]){

                // Tries to append the required item
                if(myPartition->addItem(items[i])){
                    std::cout << "Error in 'library::partition(int *refInputs)'" << 
                        " function. It was not possible to append item." << std::endl;
                    return NULL;
                }

            }
        }
      
    }

    return myPartition;
}