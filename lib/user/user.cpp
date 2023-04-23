#include "user.h"


user::user(){

}


user::user(std::string name_, std::string surName_, std::string email_,
    std::string password_, int reference_)
    : name(name_)
    , surName(surName_)
    , email(email_)
    , password(password_)
    , reference(reference_){
}


std::string user::getName(){
    return name;                                                              
}


std::string user::getSurName(){
    return toUpperCase(surName);
}


std::string user::getEmail(){
    return email;
}


int user::getReference(void){
    return reference;
}


int user::checkID(std::string email_, std::string password_){
    // Function that returns if the credentials of the user were correct.
    // It comparaires the email and the password only, and will return 1
    // only if both credentials are the same.

    return (!email.compare(email_) && !password.compare(password_));
}


int *user::getAttributes(void){
    return NULL;
}


int user::returnItem(int reference){
    return 1;
}


std::string user::toUpperCase(std::string inputString){
  // Function to change all the caractheres to lower case. Used in searchFor
  // function. For inter use only.

	for(int i=0;inputString[i]!='\0';i++){
    //checking for uppercase characters
		if (inputString[i] >= 'a' && inputString[i] <= 'z'){
            //converting uppercase to lowercase
			inputString[i] = inputString[i] - 32; 
        }
	}

	return inputString;
}


int user::save(std::string dirName){
    // Function to save the client info 
    std::cout << "\nLine " << __LINE__ << ": Error executing 'int " << 
        "user::save(std::string dirName)' function in " << __FILE__ <<
        "\n\tBased class method called." << std::endl;

    return -1;
}