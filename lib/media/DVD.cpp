#include "DVD.h"

DVD::DVD(int reference_, std::string author_, std::string title_, int addDate_,
    int year_, int totalNumber_, int dispNumber_, int timeDuration_,
    std::string production_, int trackNumber_)
    : VHS{reference_,author_,title_,addDate_,year_,totalNumber_,dispNumber_,
        timeDuration_,production_}
    , trackNumber(trackNumber_){
}

void DVD::showData(){
    // Function to display all the important info in class (for debug only).
    std::cout << "This item (code " << reference << ") is a " << year <<
    " CD by " << author << " called \"" << title << "\",\nproduced by " <<
    production << " with " << trackNumber << " tracks.\n";
};



std::string DVD::getFileInfo(void){
    // This function returns a string that contains all important informations about
    // this article to be saved in a txt file. It's used in "toFile" function at 
    // "library" class.
  
    return "D\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
        + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
        std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
        std::to_string(timeDuration)  + "\n" + production + "\n" + 
        std::to_string(trackNumber);
}


int DVD::searchFor(std::string toSearch){
    // Function to research the informartion in the class. Recives a string to
    // search for and returns 1 if it was found any candidate and 0 if it wasn't.

    // Convert the autors name to lower case to compare
    std::string newAuthor = toLowercase(author);
    std::string newTitle = toLowercase(title);  
    std::string newProduction = toLowercase(production);

    // Try to find the string input
    std::size_t foundAuthor = newAuthor.find(toLowercase(toSearch));
    std::size_t foundTitle = newTitle.find(toLowercase(toSearch));
    std::size_t foundProduction = newProduction.find(toLowercase(toSearch));   
    std::size_t foundType = toLowercase(toSearch).find("dvd");
    std::size_t foundYear = std::to_string(year).find(toSearch); 
    std::size_t foundReference = std::to_string(reference).find(toSearch);

    // Verify if it was found
    if(foundTitle!=std::string::npos || foundAuthor!=std::string::npos ||
        foundProduction!=std::string::npos || foundType!=std::string::npos || 
        foundYear!=std::string::npos || foundReference!=std::string::npos)
        return 1; // Candidate found
    return 0; // Candidate not found
}