#include <iostream>
#include "media/book.h"
#include "media/CD.h"
#include "media/digital.h"
#include "media/paper.h"
#include "media/VHS.h"
#include "media/DVD.h"

int main(){
  std::cout << "Initializing main...\n\n\n";

  book myFirstBook(4168, "Hugo", "The world in our hands", 24, 2010,
    3, 2, 240, "Best books of Hugo", "Short story about a relationship...",
    "Editor Inc. R");
  CD myFirstCD(4556, "Michael Jackson", "First album (live in NY)", 69, 2005,
    1, 0, 246, "Sounds and music Inc. productions", 300);
  digital myFirstDigital(48919, "Janick V. Frasch", "An Auto-generated Nonlinear MPC Algorithm for Real-Time ObstacleAvoidance of Ground Vehicles",
    63, 2013, 1, 1, "pdf", 345, "https://www.researchgate.net/publication/261435899_An_auto-generated_nonlinear_MPC_algorithm_for_real-time_obstacle_avoidance_of_ground_vehicles#fullTextFileContent");
  paper myFirstPaper(4168, "Hugo", "The world in our hands", 24, 2010,
    3, 2, 240, "Best books of Hugo", "Short story about a relationship...",
    "Editor Inc. R", 549);
  VHS myFirstVHS(4556, "Michael Jackson", "First album (live in NY)", 69, 2005,
    1, 0, 246, "Sounds and music Inc. productions");
  DVD myFirstDVD(4556, "Michael Jackson", "First album (live in NY)", 69, 2005,
    1, 0, 246, "Sounds and music Inc. productions", 2611);


  myFirstBook.showData();
  myFirstCD.showData();
  myFirstDigital.showData();
  myFirstPaper.showData();
  myFirstVHS.showData();
  myFirstDVD.showData();

  std::cout << "\n\n";

  return 0;
}
