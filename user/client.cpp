#include "client.h"


client::client(){

}


client::client(std::string name_, std::string surName_, std::string email_,
    std::string password_)
    : user(name_, surName_, email_, password_){
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
    getline(myfile, name);
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