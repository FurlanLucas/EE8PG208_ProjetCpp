#include "client.h"


client::client(std::string name_, std::string surName_, std::string email_)
    : user(name_, surName, email)
    , numberOfLends(0){
}


client::client(std::string fileName){
    std::ifstream myfile;   // Txt file to be open
    myfile.open(fileName);  // Creates a client class based in a file source

    // Main inputs
    getline(myfile, name);
    getline(myfile, surName);
    getline(myfile, email);
    getline(myfile, password);
    myfile >> numberOfLends;

    // Creates the int vector for the items that were took

    /*
    *itemsReference = new int[numberOfLends];
    for(int i=0; i<numberOfLends;i++)
        myfile >> **itemsReference;
    
    */

    // Close the file opened
    
    myfile.close();
}