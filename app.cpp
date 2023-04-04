#include "app.h"


app::app(void){
    // First displays
    std::cout << "\nInitializing application." << std::endl;
    loadedLibrary = new library;
    cLibrary = new library;

    // Tries to initialize
    if(loadedLibrary->loadItems())
        std::cout << "Error loading files." << std::endl;
    else
        std::cout << "All items were loaded sucessfully." << std::endl;

    isLogged = false;
    isAdm = false;

    // Setting console collor attribute
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
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

    int toBreak = 0;
    while(!toBreak){
        // Menu printing
        displayMenuOptions();

        // Take the option and check if it is a valid integer number
        int option;
        std::cin >> option;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            displayInvalidChoice();
            continue;
        }

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
            delete cLibrary;
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

        case 12: // [12] Exit
            std::cout << "Exiting menu." << std::endl;
            return 0;          
        default:            
            displayInvalidChoice();
            break;
        }
    }

    // Unreachable line (problem ocurred)
    std::cout << "A problem ocurred in menu options." << std::endl;
    return 1;
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
    std::cin >> toSearch;

    // Search for the item and show the results
    try{   
        // Verify in which library it has to search for     
        if(cLibrary->getItemsNumber()!=0)
            results = cLibrary->search(toSearch);
        else
            results = loadedLibrary->search(toSearch);

        // Verify if there was any result
        if(results->getItemsNumber()!=0){
            std::cout << "\nShowing " << results->getItemsNumber() << 
                " results." << std::endl;
            results->showItems();
            cLibrary = results;
        }
        else{
            std::cout << "No items were found." << std::endl;
        }
    }
    catch(int errorN){
        std::cout << "Un error ocurred at the search function." << std::endl;
        delete results;
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
    DIR *folder;               // Folter variable to be loaded (see dirent.h)
    struct dirent *cfile;      // Pointer for the file in *folder (see dirent.h)
    folder = opendir(USERS_DIRNAME); // Open all files in the directory
    
    if (!folder){
        std::cout << "I was not possible open the folder." << std::endl;
        return 1;
    }

    // Count the total number of users to load
    int usersNumber = 0;
    while ((cfile = readdir(folder)) != NULL){ usersNumber++; }
    usersNumber = usersNumber - 2;  // Will not take the '.' and '..'

    // Resets the pointer
    rewinddir(folder); cfile = readdir(folder); cfile = readdir(folder);

    // Search for the information within the users data
    for (int i=0;i<usersNumber;i++) {
        std::ifstream myfile;   // txt file to be open
        cfile = readdir(folder);

        // Checks if it is a client or a adm
        std::string fileName = (std::string) USERS_DIRNAME + "/" + 
            (std::string)cfile->d_name;
  
        if(fileName.find("client")!=std::string::npos){
            cUser = new client(fileName);         
            isAdm = false;                        
        }  
        else if(fileName.find("adm")!=std::string::npos){
            isAdm = true;
            cUser = new adm(fileName); 
        }
        else {
            std::cout << "Error reading users database." << std::endl;
            return 1;
        }

        // Check if it is the correct ID;
        if(cUser->checkID(email, password)){
            std::cout << "Welcome back " << cUser->getSurName(); 
            std::cout << "!. You are now ";
            SetConsoleTextAttribute(hConsole, LOGIN_COLOR);
            std::cout << "logged in";    
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "." << std::endl;
            isLogged = true;
            closedir(folder);
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
    int itemNumber;
    std::cin >> itemNumber;
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
            std::cout << "An error ocurred trying to lend an item." << std::endl;
            return 1;
        }
    }
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

    delete cUser;
    isLogged = false;
    isAdm = false;

    // Printing
    std::cout << "By " << cUser->getSurName();
    std::cout << ". You are now ";
    SetConsoleTextAttribute(hConsole, LOGOUT_COLOR);
    std::cout << "logged out";    
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "." << std::endl;
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

