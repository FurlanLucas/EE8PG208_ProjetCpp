#include "app.h"


app::app(void)
    : toBreak(false)
    , isLogged(false)
    , isAdm(false) {

    // First displays
    std::cout << "\nInitializing application." << std::endl;
    loadedLibrary = new library;
    cLibrary = new library;

    // Tries to initialize
    if(loadedLibrary->loadItems()){
        std::cout << "Error loading files. Exiting." << std::endl;
        exit(1);
    }
    else{
        std::cout << "All " << loadedLibrary->getItemsNumber() << 
            " items were loaded sucessfully." << std::endl;
    }

    // User initialization
    loadUsers();

    // Setting console collor attribute
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
}


app::~app(void){
    // Check if was someone logged in
    if (isLogged)
        logout();

    SetConsoleTextAttribute(hConsole, 15); // Sets the cmd to normal mode

    std::cout << "Thank you for using our application." << std::endl;
    std::cout << "Exiting application." << std::endl;
}


int app::menu(void){
    // Main menu for the application. It takes the user option and controls
    // the other functions that will be called. Returns 0 if the application
    // were executed sucessfully ou 1 if it was not.

    while(!toBreak){
        // Menu printing
        displayMenuOptions();

        // Take the option and check if it is a valid integer number
        int option = takeIntChoice();

        // Main option
        switch (option) {
        case 1: // [1] Search for an item
            search();
            break;

        case 2: // [2] Show all items
            loadedLibrary->showItems();
            break;

        case 3: // [3] Show an item description
            showItemDescription();
            break;

        case 4: // [4] Lend item
            takeItem();
            break;

        case 5: // [5] Return to general library
            cLibrary = new library;
            break;

        case 6: // [6] Logout/Login
            if (isLogged)
                logout();
            else
                login();            
            break;

        case 7: // [7] Display clients info / Show my items / creates an accout
            if(isLogged && isAdm)
                showClients();
            else if(isLogged && !isAdm)
                showMyItems(); 
            else if(!isLogged)
                newUser();
            else
                displayInvalidChoice();
            break;

        case 9:
            createItem();
            break;

        case 12: // [12] Exit 
            toBreak = true;
            break;

        default:            
            displayInvalidChoice();
            break;
        }
    }

    // Exit the menu (after while)
    std::cout << "Exiting menu." << std::endl;
    return 0; 
}


void app::displayMenuOptions(void){
    // Function that display all possible choices in application menu.
    // Void function.


    std::cout << "\nList of commands:" << std::endl;
    std::cout << " [1] Search for an item" << std::endl;
    std::cout << " [2] Show all items" << std::endl;
    std::cout << " [3] Show items description" << std::endl;        
    std::cout << " [4] Lend item" << std::endl;                
    std::cout << " [5] Return to general library" << std::endl;

    if (isLogged){
        std::cout << " [6] Logout" << std::endl;

        // Options for adms
        if(isAdm){
            std::cout << " [7] Display clients info" << std::endl;
            std::cout << " [8] Return un item" << std::endl;
            std::cout << " [9] Add item" << std::endl;
            std::cout << "[10] Remove item" << std::endl;            
            std::cout << "[11] Remove cliet" << std::endl;
        }

        // Options for clients
        else{
            std::cout << " [7] Show my items" << std::endl;            
        }
    }
    else{
        std::cout << " [6] Login" << std::endl;
        std::cout << " [7] Create an account" << std::endl;
    }
         
    // Final options
    std::cout << "[12] Exit" << std::endl;
    std::cout << "\nEnter your option: ";
}


int app::search(void){
    // Function to saerch un item in the current library. It returns 0 if
    // no problems ocurred or 1 if the execution was forced to stop at any
    // time. If the  current library is empty (zero items inside), the
    // research is done in the loaded general library. If it is not empty,
    // the research is done in current library. In both cases, current library
    // is replaced by the result of the actual research.

    // Creates the library for the results
    library *results;

    // Display the instruction
    std::cout << "Enter with a name to search for: ";

    // Take the string to search for
    std::string toSearch;
    std::getline(std::cin, toSearch);    
    std::cin.clear();

    // Verify in which library it has to search for  
    //library* results = cLibrary->getItemsNumber() ? cLibrary : loadedLibrary;
    //library* results;

    // Search for the item and show the results
    try{  
        if (cLibrary->getItemsNumber())
            results = cLibrary->search(toSearch);
        else
            results = loadedLibrary->search(toSearch);

        // Verify if there was any result
        if(results->getItemsNumber()){
            std::cout << "\nShowing " << results->getItemsNumber() << 
                " results." << std::endl;
            cLibrary = results;
            cLibrary->showItems();
        }
        else{
            std::cout << "No items were found." << std::endl;
        }
    }
    catch(int errorN){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::search(void)' function in " << __FILE__ << ".\n\tIt is not"
            " possible to show items within a empty library.\n";
        delete results;
        toBreak = true;
        return 1;
    }

    delete results;
    return 0;
}


