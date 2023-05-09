#include "library.h"


library::library(std::string folderName) 
    // Class constructor, initialize the attributes with zeros items inside.
    : dirName(folderName){    
    items = *new std::vector<media*> (0);
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

    // If it is possible to opfile the directory
    if (!folder) {
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::loadItems(void)' function in " << __FILE__ << ".\n" <<
            "\tIt was not possible to open the directory." << std::endl;
        return 1;
    }

    // Count the total number of items to load
    int itemsNumber = 0;
    while ((cfile = readdir(folder)) != NULL){ itemsNumber++; }
    itemsNumber = itemsNumber - 2;  // Will not take the '.' and '..'

    // Check the number of number of items
    if (itemsNumber>MAXITEMS){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::loadItems(void)' function in " << __FILE__ << ".\n" <<
            "\tImpossible to load files: number of items exceed the " <<
            "maximum possible.\n" << std::endl;
        return 1;
    }

    // Items in the object will be overwrited
    items = *new std::vector<media*> (itemsNumber);

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
    // This function is used at 'loadItems()', not for public use. If it was 
    // possible to load the item, returns media pointer. If any problem has
    // occured, return a null pointer.

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
    std::string format;     // Format of the digital ressource
    std::string link;       // Link for the digital ressource
    int size;               // Size of the online ressource

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
            dispNumber,pagesNumber,collection,summary,editor);
  
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
    std::cout << "\nLine " << __LINE__ << ": Error executing 'media *" << 
            "library::itemFromFile(std::string fileName)' function in " << 
            __FILE__ << ".\nIt was not possible to open the file.\n";
    return NULL;
}


int library::addItem(media *itemToAdd, bool toSave){
    // Function to add an item to the library. Recives a 'media' pointer to be
    // added and returns 0 if the item was sucessfully added or 1 if any problem
    // ocurred. This function is to intern use only, for external (user) item
    // append, use the addItem(void). The boolean variable toFIle controls
    // whenever the media item to be added will be saved in the respective
    // directory.

    // Try to append the new value
    try{
        items.insert(items.end(), itemToAdd);
        if(toSave){
            if(!toFile(itemToAdd)){
                std::cout << "\nLine " << __LINE__ << ": Error executi" << 
                "ng 'int library::addItem(media *itemToAdd)' function in " << 
                 __FILE__ << ".\n\tCould not append the new value.\n";
                return 1;
            }
        }
        return 0;
    }
    catch(int error){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::addItem(media *itemToAdd)' function in " << __FILE__ << 
            ".\n\tCould not append the new value." << std::endl;
        return 1;
    }
}


int library::addItem(int itemToIncrease){
    // Function to add an item (wich already exist) to the library. It
    // will return 1 if any error ocurred (given by the function toFile).

    items[itemToIncrease]->addItem();
    return toFile(items[itemToIncrease]);
}


void library::showItems(void){
    // Function to display main item information for all items in the library,
    // (any user may call).

    if(items.size()==0){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'void " << 
            "library::showitems(void)' function in " << __FILE__ << 
            ".\n\tIt is not possible to show items within a empty library.\n";
        return;
    }

    // Label display
    std::cout << "\n\n  N \t Reference \t Title \t\t\t\t\t\t\t Autor \t\t\t\t\t" <<
        "Number \t Year \t Type" << std::endl;

    // Item display
    int i = 1;
    for(media *element : items){
        std::string title = element->getTitle() +
            "                                                              " ;
        std::string author = element->getAuthor() +
            "                                                              " ;
        std::string type = typeid(*element).name();
        std::cout << " [" << i++ << "] \t "<< element->getReference() << " \t "
          << title.substr(0, CAR_TITLE) << " \t " << author.substr(0, CAR_AUTHOR)
          << " \t" << element->getDispNumber() << "/" << element->getTotalNumber()
          << " \t " << element->getYear() << " \t " << type.substr(1, 8) << "\n";
    }

    std::cout << "\n\n";
}


library *library::search(std::string nameToSearch){
    // Function to search an item. Recives a string 'nameToSearch' to search for 
    // and returns a library pointer to an new object made of the results. That
    // makes a new research possible within the previous results. If no result is,
    // found it return a library with 0 elements in side, then it is necessary to 
    // check the result.

    // Creat a library for the results
    library *results = new library;

    size_t pos = 0;
    std::string token;
    while ((pos = nameToSearch.find(STRING_DELIM)) != std::string::npos) {
        token = nameToSearch.substr(0, pos);
        std::cout << token << std::endl;
        nameToSearch.erase(0, pos + 1); // pos + delimiter.length()
        
        // Search in currant library the matches
        for(media *element : items){
            // if it is fund, add the item to results
            if(element->searchFor(token))
                results->addItem(element);
        }
    }
    
    // Search in currant library the matches
    for(media *element : items){
        // if it is fund, add the item to results
        if(element->searchFor(nameToSearch))
            results->addItem(element);
    }

    return results; // Return results
}


