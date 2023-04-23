#include "media.h"

media::media(){};


media::media(int reference_, std::string author_, std::string title_,
  int addDate_, int year_, int totalNumber_, int dispNumber_)
  : reference(reference_)
  , author(author_)
  , title(title_)
  , addDate(addDate_)
  , year(year_)
  , totalNumber(totalNumber_)
  , dispNumber(dispNumber_)
  {
};


void media::addItem(void){
  // Function to add a item to the total number.
  totalNumber++;
  dispNumber++;
};


int media::removeItem(void){
  // Funcition to remove a item to the total number. Return 0 if an item has
  // been removed sucessfully and 1 if an error occurred.

  if((totalNumber > 1) && dispNumber>0){
    totalNumber--;
    dispNumber--;
    return 0;
  }
  else{
    return 1;
  }
};


int media::lendItem(void){
  // Function to lend a item to a user. It reduces the available number by one.
  // It returns 0 if it was sucessfully executated and 0 if it was not.
  if (dispNumber > 0){
    dispNumber--;
    return 0;
  }
  else{
    return 1;
  }
}


void media::returnItem(void){
  if(dispNumber == totalNumber){
   std::cout << "\nLine " << __LINE__ << ": Error executing 'void" << 
    " media::returnItem(void)' function in " << __FILE__ << 
    ".\n\tIt is not possible to return a item wich is not taken.\n";
  }     
   dispNumber++;
}


int media::getDispNumber(void){
  // Get the dispNumber
  return dispNumber;
}


int media::getTotalNumber(void){
  // Get the total number
  return totalNumber;
}


std::string media::getAuthor(void){
  // Get autors name
  return author;
}


int media::getYear(void){
  // Get the item's year
  return year;
}


std::string media::getTitle(void){
  // Get item's title
  return title;
}


int media::getReference(void){
  // Get item's reference
  return reference;
}


int media::searchFor(std::string toSearch){
  // Function to research the informartion in the class. Recives a string to
  // search for and returns 1 if it was found any candidate and 0 if it wasn't.

  // Convert the autors name to lower case to compare
  std::string newAuthor = toLowercase(author);
  std::string newTitle = toLowercase(title);

  // Try to find the string input
  std::size_t foundAuthor = newAuthor.find(toLowercase(toSearch));
  std::size_t foundTitle = newTitle.find(toLowercase(toSearch));

  // Verify if it was found
  if(foundTitle!=std::string::npos || foundAuthor!=std::string::npos)
    return 1; // Candidate found
  return 0; // Candidate not found
}


std::string media::toLowercase(std::string inputString){
  // Function to change all the caractheres to lower case. Used in searchFor
  // function. For inter use only.

	for(int i=0;inputString[i]!='\0';i++){
    //checking for uppercase characters
		if (inputString[i] >= 'A' && inputString[i] <= 'Z')
			inputString[i] = inputString[i] + 32; //converting uppercase to lowercase
	}

	return inputString;
}


std::string media::getFileInfo(void){
  return "TEST";
}