void app::showItemDescription(void){
    // Function that display an specific item description. It just calls the
    // showItemDes function of library class.
    
    // Display the instruction
    std::cout << "Enter with the item to display: ";

    // Take the string to search for
    int toDisplay;
    std::cin >> toDisplay;
    std::cout << "\n";

    // Check if the command is to the currant library or the loaded one
    if(cLibrary->getItemsNumber()!=0){
        // Ckeck if the choice is possible
        if(toDisplay<cLibrary->getItemsNumber())
            cLibrary->showItemDes(toDisplay-1);
        else
            std::cout << "There is no such item in current library.\n";
    }
    else{
        if(toDisplay<loadedLibrary->getItemsNumber())
            loadedLibrary->showItemDes(toDisplay-1);
        else
            std::cout << "There is no such item in current library.\n";
    }
}


int app::login(void){
    // Function to make the login of an user. Returns 0 if the loggin
    // ocurred sucessfully or 1 if it did not.

    // Take the user's email
    std::string email;
    std::cout << "Enter with your e-mail: ";
    std::cin >> email;

    // Take the user's password
    std::string password;
    std::cout << "Enter with your password: ";
    std::cin >> password;

    // Search for the information within the users data
    for (int i=0;i<allUsers.size();i++) {

        // Check if it is the correct ID;
        if (allUsers[i]->checkID(email, password)) {
            cUser = allUsers[i];
            std::cout << "Welcome back " << cUser->getSurName(); 
            std::cout << "! You are now ";
            SetConsoleTextAttribute(hConsole, LOGIN_COLOR);
            std::cout << "logged in";    
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "." << std::endl;
            isLogged = true; 

            // Check if it is an adm
            std::string type = typeid(*(allUsers[i])).name();
            if (type.find("adm")!=std::string::npos)
                isAdm = true;

            return 0;
        }

    }

    // If it reachs this point, no user were found
    std::cout << "User not found." << std::endl;
    isAdm = false;
    return 0;
}


int app::takeItem(void){
    // Function to lend an item from the library. It requires a user loggin. The
    // function will return 0 if it was executed correctly or 1 if any problem
    // have ocurred. If the current library is empty, the choice is made within
    // the general loaded library.

    // Check if a user is logged in
    if (!isLogged){
        std::cout << "For lend an item, a login is needed." << std::endl;
        login();
    }


    // Show items
    if(cLibrary->getItemsNumber()==0)
        loadedLibrary->showItems();
    else
        cLibrary->showItems();

    // Take the users choice
    std::cout << "Which item do you want to take? ";
    int itemNumber = takeIntChoice();
    itemNumber--;

    // Confirms the choice
    std::cout << "You want to lend the following item:\n\n";
    if(cLibrary->getItemsNumber()==0)
        loadedLibrary->showItemDes(itemNumber);
    else
        cLibrary->showItemDes(itemNumber);
    std::cout << "Press 1 to confirm or 0 to return to menu: ";
    int confirmation;
    std::cin >> confirmation;
    if(!confirmation)
        return 0;

    // Take the item
    if(cLibrary->getItemsNumber()==0){
        if(!loadedLibrary->lendItem(itemNumber))
            return 0;
        else{
            std::cout << "An error ocurred trying to lend an item." << std::endl;
            return 1;
        }
    }
    else{
        if(!cLibrary->lendItem(itemNumber))
            return 0;
        else{
            std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::takeItem(void)' function in " << __FILE__ << ".\nIt was " <<
            "not possible to lend an item.\n";
            return 1;
        }
    }
}


void app::showMyItems(void){
    // Function to show all current items of a client. It first load
    // all client items based in the reflist (array of int) defined
    // in client class.

    loadClientsItems();
    std::cout << "You have currently those items: \n" << std::endl;
    userItems->showItems();
}


void app::loadClientsItems(void){
    // Function to load the client's items. It takes the list of items
    // presented in the clients source file (ref code) and creates a
    // partition in the loaded library. See 'partition' in 'lybrary.cpp'
    // for more info
    
    int *refList = cUser->getAttributes();
    userItems = loadedLibrary->partition(refList);
}


