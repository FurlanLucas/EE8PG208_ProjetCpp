#include "adm.h"


adm::adm(std::string name_, std::string surName_, std::string email_)
    : user(name_, surName, email){

}


adm::adm(std::string fileName){
    std::ifstream myfile;   // Txt file to be open
    myfile.open(fileName);  // Creates a client class based in a file source

    // Main inputs
    getline(myfile, name);
    getline(myfile, surName);
    getline(myfile, email);
    getline(myfile, password);
    
    // Close the file opened
    myfile.close();
}


void adm::showClientsInfo(void){

}
