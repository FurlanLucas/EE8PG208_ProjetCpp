#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <vector>
#include <string>

using namespace std;


class Utilisateur {
public:
// definition d'un utilisateur global à partir de son nom, prenom,addresse,mot de passe 
// constructeur avec utilisateur  paramètre
    Utilisateur(string nom,string prenom,string login);
     string getNom() ;
     string getPrenom() ;
     string getLogin() ;
   


private:
    string m_nom;
    string m_prenom;
    string m_login;
  
};






// définition d'un client qui hérite de la classe utilisateur
class Client : public Utilisateur {
public:
// constructeur client avec paramètre
    Client(string nom,string prenom,string login,string motDePasse,string telephone,string adresse);
   
    string getAdresse() ;
    string getTelephone() ;
 
    bool verifierMotDePasse(string motDePasse) ;
  

private:
   
   string m_adresse;
   string m_telephone;
   string m_motDePasse;
  
};



// definition d'un administrateur qui herite pour la bibliothèque

class Administrateur: public Utilisateur {
public:
// constructeur administrateur avec paramètre
      Administrateur(string nom,string prenom,string login,string motDePasse);

     
     bool verifierMotDePasse(string motDePasse);

private:

string m_motDePasse;
};





#endif