void app::showClients(void){
    // Function to show all clients in the library

    std::cout << "\tName \t Surname \t Code" << std::endl;
    // Search for the information within the users data
    int j = 0;
    for (int i=0;i<allUsers.size();i++) {  
        // Take the type of user    
        std::string type = typeid(*(allUsers[i])).name();

        // Check wether it ios client
        if(type.find("client")!=std::string::npos){                   
            std::cout << "[" << ++j << "]\t" << allUsers[i]->getSurName() <<  
                '\t' << allUsers[i]->getName() << '\t' << std::endl;                   
        }        
    }


    // Menu option
    int localBreak = false;
    while(!localBreak){
        // Display options
        std::cout << "\n\n";
        std::cout << "List of commands:" << std::endl;
        std::cout << " [1] Delete client" << std::endl;
        std::cout << " [2] Change client info" << std::endl;
        std::cout << " [3] Return to main menu" << std::endl;
        std::cout << "[12] Exit" << std::endl;
        std::cout << "\nEnter your option: ";
        
        // Take user choice
        int localOption = takeIntChoice();

        switch(localOption){
        case 1:
            return;
        case 2:
            return;
        case 3:
            return; 
        case 12:
            toBreak = true;
            return;          
        default:            
            displayInvalidChoice();
            break;
        }
    }
}


void app::displayInvalidChoice(void){
    // Function to display the massega of invalid choice type. Changes
    // temporally the display color. It doesent return anything.

    SetConsoleTextAttribute(hConsole, ERROR_COLOR);
    std::cout << "Invalid type";    
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << ". If you want to exit the application," <<
        " tap 12. " << std::endl;
}


void app::logout(void){
    // Function to logout a user. Set the attributes to non logged mode.  

    isLogged = false;
    isAdm = false;

    // Printing
    std::cout << "By " << cUser->getSurName();
    std::cout << ". You are now ";
    SetConsoleTextAttribute(hConsole, LOGOUT_COLOR);
    std::cout << "logged out";    
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "." << std::endl;

    //delete cUser;
}


int app::newUser(void){
    // Function that creates a new user. Returns 0 if it was executed
    // sucessfully or 1 it it was not.

    // Check if there is someone logged
    if(isLogged && isAdm){
        int choice;
        std::cout << "Do you want to create a new adm user? " <<
            "Enter [1] for yes and [2] for no." << std::endl;
        std::cin >> choice;
        switch (choice){
        case 1: // There is an adm connected an it wants a new adm account
            newAdmUser();
            return 0;
        
        case 2: // There is an adm connected an it wants a new client account
            logout();
            break;

        default:
            displayInvalidChoice();
            return 1;
        }
    }
    else if (isLogged && !isAdm) // There is a client connected
        logout();
    

    newClientUser();
    
    return 0;
}


int app::newClientUser(void){
    // Function to creates a new client user. Takes all information that is needed
    // in the std::cin.

    std::string name;
    std::string surname;
    std::string email;
    std::string password;

    std::cout << "Enter your name (without surname): ";
    std::cin >> name;
    std::cout << "Enter your surname: ";
    std::cin >> surname;    
    std::cout << "Enter your email: ";
    std::cin >> email;

    try{
        cUser = new client(name, surname, email, password);
    }
    catch(int error){
        std::cout << "Error in 'app::newCLientUser(void)' function. " <<
            "Impossible to creat a new client class." << std::endl;
        return 1;
    }
    return 0;
}


int app::newAdmUser(void){
    return 0;
}


int app::loadUsers(void){
    // Load users to the app if the total number of items to be read is less
    // than MAX_USERS defined in the header. This function overwrite all users
    // that were inside. The function will return 0 if the files were sucessfully
    // loaded and 1 in any other case.

    // Variable declarions
    DIR *folder;               // Folter variable to be loaded (see dirent.h)
    struct dirent *cfile;      // Pointer for the file in *folder (see dirent.h)
    folder = opendir(USERS_DIRNAME); // Open all files in the directory
    
    // Count the total number of items to load
    int usersNumber = 0;
    while ((cfile = readdir(folder)) != NULL){ usersNumber++; }
    usersNumber = usersNumber - 2;  // Will not take the '.' and '..'

    // Check the number of number of items
    if (usersNumber> MAX_USERS){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::loadUsers(void)' function in " << __FILE__ << ".\n" <<
            "\tImpossible to load files: number of users exceed the " <<
            "maximum possible.\n" << std::endl;
        return 1;
    }

    // Items in the object will be overwrited
    allUsers = *new std::vector<user*> (usersNumber);

    // Reset the pointer to the first file and ignore '.' and '..'
    rewinddir(folder); cfile = readdir(folder); cfile = readdir(folder);

    // Open each one of the files and charges the info
    for(int i = 0;(cfile = readdir(folder)) != NULL; i++) {
        std::string fileName = (std::string) USERS_DIRNAME + "/" + 
            (std::string) cfile->d_name;
        if(fileName.find("client")!=std::string::npos){
            allUsers[i] = new client(fileName);
        }
        else if(fileName.find("adm")!=std::string::npos){
            allUsers[i] = new adm(fileName);
        }

    }
    closedir(folder); //close all directory    
    return 0;
}


