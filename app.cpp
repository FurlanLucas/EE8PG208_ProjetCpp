#include "app.h"


app::app(void){
    // First displays
    std::cout << "\nInitializing application." << std::endl;
    loadedLibrary = new library;
    cLibrary = new library;

    // Tries to initialize
    if(loadedLibrary->loadItems())
        std::cout << "Error loading files" << std::endl;
    else
        std::cout << "All items were loaded sucessfully." << std::endl;

    isLogged = false;
}


app::~app(){
    std::cout << "Exiting application." << std::endl;
}


int app::menu(){
    // Main menu for the application. It takes the user option and controls
    // the other functions that will be called. Returns 0 if the application
    // were executed sucessfully ou 1 if it was not.

    int toBreak = 0;
    while(!toBreak){
        // Menu printing
        std::cout << "\nList of commands:" << std::endl;
        std::cout << "[1] Search for an item" << std::endl;
        std::cout << "[2] Show all items" << std::endl;
        std::cout << "[3] Show items description" << std::endl;        
        std::cout << "[4] Return to general library" << std::endl;
        if (isLogged)
            std::cout << "[5] Logout" << std::endl;
        else
            std::cout << "[5] Login" << std::endl;
        std::cout << "[6] Exit" << std::endl;
        std::cout << "\nEnter your option: ";

        // Take the option and check if it is a valid integer number
        int option;
        std::cin >> option;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid type. If you want to exit the application," 
            " tap 6. " << std::endl;
            continue;
        }

        // Main option
        switch (option) {
        case 1:
            search();
            break;
        case 2:
            loadedLibrary->showItems();
            break;
        case 3:
            showItemDescription();
            break;
        case 4:
            cLibrary = new library;
            break;
        case 5:
            if (isLogged){                
                delete cUser;
                isLogged = false;
                std::cout << "Your are logged out." << std::endl;
            }
            else
                login();
            break;
        case 6:
            std::cout << "Exiting menu." << std::endl;
            return 0;          
        default:            
            std::cout << "Invalid choice. If you want to exit the " <<
                "application, tap 6." << std::endl;
            break;
        }
    }

    // Unreachable line (problem ocurred)
    std::cout << "A problem ocurred in menu options." << std::endl;
    return 1;
}


int app::search(){
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
            std::cout << "\nThe following items were found:" << std::endl;
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


void app::showItemDescription(){
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


int app::login(){
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
        user *testUser;
  
        if(fileName.find("client")!=std::string::npos){
            testUser = new client(fileName);                     
        }  
        else if(fileName.find("user")!=std::string::npos)
            testUser = new adm(fileName); 
        else {
            std::cout << "Error reading users database." << std::endl;
            return 1;
        }

        // Check if it is the correct ID;
        if(testUser->checkID(email, password)){
            std::cout << "Your are logged in." << std::endl;
            isLogged = true;
            cUser = testUser;
            delete testUser;
            closedir(folder);
            return 0;
        }

    }

    // If it reachs this point, no user were found
    std::cout << "User not found." << std::endl;
    return 0;
}


int app::takeItem(){
    // Function to lend an item from the library.
    cLibrary->showItems();
    std::cout << "Which item do you want to take ?" << std::endl;
    int itemNumber;
    std::cin >> itemNumber;
    cLibrary->lendItem(itemNumber);
    return 0;
}