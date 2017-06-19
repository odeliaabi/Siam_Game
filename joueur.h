#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "pion.h"
#include "animal.h"
#include "plateau.h"

class Joueur
{
private:
    std::vector <Animal> m_nb_animal;
    std::string m_nom_joueur;
    int m_nb_presence_animal_plateau;

public:
    // Constructeurs
    Joueur();
    Joueur(std::vector <Animal> _nb_animal, std::string _nom_joueur);

    // Destructeur
    ~Joueur();

    // Methodes
    void DisplayJoueur();

    int menu();
    void action(int a, Plateau *plateau);
    void entrer_un_animal(Plateau *plateau);
    void deplacer_sur_plateau(Plateau *plateau);
    void changer_orientation(int ValPion);
    void sortir_animal();
    void deplacer_en_pousant();
    bool presencePion(int choixDeplacement, Plateau *plateau, int valPion);

    // Accesseurs
    std::vector <Animal> getNb_animal();
    std::string getNom_joueur();
    int getLongueur_plateau();
    int getLargeur_plateau();
    int getNb_presence_animal_plateau();

    void setNb_animal(std::vector <Animal> nb_animal);
    void setNom_joueur(std::string nom_joueur);
    void setNb_presence_animal_plateau(int nb_presence_animal_plateau);
};

#endif // JOUEUR_H_INCLUDED
