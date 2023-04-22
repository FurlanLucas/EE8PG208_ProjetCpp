#include "client.h"


client::client(){

}


client::client(std::string name_, std::string surName_, std::string email_,
    std::string password_, int reference_)
    : user(name_, surName_, email_, password_, reference_)
    , itemsLendedRef(new int(0)){
}


client::client(std::string fileName){
    // Constructor that loads the client info. The itemsLendedRef variable 
    // stores the reference code for all items that a client have taken. It 
    // is an array of n+1 variables, with n been the number of borows and 
    // the first element of the array is the number n.

    std::ifstream myfile;   // Txt file to be open
    myfile.open(fileName);  // Creates a client class based in a file source

    if(!myfile.is_open()){
        std::cout << "Error in contructor of client(std::string fileName)." <<
            " It was not possible to open the client file" << std::endl;
        return;
    }    

    // Main inputs 
    int numberOfLends;
    myfile >> reference;
    myfile.ignore(1, '\n'); getline(myfile, name);
    getline(myfile, surName);
    getline(myfile, email);
    getline(myfile, password);
    myfile >> numberOfLends;
    
    itemsLendedRef = new int[numberOfLends+1];
    itemsLendedRef[0] = numberOfLends;

    // Take the reference
    for(int i=1; i<=numberOfLends;i++)
        myfile >> itemsLendedRef[i];

    // Close the file opened
    myfile.close();
}


int *client::getAttributes(void){
    // Returns the references for lended items
    return itemsLendedRef;
}


int client::save(std::string dirName){
    // Function that saves client's info to a txt file. Returns 0 if it
    // was executed successfully or 1 if any error occured.

    // Item file name
    std::string fileName = dirName + "/client_" + std::to_string(reference) + 
        "_" +  (name+surName).substr(0, CAR_NAME_TXT);

    // Out file  
    std::ofstream outFile;
    outFile.open(fileName + ".txt");

    // Check if the file has been opened
    if(!outFile){
        std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
            "client::save(std::string dirName)' function in " << __FILE__ << 
            ".\nFile " << fileName << " could not be opened." << std::endl;
        return 1;
    }

    // Write to the out file   
    outFile << reference << std::endl;
    outFile << name << std::endl;  
    outFile << surName << std::endl;
    outFile << email << std::endl;
    outFile << password << std::endl;
    for(int i=0; i<=itemsLendedRef[0];i++)
        outFile << itemsLendedRef[i] << std::endl;

    // Output return
    outFile.close();
    return 0;
}