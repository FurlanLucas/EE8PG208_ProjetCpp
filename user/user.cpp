#include "user.h"


user::user(){

}


user::user(std::string name_, std::string surName_, std::string email_)
  : name(name_)
  , surName(surName_)
  , email(email_){
}


std::string user::getName(){
    return name;                                                              
}

std::string user::getSurName(){
    return surName;
}

std::string user::getEmail(){
    return email;
}


int user::checkID(std::string email_, std::string password_){
    // Function that returns if the credentials of the user were correct.
    // It comparaires the email and the password only, and will return 1
    // only if both credentials are the same.

    if (!email.compare(email_) && !password.compare(password_))
        return true;
    else
        return false;
}