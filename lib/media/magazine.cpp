#include "magazine.h"

magazine::magazine(int reference_, std::string author_, std::string title_,
    int addDate_, int year_, int totalNumber_, int dispNumber_, int pagesNumber_,
    std::string collection_, std::string summary_, std::string editor_,
    int artNumber_)
    : book{reference_, author_, title_, addDate_, year_, totalNumber_, dispNumber_,
        pagesNumber_, collection_, summary_, editor_}
    , artNumber(artNumber_){
}

void magazine::showData(){
    // Function to display all the important info in class (for debug only).
    std::cout << "This item (code " << reference << ") is a " << year <<
    " book by " << author << " called \"" << title << "\",\npublished by " <<
    editor << " with " << pagesNumber << " pages. " << summary << ".\n";
};


std::string magazine::getFileInfo(void){
    // This function returns a string that contains all important informations about
    // this article to be saved in a txt file. It's used in "toFile" function at 
    // "library" class.
  
    return "m\n" + std::to_string(reference) + "\n" + author + "\n" + title + "\n"
        + std::to_string(addDate) + "\n" + std::to_string(year) + "\n" + 
        std::to_string(totalNumber) + "\n" + std::to_string(dispNumber) + "\n" + 
        std::to_string(pagesNumber) + "\n" + collection + "\n" + summary + "\n" +
        editor + "\n" + std::to_string(artNumber);
}


int magazine::searchFor(std::string toSearch){
    // Function to research the informartion in the class. Recives a string to
    // search for and returns 1 if it was found any candidate and 0 if it wasn't.

    // Convert the autors name to lower case to compare
    std::string newAuthor = toLowercase(author);
    std::string newTitle = toLowercase(title);  
    std::string newCollection = toLowercase(collection);
    std::string newEditor = toLowercase(editor);

    // Try to find the string input
    std::size_t foundAuthor = newAuthor.find(toLowercase(toSearch));
    std::size_t foundTitle = newTitle.find(toLowercase(toSearch));
    std::size_t foundCollection = newCollection.find(toLowercase(toSearch));
    std::size_t foundEditor = newEditor.find(toLowercase(toSearch));  
    std::size_t foundType = toLowercase(toSearch).find("magazine");
    std::size_t foundYear = std::to_string(year).find(toSearch); 
    std::size_t foundReference = std::to_string(reference).find(toSearch);

    // Verify if it was found
    if(foundTitle!=std::string::npos || foundAuthor!=std::string::npos ||
        foundCollection!=std::string::npos || foundEditor!=std::string::npos
        || foundType!=std::string::npos || foundYear!=std::string::npos || 
        foundReference!=std::string::npos)
        return 1; // Candidate found
    return 0; // Candidate not found
}