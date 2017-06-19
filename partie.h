#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include <vector>
#include "pion.h"
#include "plateau.h"
#include "joueur.h"

class Partie
{

private:
    Plateau m_plateau_partie;
    int m_nb_tour;
    int m_allegro;
    int m_choix_menu;//Continet le choix du menu
    int m_sortie;//Contiens la valeur de sortie de la boucle de jeu
    int m_sortie_menu;//Contines la valeur de sortie du menu dejeu
    int m_fin_jeu;
    std::vector <Joueur> m_nb_joueur;

public:
    /// Constructeurs & Destrcuteurs
    Partie();
    Partie(Plateau _plateau_partie, int _nb_tour, std::vector <Joueur> _nb_joueur, int m_allegro);
    ~Partie();

    /// Methodes
    //method gerant le jeu
    void initialisation_partie(int nbrJoueur, int nbrAnimal, int nbrMontagne, int nbrColonne, int nbrLigne, int nbrIA);
    void boucle_partie();
    void menu();

    //Methodes gerant des evenements du jeu
    void DetectionTouche();
    void FinDePartie();
    void presentation();

    //Methodes affichants des pages de jeux
    void pageAcceuil();
    void pageVictoire();
    void pageSortie();

    //fonction de test
    void DisplayPartie();

    /// Getter & Setter
    //Getter
    Plateau getPlateau_partie();
    int getNb_tour();
    int getAllegro();
    int getChoixMenu();
    int getSortie();
    int getSortieMenu();
    int getFinJeu();
    std::vector <Joueur> getNb_joueur();

    //Setter
    void setPlateau_partie(Plateau plateau_partie);
    void setNb_tour(int nb_tour);
    void setAllegro(int _allegro);
    void setChoixMenu(int _choix_menu);
    void setSortie(int _sortie);
    void setSortieMenu(int _sortie_menu);
    void setFinJeu(int _fin_jeu);
    void setNb_joueur(std::vector<Joueur> nb_joueur);
};

#endif // PARTIE_H_INCLUDED