int app::createItem(void){
    // Function that creates a new item to be add to the current library. Returns
    // 1 if it was executed sucessfully and 0 in any other case. The creation is a
    // while loop in each information, been possible to rewrite the last attribute
    // or even return to the previous attribute. The local menu, with localOption
    // and localBreak does not interfere in the global menu (option and toBreak).

    // Variable declaration
    int localOption;               // Takes the option for the menu display (local)
    bool localBreak = false;       // Controls the while loop for the menu (local)
    int reference;                 // Item's code of reference
    std::string author;            // Autor
    std::string title;             // Ttem's name
    int addDate;                   // Item's inclusion date
    int year;                      // Item's year of creation
    int totalNumber;               // Total number of this item
    int pagesNumber;               // Number of book pages
    std::string collection;        // Name of the collection
    std::string editor;            // Editor's name
    std::string summary;           // Breaf summary of the book/magazine
    int artNumber;                 // Number of articles in a magazine
    std::string production;        // Productors' name
    int timeDuration;              // Time duration (min)
    int trackNumber;               // Number of tracks in DVD/CD
    std::string format;            // Format of the digital ressource
    std::string link;              // Link for the digital ressource
    int size;               // Size of the online ressource
    media * newItem;               // New item to be added

    // Take the main information (commum for all items / media attributes)
    reference = std::stoi(takeSingleInfo("item's code reference", true));
    if(reference == 0) return 0; // Check for return option
    author = takeSingleInfo("author's name(s)");
    if(author == "0") return 0; // Check for return option
    title = takeSingleInfo("item's title");
    if(title == "0") return 0; // Check for return option
    addDate = 12;
    year = std::stoi(takeSingleInfo("item's year of creation"));
    if(year == 0) return 0; // Check for return option
    totalNumber = std::stoi(takeSingleInfo("avaiable number"));
    if(totalNumber == 0) return 0; // Check for return option

    // ------------------------------------------------------------
    while(!localBreak){
        // Display options of item
        std::cout << "\n\n";
        std::cout << "Which item do you want to create ?" << std::endl;
        std::cout << "[1] Book" << std::endl;
        std::cout << "[2] Magazine" << std::endl;
        std::cout << "[3] CD" << std::endl;
        std::cout << "[4] digital" << std::endl;
        std::cout << "[5] VHS" << std::endl;
        std::cout << "[6] DVD" << std::endl;
        std::cout << "\nEnter your option: ";

        // Chose the type of the item to be created
        localOption = takeIntChoice();
        
        // If the choice is valid, jumps to the next part
        if(localOption < 7 && localOption > 0){
            localBreak = true;
        }
    }

    // -------------------------------------------------------------
    switch(localOption){
    case 1: // Will create a book
        pagesNumber = std::stoi(takeSingleInfo("pages number"));
        if(pagesNumber == 0) return 0; // Check for return option
        collection = takeSingleInfo("collection");
        if(collection == "0") return 0; // Check for return option
        editor = takeSingleInfo("editor");
        if(editor == "0") return 0; // Check for return option
        summary = takeSingleInfo("summary");
        if(summary == "0") return 0; // Check for return option
        newItem = new book(reference, author, title, addDate, year,
            totalNumber, totalNumber, pagesNumber, collection, summary, editor);
        break;
    case 2: // Will create a magazine
        pagesNumber = std::stoi(takeSingleInfo("pages number"));
        collection = takeSingleInfo("collection");
        editor = takeSingleInfo("editor");
        summary = takeSingleInfo("summary");
        artNumber = std::stoi(takeSingleInfo("number of articles"));
        newItem = new magazine(reference, author, title, addDate, year,
            totalNumber, totalNumber, pagesNumber, collection, summary, editor, 
            artNumber);
        break;
    case 3: // Will create a CD
        timeDuration = std::stoi(takeSingleInfo("time duration"));
        production = takeSingleInfo("collection");
        trackNumber = std::stoi(takeSingleInfo("number of articles"));
        newItem = new CD(reference, author, title, addDate, year, totalNumber,
            totalNumber, timeDuration, production, trackNumber);
        break;
    case 4: // Will create a digital ressource        
        format = takeSingleInfo("format");
        size = std::stoi(takeSingleInfo("file size"));
        link = takeSingleInfo("link for the ressource");
        newItem = new digital(reference, author, title, addDate, year, totalNumber,
            totalNumber, format, size, link);
        break;
    case 5: // Will create a VHS
        timeDuration = std::stoi(takeSingleInfo("time duration"));
        production = takeSingleInfo("production");
        newItem = new VHS(reference, author, title, addDate, year, totalNumber,
            totalNumber, timeDuration, production);
        break;
    case 6: // Will create a DVD
        timeDuration = std::stoi(takeSingleInfo("time duration"));
        production = takeSingleInfo("production");
        trackNumber = std::stoi(takeSingleInfo("track number"));
        newItem = new DVD(reference, author,title, addDate, year, totalNumber,
            totalNumber, timeDuration, production, trackNumber);
        break;
    default:
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::createItem(void)' function in " << __FILE__ << ".\nIt was" <<
            " not possible to create a new item Impossible option was chosen.\n";
        return 1;
    }

    if(!loadedLibrary->addItem(newItem)){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::createItem(void)' function in " << __FILE__ << ".\nIt was" <<
            " not possible to append the item.\n";
        return 1;
    }
    
    // Ending
    loadedLibrary->addItem(newItem, true);
    std::cout << "Item created sucessfully. Tap 2 to show the items or seach for" <<
        "the item if the command 1.";
    return 0;
}


