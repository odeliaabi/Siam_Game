#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "pion.h"
#include "animal.h"
#include <vector>

class Plateau
{
private:
    std::vector <Pion> m_plateau;
    std::vector <Animal> m_animal_plateau;
    int m_longueur_plateau;
    int m_largeur_plateau;

public:

    ///Constructeur & Destructeur
    //COnstructeur
    Plateau();
    //constructeur surchargé
    Plateau(unsigned int NbrAnimal);
    Plateau(std::vector <Pion> _plateau, int _longueur_plateau, int _largeur_plateau);
    // Destructeur
    ~Plateau();

    ///Méthodes
    void afficher_plateau();
    //Méthodes de test
    void DisplayPlateau();

    ///Getter & Setter
    //Getter
    std::vector <Pion> getPlateau();
    std::vector <Animal> getAnimal_plateau();
    int getLongueur_plateau();
    int getLargeur_plateau();
    //Setter
    void setPlateau(std::vector <Pion> plateau);
    void setAnimal_plateau(std::vector <Animal> animal_plateau);
    void setLongueur_plateau(int longueur_plateau);
    void setLargeur_plateau(int largeur_plateau);
};

#endif // PLATEAU_H_INCLUDED
