#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include "pion.h"

class Animal : public Pion
{
private:
    char m_direction;

public:
    // Constructeurs
    Animal();
    Animal(char _nom, float _resistance, int _ligne_pion, char _colonne_pion, bool _presence_plateau, char _direction);

    // Destructeur
    ~Animal();

    // Methodes
    bool possible_pousser();
    void pousser();
    void DisplayAnimal();

    // Accesseurs
    char getDirection();

    void setDirection(char direction);
};

#endif // ANIMAL_H_INCLUDED