std::string app::takeSingleInfo(std::string informationName, bool isInt){
    // Function to take (and confirm) one information given by an user. It will
    // return the information in a std::string type. The boolean variabel
    // isInt controls if its mandatory for the input to be an integer type.
    // It is true and the input is no numeric, will ask for another input from
    // the user.

    // Variable declaration
    std::string information;
    bool localBreak = false;
    int localOption;

    while(!localBreak){
        
        // Display command
        std::cout << "Enter the " << informationName << " : ";
        std::getline(std::cin, information);    
        std::cin.clear();

        // Check if the input have to be an integer
        if(isInt && information.find_first_not_of("0123456789")!=std::string::npos){
            SetConsoleTextAttribute(hConsole, ERROR_COLOR);
            std::cout << "Erro";            
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << ": The input must be an integer.\n";
            continue;
        }

        bool insideLocalBreak = false;
        while(!insideLocalBreak){
            std::cout << "Entered " << informationName << " : ";
            SetConsoleTextAttribute(hConsole, CONFIRMATION_COLOR);
            std::cout << information << std::endl;            
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "\nDo you confirm the information ? " << std::endl;
            std::cout << " [1] Yes, continue" << std::endl;
            std::cout << " [2] No, undo the command" << std::endl;   
            std::cout << " [3] Cancel and return to main menu" << std::endl;    
            std::cout << "[12] Exit\n" << std::endl;
            std::cout << "Enter your option: ";

            localOption = takeIntChoice();

            switch (localOption){
                case 1:
                    insideLocalBreak = true;
                    localBreak  = true;
                    return information;
                case 2:
                    insideLocalBreak = true;
                    break;
                case 3:
                    std::cout << "Returning to main menu." << std::endl;
                    return "0";
                case 12:
                    toBreak = true;
                    return "0";
                default:
                    displayInvalidChoice();
                    break;
                }
        }
    }

    // Unreacheable line, error
    std::cout << "\nLine " << __LINE__ << ": Error executing 'std:" << 
            ":string app::takeSingleInfo(std::string informationNa" << 
            "me, bool isInt)' function in " << __FILE__ << ".\nIt " <<
            "was not possible to open the file." << std::endl;
    return NULL;
}


int app::takeIntChoice(void){
    // Function that takes an integer taped by the user. The function was
    // created to avoid code repetition, since the same lines were used
    // multiple times. Return the number taped by the user.

    int tapedOption;
    std::cin >> tapedOption;
    std::cin.clear();
    std::cin.ignore(CHAR_IGNORE, '\n');

    // Check if it is valid choice (integer)
    if(std::cin.fail()){
        displayInvalidChoice();
    }

    return tapedOption;
}