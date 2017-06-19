#include "Plateau.h"

///Constructeur & Destructeur
// Constructeurs
Plateau::Plateau(){
}

//Constructeur surchargé
Plateau::Plateau(std::vector <Pion> _plateau, int _longueur_plateau, int _largeur_plateau)
        :m_plateau(_plateau), m_longueur_plateau(_longueur_plateau), m_largeur_plateau(_largeur_plateau){
}

// Destructeur
Plateau::~Plateau(){
}

/// Methodes
void Plateau::afficher_plateau(){
    char c;
    int p, o, placementPion = 0;

    /// Ressources
    // Coin 1 gauche haut
    char c1 = 218;
    // Coin 2 droite haut
    char c2 = 191;
    // Coin 3 droite bas
    char c3 = 217;
    // Coin 4 gauche bas
    char c4 = 192;
    // Horizontal
    char h = 196;
    // Vertical
    char v = 179;
    // Vertical et horizontal vers la droite
    char vd = 195;
    // Vertical et horizontal vers la gauche
    char vg = 180;
    // Horizontal et vertical vers le bas
    char hb = 194;
    // Horizontal et vertical vers le haut
    char hh = 193;
    // Croix
    char croix = 197;

    /*std::vector<Pion> ProvPion;
    ProvPion = m_plateau;*/

    for(int i = 0; i < m_largeur_plateau + 1; i++){


        ///Affiche la premiere ligne de caractere du tableau
        if(i == 0){
            std::cout << c1 << h << hb << h << h;

            for(int j = 2; j < m_longueur_plateau + 1; j++){
                p = j / 10 + 1;
                std::cout << hb;
                for(int cpt = 0; cpt < p; cpt++){
                    std::cout << h << h;
                }
            }
            std::cout << c2 << std::endl;
        }
        ///Affiche la deuxieme ligne de caractere (les 5 premiers caracteres de la ligne sont spéciaux)
        else if(i == 1){
            std::cout << vd << h << croix << h << h;

            for(int j = 2; j < m_longueur_plateau + 1; j++){
                p = j / 10 + 1;
                std::cout << croix;
                for(int cpt = 0; cpt < p; cpt++){
                    std::cout << h << h;
                }
            }
            std::cout << vg << std::endl;
        }
        ///Affiche les lignes classiques du tableau
        else{
            std::cout << vd << h << croix;
            for(int j = 1; j < m_longueur_plateau; j++){
                p = j / 10 + 1;
                std::cout << h;
                for(int cpt = 0; cpt < p; cpt++){
                    std::cout << h;
                }
                std::cout << croix;
            }
            std::cout << h << h << vg << std::endl;
        }

        for(int j = 0; j < m_longueur_plateau + 2; j++){
            ///Affiche le nom des colonnes sur la premiere ligne
            if(i == 0){
                if(j == 0){
                    std::cout << v;
                    std::cout << " ";
                }
                if(j > 1 && j <= m_longueur_plateau){
                    std::cout << v;
                    std::cout << j - 1;
                    std::cout << " ";
                }
                if(j == m_longueur_plateau + 1){
                    std::cout << v;
                    std::cout << j - 1;
                    std::cout << " ";
                    std::cout << v;
                }
            }
            ///Affiche le nom des lignes sur la premieres case de chaque ligne
            else if(j == 1 && i >= 1){
                std::cout << v;
                c = 64+i; //affiche le caractere correspondant selon la table ASCII, si cela affiche autres chose que des lettres, le problemes est ici
                std::cout << c;
                std::cout << v;
            }
            ///Affiche les pions qui sont sur le plateau et les cases vides (a retravailler !!!!)
            if(j > 1 && i > 0){
                for(unsigned int k = 0; k < m_plateau.size(); k++){
                    o = m_plateau[k].getColonne_pion() - 95;

                    //std::cout << i/*hauteur*/ << m_plateau[k].getLigne_pion() << " ";
                    //std::cout << j/*longueur*/ << o << " ";*/
                    if(o == j && m_plateau[k].getLigne_pion() == i){
                        std::cout << m_plateau[k].getNom() << " ";
                        placementPion = 1;
                    }
                }
                if(placementPion == 0){
                    std::cout << "  ";
                }
                placementPion = 0;

                //permet d'agrandir les cases si le chiffre de la colonne est plus long
                p = j / 10 + 1;
                std::cout << v;
                for(int cpt = 2; cpt < p; cpt++){
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    ///Affiche la derniere ligne du tableau
    std::cout << c4 << h;
    for(int j = 0; j < m_longueur_plateau; j++){
        p = j / 10 + 1;
        std::cout << hh;
        for(int cpt = 0; cpt < p; cpt++){
            std::cout << h << h;
        }
    }
    std::cout << c3 << std::endl;
}

//Méthodes de test
void Plateau::DisplayPlateau(){

    std::cout << std::endl << "Nombre de montagne : " << m_plateau.size() << std::endl;
    for(unsigned int i = 0; i < m_plateau.size(); i++){
        m_plateau[i].DisplayPion();
    }

    for(unsigned int i = 0; i < m_animal_plateau.size(); i++){
        std::cout << std::endl << m_animal_plateau.size() << std::endl;
        m_animal_plateau[i].DisplayAnimal();
    }
}

/// Getter & Setter
//Getter
std::vector <Pion> Plateau::getPlateau(){
    return m_plateau;
}

std::vector <Animal> Plateau::getAnimal_plateau(){
    return m_animal_plateau;
}

int Plateau::getLongueur_plateau(){
    return m_longueur_plateau;
}

int Plateau::getLargeur_plateau(){
    return m_largeur_plateau;
}

//Setter
void Plateau::setPlateau(std::vector <Pion> plateau){
    m_plateau = plateau;
}

void Plateau::setAnimal_plateau(std::vector <Animal> animal_plateau){
    m_animal_plateau = animal_plateau;
}

void Plateau::setLongueur_plateau(int longueur_plateau){
    m_longueur_plateau = longueur_plateau;
}

void Plateau::setLargeur_plateau(int largeur_plateau){
    m_largeur_plateau = largeur_plateau;
}
