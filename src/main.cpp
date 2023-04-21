#include "app.h"

int main(){
  app *application = new app;
  application->menu();
  delete application;
  std::cout << "Press any key to continue..." << std::endl;
  std::cin.get();
  return 0;
}