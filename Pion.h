#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED
#include <iostream>

class Pion
{
protected:
    char m_nom;
    int m_resistance;
    int m_ligne_pion;
    char m_colonne_pion;
    bool m_presence_plateau;

public:
    // Constructeurs
    Pion();
    Pion(char _nom, int _resistance, int _ligne_pion, char _colonne_pion, bool _presence_plateau);

    // Destructeur
    ~Pion();

    // Methodes
    bool plateau();
    void DisplayPion();

    // Accesseurs
    char getNom();
    float getResistance();
    int getLigne_pion();
    char getColonne_pion();
    bool getPresence_plateau();

    void setNom(char nom);
    void setResistance(float resistance);
    void setLigne_pion(int ligne_pion);
    void setColonne_pion(char colonne_pion);
    void setPresence_plateau(bool presence_plateau);
};

#endif // PION_H_INCLUDED
