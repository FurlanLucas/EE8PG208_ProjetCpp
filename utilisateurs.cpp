#include "utilisateur.h"
#include<iostream>
#include <string>

using namespace  std;


// Methodes de la classe utilisateur

Utilisateur::Utilisateur(string nom,string prenom,string login)
    :m_nom(nom),m_prenom(prenom),m_login(login){}



string Utilisateur::getNom(){
    return m_nom;                                                              
}

string Utilisateur::getPrenom(){
    return m_prenom;
}

string Utilisateur::getLogin(){
    return m_login;
}



// utilisation des methodes  de la classe client 
Client::Client(string nom,  string prenom, string login,  string motDePasse,string telephone,string adresse)
      :m_motDePasse(motDePasse),m_telephone(telephone),m_adresse(adresse),
      Utilisateur(nom,prenom,login){}

string Client::getTelephone(){
return m_telephone;
}


string Client::getAdresse(){
return m_adresse;
}


bool Client::verifierMotDePasse(string motDePasse){
  if(m_motDePasse == motDePasse){
           cout<< "Bienvenue"<<endl;
    }
  else 
         cout<< "mot de passe incorrect"<<endl;

}




// utilisation des methodes  de la classe administrateur

Administrateur::Administrateur(string nom,string prenom,string login,string motDePasse) :m_motDePasse(motDePasse),Utilisateur(nom,prenom,login){}



bool Administrateur::verifierMotDePasse(string motDePasse){
  if(m_motDePasse == motDePasse){
           cout<< "Bienvenue"<<endl;
    }
  else 
         cout<< "mot de passe incorrect"<<endl;

}
















