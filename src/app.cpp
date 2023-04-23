#include "app.h"


app::app(void)
    : toBreak(false)
    , isLogged(false)
    , isAdm(false) {

    // First displays
    system("CLS");
    std::cout << "Initializing application." << std::endl;
    loadedLibrary = new library;
    cLibrary = new library("NULL");

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
    delete loadedLibrary;
    delete cLibrary;
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
            system("CLS");
            loadedLibrary->showItems();
            break;

        case 3: // [3] Show an item description
            showItemDescription();
            break;

        case 4: // [4] Lend item
            takeItem();
            break;

        case 5: // [5] Return to general library
            system("CLS");            
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
                showUsers();
            else if(isLogged && !isAdm)
                showMyItems(); 
            else if(!isLogged)
                newUser();
            else
                displayInvalidChoice();
            break;

        case 8: // [8] Forgot my password / return an item
            if(!isLogged)
                forgotPassword();
            else if(isAdm)
                returnItem();
            else
                displayInvalidChoice();
            break;

        case 9: // [9] Create/add an item (adm use only)
            if(isLogged && isAdm)
                addItem();
            else
                displayInvalidChoice();
            break;
        
        case 10: // [10] Remove an item (adm use only)
            if(isLogged && isAdm)
                removeItem();
            else
                displayInvalidChoice();
            break;

        case 11: // [11] Remove client (adm use only)
            if(isLogged && isAdm)
                removeClient();
            else
                displayInvalidChoice();
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
    // Void function. Is there is any item in the current library, shows
    // it. Display also the library in process.

    // Display current library
    if(cLibrary->getItemsNumber())
            cLibrary->showItems();
    else{
        std::cout << "Working in "; 
        SetConsoleTextAttribute(hConsole, ATT_COLOR);
        std::cout << "general Library";
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << "." << std::endl;
    }

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
            std::cout << " [9] Add/create item" << std::endl;
            std::cout << "[10] Remove/delete item" << std::endl;            
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
        std::cout << " [8] Forgot my password" << std::endl;
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

    // Search for the item and show the results
    try{  

        if(cLibrary->getItemsNumber())
            results = cLibrary->search(toSearch);
        else
            results = loadedLibrary->search(toSearch);

        // Verify if there was any result
        system("CLS");
        if(results->getItemsNumber()){
            std::cout << "\nShowing " << results->getItemsNumber() << 
                " results." << std::endl;
            delete cLibrary;
            cLibrary = results;
        }
        else
            std::cout << "No items were found." << std::endl;     
    }
    catch(int errorN){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::search(void)' function in " << __FILE__ << ".\n\tIt is not"
            " possible to show items within a empty library.\n";
        toBreak = true;
        return 1;
    }

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
    std::string email = takeSingleInfo("email");
    if(email == "0") return 0; // Check if the user wants to quit

    // Take the user's password
    std::string password = takeSecretPassword("password");
    std::cout << std::endl;

    // Search for the information within the users data
    for (user *uElement : allUsers) {

        // Check if it is the correct ID;
        if (uElement->checkID(email, password)) {
            cUser = uElement;
            system("CLS");
            std::cout << "Welcome back " << cUser->getSurName(); 
            std::cout << "! You are now ";
            SetConsoleTextAttribute(hConsole, LOGIN_COLOR);
            std::cout << "logged in";    
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "." << std::endl;
            isLogged = true; 


            std::string type = typeid(*uElement).name();

            // Check if it is an adm            
            if (type.find("client")!=std::string::npos){
                int *refList = cUser->getAttributes();
                userItems = loadedLibrary->partition(refList);
            }

            // Check if it is an adm            
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

    // Variable declaration
    library* &target = (cLibrary->getItemsNumber()>0) ? cLibrary : loadedLibrary;
    bool localCheck = false;
    int localOption;
    int itemNumber;

    // Check if a user is logged in
    if (!isLogged){
        std::cout << "For lend an item, a login is needed." << std::endl;
        login();
    }
    
    while(!localCheck){
        // Take the users choice
        std::cout << "Which item do you want to take? ";
        itemNumber = takeIntChoice();
        itemNumber--;

        // Confirms the choice
        std::cout << "You want to lend the following item:\n\n";
        if(cLibrary->getItemsNumber()==0)
            loadedLibrary->showItemDes(itemNumber);
        else
            cLibrary->showItemDes(itemNumber);
        std::cout << "\nDo you confirme your choice?" << std::endl;
        std::cout << " [1] Yes" << std::endl;        
        std::cout << " [2] No, return to main menu" << std::endl;
        std::cout << "[12] Exit" << std::endl;
        std::cout << "\nEnter your choice: ";
        localOption = takeIntChoice();

        switch(localOption){
        case 1:
            localCheck = true;
            break;
        case 2:
            return 0;
        case 12:
            toBreak = true;
            return 0;
        default:
            displayInvalidChoice();
            break;
        }
    }

    // Check if it is possible to take the item
    if(itemNumber >= target->getItemsNumber() || itemNumber < 0){
        std::cout << "There is not such item in the library.\n";
        return 0;
    }

    // Check if the user already has this item
    int itemReference = target->getItemsReference(itemNumber);
    int pos = userItems->getPositionByReference(itemReference);
    if(pos>=0){
        system("CLS");
        std::cout << "You already have this item.\n";
        return 0;
    }

    // Take the item
    int out = target->lendItem(itemNumber);
    if(out==-1){
        system("CLS");
        std::cout << "We can not lend this item becaus there is not" <<
            " other units avaiable." << std::endl;
        return 0;
    }
    else if(out == 1){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
        "app::takeItem(void)' function in " << __FILE__ << " file.\nIt " <<
        " was not possible to lend an item." << std::endl;
        return 1;
    }

    system("CLS");
    std::cout << "You successfully took the item." << std::endl;
    return 0;
}


void app::showMyItems(void){
    // Function to show all current items of a client. It first load
    // all client items based in the reflist (array of int) defined
    // in client class.

    // Check if the user has items
    if(userItems->getItemsNumber() == 0){
        std::cout << "You currently do not have items. Go to 'lend item' in" << 
            " the main menu to lend an item." << std::endl;
        return;
    }

    // If there are items in the library
    std::cout << "You have currently those items: \n" << std::endl;
    userItems->showItems();
}


void app::showUsers(void){
    // Function to show all clients in the library

    std::cout << "\tName \t Surname \t Code" << std::endl;
    // Search for the information within the users data
    int j = 1;
    for (user *uElement : allUsers) {  
        // Take the type of user    
        std::cout << "[" << j++ << "]\t" << uElement->getSurName() <<  
            '\t' << uElement->getName() << '\t' << std::endl;                      
    }
    std::cout << std::endl;
}


void app::displayInvalidChoice(void){
    // Function to display the massage of invalid choice type. Changes
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

    system("CLS");

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
    // in the std::cin from user. All information is confirmed in takeSingleInfo,
    // but a check of return == "0" is done each time (see takeSingleInfo for more
    // information). Besides, an email existence and password security nivel check is
    // done.

    // Variable declaration
    bool emailPasswordCheckBreak = false;
    std::string name;
    std::string surname;
    std::string email;
    std::string password = "";
    std::string secondPassword;
    char a; // Char for hiden password input

    // Get name and surname from user
    name = takeSingleInfo("name (without surname)");
    if(name == "0") return 0; // Check if the user wants to quit
    surname = takeSingleInfo("surname");
    if(surname == "0") return 0; // Check if the user wants to quit

    // Get the email
    while(!emailPasswordCheckBreak){
        email = takeSingleInfo("email");
        if(email == "0") return 0; // Check if the user wants to quit

        // Check if the email is already registred
        for(int i=0; i<allUsers.size(); i++){
            if(allUsers[i]->getEmail() == email){
                std::cout << "This email is already registred. If you forgot"
                    << " your password, go to 'forgot my password' option.\n";
                break;
            }
            // If the email is avaiable
            if(i+1==allUsers.size())
                emailPasswordCheckBreak = true;
        }
    }

    // Get the password
    emailPasswordCheckBreak = false;
    while(!emailPasswordCheckBreak){
        // Take the password
        password = takeSecretPassword("password");
        std::cout << std::endl;

        // Check if the password is strong enough
        bool passwordSize = password.size() <= MINIMUM_CHAR_PASSWORD;
        bool notNum = password.find_first_of("0123456789")==std::string::npos;
        bool notSim = password.find_first_of(SYMBOLS_PASSWORD)==std::string::npos;
        bool notUper = true;
        bool notLower = true;
        for(char element : password){
            if(isupper(element)) notUper = false;
            if(islower(element)) notLower = false;
        }
        
        if(notNum || notSim || notUper || notLower || passwordSize){
            std::cout << "The password must have a number, a symbol ( " <<
                SYMBOLS_PASSWORD << " ), at least " << MINIMUM_CHAR_PASSWORD << 
                " characters, with one upper and lower case." << std::endl;
            continue;
        }
        
        // Gets the same password a second time (confirmation)
        secondPassword = takeSecretPassword("password again (confirmation)");
        std::cout << std::endl;
        if(secondPassword != password){
            std::cout << "The passwords must be identical." << std::endl;
            continue;
        }

        std::cout << std::endl;
        emailPasswordCheckBreak = true;
    }

    // Try to create the user (automatic login)
    try{        
        allUsers.push_back(new client(name, surname, email, password,
            allUsers.size()+1));
        cUser = allUsers[allUsers.size()-1];
        cUser->save(USERS_DIRNAME);
        userItems = new library("NULL");
        isLogged = true;
    }
    catch(int error){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::newClientUser(void)' function in " << __FILE__ << ".\n" <<
            "\tIt was not possible to create the new user." << std::endl;
        return 1;
    }

    // Try to save the user in dataBase
    try{
        // Code to be added
    }
    catch(int error){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::newClientUser(void)' function in " << __FILE__ << ".\n" <<
            "\tIt was not possible to save the user." << std::endl;
        return 1;
    }

    // Ending
    std::cout << "User created successfully. Welcome " << cUser->getSurName(); 
    std::cout << "! You are now ";
    SetConsoleTextAttribute(hConsole, LOGIN_COLOR);
    std::cout << "logged in";    
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "." << std::endl;
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


int app::addItem(void){
    // Function that creates a new item to be add to the current library. Returns
    // 1 if it was executed sucessfully and 0 in any other case. The creation is a
    // while loop in each information, been possible to rewrite the last attribute
    // or even return to the previous attribute. The local menu, with localOption
    // and localBreak does not interfere in the global menu (option and toBreak).
    // This function also add an item to the total number of it (not creating
    // another). 

    // Variable declaration
    int reference;                 // Item's code of reference
    std::string author;            // Author
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
    int localOption;               // Takes the option for the menu display (local)
    bool localBreak = false;       // Controls the while loop for the menu (local)
    int itemNumber;                // Number of the item to be added
    library* &target = (cLibrary->getItemsNumber()>0) ? cLibrary : loadedLibrary;

    MENU:
    // Display options of item
    std::cout << "\n\n";
    std::cout << "Do you wanto to:" << std::endl;
    std::cout << " [1] Create a new item" << std::endl;
    std::cout << " [2] Add an unit to an existem item" << std::endl;
    std::cout << " [3] Return to main menu" << std::endl;
    std::cout << "[12] Exit" << std::endl;
    std::cout << "\nEnter your option: ";

    // Chose the type of the item to be created
    localOption = takeIntChoice();
    
    // If the choice is valid, jumps to the next part
    switch(localOption){
        case 1: 
            break;
        case 2:  // Add item 
            goto ADD_ITEM_MENU;         
        case 3:
            system("CLS");
            return 0;
        case 12:
            toBreak = true;
            return 0;            
        default:        
            displayInvalidChoice();
            goto MENU;
            break;
    }

    // Take the main information (commum for all items / media attributes)
    reference = std::stoi(takeSingleInfo("item's code reference", true));
    if(reference == 0) return 0; // Check for return option
    author = takeSingleInfo("author's name(s)");
    if(author == "0") return 0; // Check for return option
    title = takeSingleInfo("item's title");
    if(title == "0") return 0; // Check for return option
    addDate = 12;
    year = std::stoi(takeSingleInfo("item's year of creation", true));
    if(year == 0) return 0; // Check for return option
    totalNumber = std::stoi(takeSingleInfo("avaiable number", true));
    if(totalNumber == 0) return 0; // Check for return option

    // ------------------------------------------------------------
    localBreak = false;
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
        pagesNumber = std::stoi(takeSingleInfo("pages number", true));
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
        pagesNumber = std::stoi(takeSingleInfo("pages number", true));
        collection = takeSingleInfo("collection");
        editor = takeSingleInfo("editor");
        summary = takeSingleInfo("summary");
        artNumber = std::stoi(takeSingleInfo("number of articles", true));
        newItem = new magazine(reference, author, title, addDate, year,
            totalNumber, totalNumber, pagesNumber, collection, summary, editor, 
            artNumber);
        break;
    case 3: // Will create a CD
        timeDuration = std::stoi(takeSingleInfo("time duration", true));
        production = takeSingleInfo("production");
        trackNumber = std::stoi(takeSingleInfo("track number", true));
        newItem = new CD(reference, author, title, addDate, year, totalNumber,
            totalNumber, timeDuration, production, trackNumber);
        break;
    case 4: // Will create a digital ressource        
        format = takeSingleInfo("format");
        size = std::stoi(takeSingleInfo("file size", true));
        link = takeSingleInfo("link for the ressource");
        newItem = new digital(reference, author, title, addDate, year, totalNumber,
            totalNumber, format, size, link);
        break;
    case 5: // Will create a VHS
        timeDuration = std::stoi(takeSingleInfo("time duration", true));
        production = takeSingleInfo("production");
        newItem = new VHS(reference, author, title, addDate, year, totalNumber,
            totalNumber, timeDuration, production);
        break;
    case 6: // Will create a DVD
        timeDuration = std::stoi(takeSingleInfo("time duration", true));
        production = takeSingleInfo("production");
        trackNumber = std::stoi(takeSingleInfo("track number", true));
        newItem = new DVD(reference, author,title, addDate, year, totalNumber,
            totalNumber, timeDuration, production, trackNumber);
        break;
    default:
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::createItem(void)' function in " << __FILE__ << ".\nIt was" <<
            " not possible to create a new item Impossible option was chosen.\n";
        return 1;
    }

    if(loadedLibrary->addItem(newItem, true)){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "app::createItem(void)' function in " << __FILE__ << ".\nIt was" <<
            " not possible to append the item.\n";
        return 1;
    }
    
    // Ending
    std::cout << "Item created sucessfully. Tap [2] to show all the items or " <<
        "seach for it with command [1] search.";
    return 0;

    // Add an item menu -----------------------------------------------------------
    ADD_ITEM_MENU:
    std::cout << "Wich item do you want to add? ";
    itemNumber = takeIntChoice();
    std::cout << "Item description:\n" << std::endl;
    target->showItemDes(itemNumber);
    
    std::cout << "\nAre you sure that you want to add one of this item?\n";            
    std::cout << " [1] Yes" << std::endl;
    std::cout << " [2] No, return to main menu" << std::endl;
    std::cout << "[12] Exit" << std::endl;
    std::cout << "\nEnter your option: ";
    localOption = takeIntChoice();

    if(--itemNumber >= target->getItemsNumber() || itemNumber < 0){
        std::cout << "There is no such item in the library." << std::endl;
        goto ADD_ITEM_MENU;
    }

    switch (localOption){
    case 1:                
        target->addItem(itemNumber);
        system("CLS");
        std::cout << "Item add with success." << std::endl;            
        return 0;
    case 2:
        return 0;
    case 3:
        toBreak = true;
        return 0;
    default:
        displayInvalidChoice();
        goto ADD_ITEM_MENU;
    }             
}


std::string app::takeSingleInfo(std::string informationName, bool isInt){
    // Function to take (and confirm) one information given by an user. It will
    // return the information in a std::string type. The boolean variabel
    // isInt controls if its mandatory for the input to be an integer type.
    // It is true and the input is no numeric, will ask for another input from
    // the user. If it returns the special string "0", then the user wants to
    // return to the main menu (or exit the application). So, for each call
    // function, a return check mus be done, with the format
    // 
    // if(takeSingleInfo(informationName) == "0"){
    //      /*
    //          return statement (returns to main menu)
    //      */
    // }
    //
    // All other checks for string compatibility must be done outside the function.
    // The input informationName will be used to display only (will not affect)
    // the function itself.

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
        if(isInt&&information.find_first_not_of("0123456789")!=std::string::npos){
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


std::string app::takeSecretPassword(std::string informationName){
    // Function to takea secret password from the user. Used in user creation
    // and in login. It work identically as takeSingleInfo, but it does not have
    // to be an integer and also has a hiden input (HIDEN_CHAR). The input 
    // informationName will alse be used to display only (will not affect) the
    // function itself.

    // Variables
    std::string password = "";
    char a;

    // Display command
    std::cout << "Enter the " << informationName << ": ";
    
    // Infinite loop
    for(int i=0;;){
        a = getch();
        if(a!='\b' && a!='\0' && a!='\r'){
            password.push_back(a); //stores a in pass
            std::cout << HIDEN_CHAR;
        }
        // If backspace has been pressed (exclude the last character)
        if(a == '\b' && !password.empty()){
            std::cout << "\b \b"; // Rub the character behind the cursor.
            password.erase(std::prev(password.end()));
        }
        if(a == '\r')
            break; // Break the loop
    }

    return password;
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


void app::forgotPassword(void){
    // Function to reset a user password. To be implemented.

    // Variable declaration
    bool emailCheckBreak = false;
    std::string email;

    // Get the email
    while(!emailCheckBreak){
        email = takeSingleInfo("email");
        if(email == "0") return; // Check if the user wants to quit

        // Check if the email is already registred
        for(int i=0; i<allUsers.size(); i++){
            if(allUsers[i]->getEmail() == email){
                std::cout << "An email has been sent to " << email << ". "
                    << "Check your inbox for instructions." << std::endl;
                return;
            }
            // If the email is avaiable
            if(i+1==allUsers.size()){
                std::cout << "No account was finded with " << email << ".\n";
                return;
            }
        }
    }
}


void app::removeItem(void){
    // Function to remove an item from the loaded library.

    //Variable declaration
    int out;                  // Output integer check (delete and remove item)
    bool localBreak = false;  // While loop control
    int localOption;          // Option in local menu
    int itemNumber;           // Item number to be deleted/removed
    library* &target = (cLibrary->getItemsNumber()>0) ? cLibrary : loadedLibrary;


    // -------------------------------------------------------------------------
    LOCAL_MENU:
    system("CLS");
    target->showItems();

    // Local loop for local menu
    while(!localBreak){
        std::cout << "Enter the item number to be removed: ";
        itemNumber = takeIntChoice();

        if(itemNumber>target->getItemsNumber()){
            std::cout << "There is no such item in the library.\n";
            continue;
        }

        localBreak = true;
    }
    
    // -------------------------------------------------------------------------
    // Confirmation
    std::cout << "Item discription:\n" << std::endl;
    target->showItemDes(--itemNumber);
    std::cout << "\nWhat do you want to do?" << std::endl;
    std::cout << " [1] Remove one item" << std::endl;
    std::cout << " [2] Remove all items (DELETE ARTICLE)" << std::endl; 
    std::cout << " [3] Return to main menu" << std::endl; 
    std::cout << "[12] Exit" << std::endl;
    
    // Local loop for local menu

    std::cout << "\nEnter your option: ";
    localOption = takeIntChoice();
    switch(localOption){
    case 1:
        goto REMOVE_ONE;
    case 2:
        goto REMOVE_ALL;
    case 3:
        return;
    case 12:
        toBreak = true;
        return;
    default:
        displayInvalidChoice();
        goto LOCAL_MENU;
    }

    // -----------------------------------------------------------------------
    REMOVE_ALL:

    std::cout << "Are you sure that you want to remove ";
    std::cout<< " items?" << std::endl;
    std::cout << " [1] Yes" << std::endl;
    std::cout << " [2] No, return to main menu" << std::endl; 
    std::cout << "[12] Exit" << std::endl;
    std::cout << "\nEnter your option: ";
    localOption = takeIntChoice();
    switch(localOption){
    case 1:
        break;
    case 2:
        return;
    case 12:
        toBreak = true;
        return;
    default:
        displayInvalidChoice();
        goto REMOVE_ALL;
    }

    // Check if the item exist
    if(itemNumber >= target->getItemsNumber() || itemNumber < 0){
        std::cout << "There is not such item in the library." << std::endl;
        return;
    }

    // Try to delete all the items (and file)
    out = target->deleteItem(itemNumber);
    if(out == 1){
        std::cout << "There is at least one item with a client yet." <<
            "You have to return all item to delete it." << std::endl;
        return;
    }
    else if(out == -1){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'void" << 
            " app::removeItem(void)' function in " << __FILE__ << 
            ".\n\tIt was not possible to remove the item." << std::endl;
        return;
    }

    // Remove the item from the loaded library (if necessary)
    if(cLibrary->getItemsNumber()>0){
        int ref = cLibrary->getItemsReference(itemNumber);
        int pos = loadedLibrary->getPositionByReference(ref);
        loadedLibrary->removeItem(pos);
    }

    // Ending
    system("CLS");
    std::cout << "Item removed successfully." << std::endl;
    return;

    // ------------------------------------------------------------------------
    REMOVE_ONE:
    // Try to remove the item (and file)
    if(target->removeItem(itemNumber)){
        std::cout << "There is no items returned to do the action. " <<
            "You have to return at least one item to delete it." << std::endl;
    }
    system("CLS");
    std::cout << "Item removed successfully." << std::endl;
    return;
}


void app::removeClient(void){
    // Function to remove a client (adm use only).

    showUsers();

    //Variable declaration
    bool localBreak = false;
    int userNumber;

    // Local loop for local menu
    while(!localBreak){
        std::cout << "Enter the client number to be removed: ";
        userNumber = takeIntChoice();

        if(userNumber>allUsers.size()){
            std::cout << "There is no such client in the library.\n";
            continue;
        }

        localBreak = true;
    }

    // Confirmation
    std::cout << "Client discription:\n" << std::endl;
    std::cout << allUsers[--userNumber]->getName() << std::endl;
    std::cout << "\nAre you sure that you want to remove the client " <<
        "permanently?" << std::endl;
    std::cout << " [1] Yes" << std::endl;
    std::cout << " [2] No, return to main menu" << std::endl;    
    std::cout << "[12] No, exit application" << std::endl;
    
    // Local loop for local menu
    localBreak = false;
    while(!localBreak){
        std::cout << "\nEnter your option: ";
        int localOption = takeIntChoice();
        switch(localOption)    {
        case 1:
            localBreak = true;
            break;
        case 2:
            return;
        case 12:
            toBreak = true;
            return;
        default:
            displayInvalidChoice();
            continue;
        }
    }

    // Try to remove the item (and file)
    std::string fileName = (std::string) USERS_DIRNAME + "/client_" + 
        std::to_string(allUsers[userNumber]->getReference()) + "_" +  
        allUsers[userNumber]->getName() + ".txt";
    remove(fileName.c_str());

    // Remo
    allUsers.erase(allUsers.begin()+userNumber);

    // Ending
    std::cout << "Client removed successfully." << std::endl;
    return;
}


void app::returnItem(void){
    // Function to return an item (adm use only)

    // Variable declarations
    int referenceToSearch;  // Reference for the item that is been took
    int positionToSearch;   // Position of the item in the library
    int numberOfLends;      // Number of lends
    int *userItemsList;     // List of items took by the user
    int localOption;        // Local option for local menu

    // Take the item reference
    referenceToSearch = std::stoi(takeSingleInfo("item's reference", true));

    // Take the number of lends
    positionToSearch = loadedLibrary->getPositionByReference(referenceToSearch);
    numberOfLends = loadedLibrary->getLendsNumber(positionToSearch);
    int matchedList[numberOfLends]; // Lists all users that have took the item

    // Display all possible users
    std::cout << "Possible users:\n" << std::endl;
    int j = 0;
    for(int i=0; i<allUsers.size(); i++){ 

        // Take the items of the user
        userItemsList = allUsers[i]->getAttributes();

        if(userItemsList == NULL)
                continue; // An adm was found

        for(int itemCounter=1; itemCounter<=userItemsList[0]; itemCounter++){   

            if(userItemsList[itemCounter] == referenceToSearch){
                matchedList[j++] = i;
                std::cout << "[" << j << "]\t" << allUsers[i]->getSurName() 
                    <<  '\t' << allUsers[i]->getName() << '\t' << std::endl; 
                break; 
            }
        }
    }

    // Check if there is any client with that article 
    if(j==0){
        system("CLS");
        std::cout << "There is not any client with this article." << std::endl;
        return;
    }
    

    // --------------------------------------------------------------------
    CHOICE_MENU:
    std::cout << "\nEnter the user wich is returning the item: ";
    int userToReturn = takeIntChoice();

    // Verify if its a valid choice
    if(userToReturn>numberOfLends || userToReturn<1){
        std::cout << "There is no such user in the results shown above.\n";
        goto CHOICE_MENU;
    }
    user* &target = allUsers[matchedList[--userToReturn]];

    // Confirmation
    std::cout << "Do you confirm the return of the item:\n" << std::endl;
    loadedLibrary->showItemDes(positionToSearch);
    std::cout << "\nof the client " << target->getName() << " " << 
        target->getSurName() << " ?" << std::endl;
    std::cout << " [1] Yes" << std::endl;
    std::cout << " [2] No, return to main menu" << std::endl;
    std::cout << "[12] Exit" << std::endl;
    std::cout << "\nEnter your option: "; 
    int option = takeIntChoice();

    switch (option){
    case 1:
        system("CLS");
        loadedLibrary->returnItem(--option);
        target->returnItem(referenceToSearch);
        target->save(USERS_DIRNAME);
        std::cout << "Article returned successfully." << std::endl;
        break;
    case 2:
        return;        
    case 3:
        return;
    case 12:
        toBreak = true;
        return;
    default:
        displayInvalidChoice();
        goto CHOICE_MENU;
    }

    return;
}