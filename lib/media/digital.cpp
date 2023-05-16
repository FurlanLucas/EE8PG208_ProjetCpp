#include "digital.h"


digital::digital(int reference_, std::string author_, std::string title_,
    int addDate_, int year_, int totalNumber_, int dispNumber_,
    std::string format_, int size_, std::string link_)
    : media{reference_,author_,title_,addDate_,year_,totalNumber_,dispNumber_}
    , format(format_)
    , size(size_)
    , link(link_){
}


void digital::showData(){
    // Function to display all the important info in class (for debug only).
    std::cout << "This item (code " << reference << ") is a " << year <<
    " " << format << " file by " << author << "\ncalled \"" << title <<
    "\navailable in " << link << ".\n";
};


std::string digital::getFileInfo(void){
    // This function returns a string that contains all important informations about
    // this article to be saved in a txt file. It's used in "toFile" function at 
    // "library" class.
  
    return "d\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
        + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
        std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
        format + "\n" + std::to_string(size) + "\n" + link;
}


int digital::searchFor(std::string toSearch){
    // Function to research the informartion in the class. Recives a string to
    // search for and returns 1 if it was found any candidate and 0 if it wasn't.

    // Convert the autors name to lower case to compare
    std::string newAuthor = toLowercase(author);
    std::string newTitle = toLowercase(title);

    // Try to find the string input
    std::size_t foundAuthor = newAuthor.find(toLowercase(toSearch));
    std::size_t foundTitle = newTitle.find(toLowercase(toSearch));   
    std::size_t foundType = toLowercase(toSearch).find("digital");
    std::size_t foundYear = std::to_string(year).find(toSearch); 
    std::size_t foundReference = std::to_string(reference).find(toSearch);

    // Verify if it was found
    if(foundTitle!=std::string::npos || foundAuthor!=std::string::npos ||
        foundType!=std::string::npos || foundYear!=std::string::npos || 
        foundReference!=std::string::npos)
        return 1; // Candidate found
    return 0; // Candidate not found
}