int library::getItemsNumber(void){
    // Function to get the currant itemsNumber variable.
    return items.size();
}


int library::save(void){
    // Function to save each item in the library to a separate txt file. The function
    // will return 0 if it was sucessfully executed and 1 if it was not.

    for (int i=0; i<items.size(); i++){
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
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::toFile(media *item)' function in " << __FILE__ << 
            ".\nFile " << fileName << " could not be opened." << std::endl;
        return 1;
    }

    // Write to the out file   
    outFile << item->getFileInfo() << std::endl;

    // Output return
    outFile.close();
    return 0;
}


int library::lendItem(int itemToLend){
    // Function to lend the item. Returns 1 if any error has ocurred.
    // If it was not possible to lend the item because there is no more
    // items avaible, it returns -1;

    if(items[itemToLend]->lendItem()){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::lendItem(int itemToLend) function in" << __FILE__ << 
            " file.\nIt was not possible to lend an item.\n";
        return -1;
    }

    if(toFile(items[itemToLend])){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::lendItem(int itemToLend) function in" << __FILE__ << 
            " file.\nIt was not possible to save the item lended.\n";
        return 1;
    }

    return 0;
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
    for(media *element : items){
        // Search of the item
        for(int i=1; i<=maxItems; i++){
            // Test if the item is required
            if(element->getReference()==refInputs[i]){

                // Tries to append the required item
                if(myPartition->addItem(element)){
                    std::cout << "\nLine " << __LINE__ << ": Error executin" << 
                    "g 'int library::lendItem(int itemToLend)' function in" 
                    << __FILE__ << " .\n\tIt was not possible to append" <<
                    " item" << std::endl;
                    return NULL;
                }

            }
        }
      
    }

    return myPartition;
}


int library::deleteItem(int itemToRemove){
    // Function that removes an item from the current. Returns -1 if a error
    // has occurred. Return 1 if it is not possible to remove the item
    // (if there is any copy with a client).

    if(items[itemToRemove]->getDispNumber()!=items[itemToRemove]->getTotalNumber())
        return 1;

    // Remove the file
    std::string fileName = dirName + "/" + 
        std::to_string(items[itemToRemove]->getReference()) + 
        "_" +  items[itemToRemove]->getTitle().substr(0, CAR_TITLE_TXT) +  "_" + 
        items[itemToRemove]->getAuthor().substr(0, CAR_AUTHOR_TXT) + ".txt";
    if(remove(fileName.c_str())){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'libr" << 
            "ary::removeItem(int itemToRemove)' function in " << __FILE__ << 
            ".\n\tIt was not possible to remove the items file." << std::endl;
        return -1;
    }

    // Try to remove the item
    try{
        items.erase(items.begin()+itemToRemove);
    }
    catch(int erro){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'libr" << 
            "ary::removeItem(int itemToRemove)' function in " << __FILE__ << 
            ".\n\tIt was not possible to remove the item." << std::endl;
        return -1;
    }

    return 0;
}


int library::removeItem(int itemToRemove){
    // Function that removes an item from the current. Returns -1 if a error
    // has occurred. Return 1 if it is not possible to remove the item.

    if(items[itemToRemove]->getDispNumber()<1)
        return 1;

    // Try to remove the item
    items[itemToRemove]->removeItem();
    
    // Save to the file
    if(toFile(items[itemToRemove])){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::lendItem(int itemToLend) function in" << __FILE__ << 
            " file.\nIt was not possible to save the item lended.\n";
        return 1;
    }

    return 0;
}


int library::getItemsReference(int item){
    // Function that returns an item reference code. If there is not this
    // in the library, returns -1.

    if(item >= items.size())
        return -1;

    return items[item]->getReference();
}


int library::getPositionByReference(int reference){
    // Function that returns an item position in library by the reference.
    // If no item was found, return -1.

    for(int i=0; i<items.size();i++){
        if(items[i]->getReference() == reference)
            return i;
    }

    return -1;
}


int library::getLendsNumber(int item){
    // Function that returns the number of lends for an item
    return items[item]->getTotalNumber() - items[item]->getDispNumber();
}


void library::returnItem(int item){
    // Function to return a item from a user.
    items[item]->returnItem();

    // Save to the file
    if(toFile(items[item])){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "library::lendItem(int itemToLend) function in" << __FILE__ << 
            " file.\nIt was not possible to save the item lended.\n";
        return;
    }
} 