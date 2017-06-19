#include "Pion.h"

///Constructeur & Destructeur
//Constructeur
Pion::Pion(){
}

//Constructeur Surchargés
Pion::Pion(char _nom, int _resistance, int _ligne_pion, char _colonne_pion, bool _presence_plateau)
     :m_nom(_nom), m_resistance(_resistance), m_ligne_pion(_ligne_pion), m_colonne_pion(_colonne_pion), m_presence_plateau(_presence_plateau){
     }

// Destructeur
Pion::~Pion(){
}

/// Méthodes
//Méthodes de test
void Pion::DisplayPion(){
    std::cout << "Nom du Pion : " <<  m_nom << std::endl;
    std::cout << "Resistance du Pion : " << m_resistance << std::endl;
    std::cout << "Position Ligne Pion : " << m_ligne_pion << std::endl;
    std::cout << "Position Colonne Pion : " << m_colonne_pion << std::endl;
    std::cout << "Presence sur Plateau : " << m_presence_plateau << std::endl;
}

///Getter & Setter
//Getter
char Pion::getNom(){
    return m_nom;
}

float Pion::getResistance(){
    return m_resistance;
}

int Pion::getLigne_pion(){
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */
    return m_ligne_pion;
}

char Pion::getColonne_pion(){
    return m_colonne_pion;
}

bool Pion::getPresence_plateau(){
    return m_presence_plateau;
}

//Setter
void Pion::setNom(char nom){
    m_nom = nom;
}

void Pion::setResistance(float resistance){
    m_resistance = resistance;
}

void Pion::setLigne_pion(int ligne_pion){
    m_ligne_pion = ligne_pion;
}

void Pion::setColonne_pion(char colonne_pion){
    m_colonne_pion = colonne_pion;
}

void Pion::setPresence_plateau(bool presence_plateau){
    m_presence_plateau = presence_plateau;
}
