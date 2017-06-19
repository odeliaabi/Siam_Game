#include "animal.h"

/// Constructeurs & Getter
//Constructeur
Animal::Animal(){
}

//Constructeur Surchargé
Animal::Animal(char _nom, float _resistance, int _ligne_pion, char _colonne_pion, bool _presence_plateau, char _direction)
       : Pion(_nom, _resistance, _ligne_pion, _colonne_pion, _presence_plateau), m_direction(_direction){
}

// Destructeur
Animal::~Animal(){
}

/// Méthodes
//Méthodes de test
void Animal::DisplayAnimal(){
    std::cout << "La direction de l'Animal est : " << m_direction << std::endl;
    Pion::DisplayPion();
}

///Getter & Setter
//Getter
char Animal::getDirection(){
    return m_direction;
}

//Setter
void Animal::setDirection(char direction){
    m_direction = direction;
}
