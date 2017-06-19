#include "partie.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>

/// Constructeurs & Destructeur
//Constrcuetur
Partie::Partie(){
}

//Constructeur Surchargé
Partie::Partie(Plateau _plateau_partie, int _nb_tour, std::vector <Joueur> _nb_joueur, int _allegro)
       : m_plateau_partie(_plateau_partie), m_nb_tour(_nb_tour), m_allegro(_allegro), m_nb_joueur(_nb_joueur){
}

//Destrcuteur
Partie::~Partie(){
}


/// Methodes
//Methodes gérant le jeu
void Partie::boucle_partie(){

    //Initialisation des permieres variables
    m_fin_jeu = 1;
    m_sortie_menu = 0;
    m_sortie = 1;
    m_nb_tour = 0;

    //Affiche la page d'accueil
    this->pageAcceuil();

    while(m_sortie != 0){

        ///Boucle de menu
        while(m_sortie_menu != 1){
            this->menu();
        }

        ///Si on choisit un mode de jeu
        //this->DisplayPartie(); ///a enlever à la fin du projet
        if(m_choix_menu != 4 && m_choix_menu != 2){
            //Affiche le plateau
            m_plateau_partie.afficher_plateau();

            //lance la vrai boucle de jeu
            while(m_fin_jeu != 0){
                for(unsigned int i = 0; i < m_nb_joueur.size(); i++){
                    m_nb_joueur[i].action(m_nb_joueur[i].menu(), &m_plateau_partie);
                    this->FinDePartie();
                    this->DetectionTouche();
                    m_nb_tour ++;
                }
                if(m_nb_joueur.size() == 0){
                    std::cout << "Il n'y aucun joueur" << std::endl << std::endl;
                    m_fin_jeu = 0;
                }
            }
            //Affiche la page de victoire
            this->pageVictoire();
            m_sortie_menu = 0;
        }

        ///Si on décide  de sortir
        else{
            m_sortie = 0;
            this->pageSortie();
            //page de sortis du jeu
        }
    }
}

void Partie::initialisation_partie(int nbrJoueur, int nbrAnimal, int nbrMontagne, int NbrColonne, int NbrLigne, int IA){

    //Initialisation d'attribut provisoire

    Pion m;
    Animal a;
    Joueur j;
    Plateau pl;
    std::vector<Animal> VectProvAnimal;
    std::vector<Animal> VectProvAnimalPlateau;
    std::vector<Pion> VectPionTemp;
    std::vector<Joueur> VectJoueurTemp;

    ///Boucle initialisation de Joueur
    for(int i = 0; i < nbrJoueur; i++){

        ///Boucle initialisant les animaux du joueur
        for(int k = 0; k < nbrAnimal; k++){

            //initialise le nom des animaux
            if(i == 0){
                a.setNom('E');
            }
            if(i == 1){
                a.setNom('R');
            }
            if(i > 1){
                a.setNom('R' + i);
            }
            //Initialise les autres attributs des animaux
            a.setResistance(1);
            a.setLigne_pion(-1);
            a.setColonne_pion('#');
            a.setPresence_plateau(false);
            a.setDirection('n');
            //Ajoute l'animal au vecteur provisoire contenant les animaux du joueur
            VectProvAnimal.push_back(a);
            VectProvAnimalPlateau.push_back(a);
        }
        std::cout << pl.getAnimal_plateau().size() << std::endl <<std::endl;

        ///On initialise le joueur
        j.setNb_animal(VectProvAnimal);//ajoute l'animal créer à un joueur
        j.setNb_presence_animal_plateau(nbrAnimal);
        j.setNom_joueur("joueur");///Regarder comment concatener!! initie le nom du joueur

        //On vide le vecteur contenant les animaux
        VectProvAnimal.clear();

        ///On ajoute le joueur à la liste temporaire des joueurs de la partie
        VectJoueurTemp.push_back(j);
    }

    ///Initialise les montagnes sur le plateau
    //Corrige ne nombre de montagne max
    if(nbrMontagne > NbrLigne){
        nbrMontagne = NbrLigne - 2;
    }
    for(int i = 0; i < nbrMontagne; i++){
        //
        m.setNom('M');
        m.setResistance(0.9);
        m.setLigne_pion(i+2);
        m.setColonne_pion(97 + NbrColonne/2);
        m.setPresence_plateau(true);
        ///On ajoute la montagne à la liste temporaire des montagnes
        VectPionTemp.push_back(m);
    }

    setPlateau_partie(pl);

    ///Initialise le plateau
    pl.setAnimal_plateau(VectProvAnimalPlateau);
    pl.setPlateau(VectPionTemp); //On ajoute au plateau la liste définitive des monatgnes
    pl.setLongueur_plateau(NbrColonne);//On initie le nbr de colonne du plateau
    pl.setLargeur_plateau(NbrLigne);//on initie le nbr de ligne du plateau
    //Initialise le vecteur de pointeur de vecteur d'animaux (LOL)


    ///Initialise la partie
    m_nb_joueur = VectJoueurTemp;
    m_plateau_partie = pl;

    //test
    /*this->DisplayPartie();
    m_plateau_partie.DisplayPlateau();
    this->DetectionTouche();*/
}

void Partie::menu(){

    ///Affiche le menu
    std::cout << "*-*-*-*-*-*-*-*-*-*-* Menu *-*-*-*-*-*-*-*-*-*-*" << std::endl << std::endl;
    std::cout << "Taper 1 pour commencer un nouvelle partie a deux joueurs" << std::endl << std::endl;
    std::cout << "Taper 2 pour jouer contre une IA (pas implanter)" << std::endl << std::endl;
    std::cout << "Taper 2 pour personnaliser votre partie" << std::endl << std::endl;
    std::cout << "Taper 3 pour quitter" << std::endl << std::endl;
    std::cout << "Taper  pour afficher les regles du jeu " << std::endl << std::endl;
    std::cout << "Rentrer la valeur de votre choix : "<<std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl << std::endl;
    //Rentre la valeur voulu par le menu
    std::cin >> m_choix_menu;
    std::cout << std::endl << std::endl;

    //applique le choix rentree
    if(m_choix_menu == 1){
        m_sortie_menu = 1;
        this->initialisation_partie(2, 5, 3, 5, 5, 0);
    }
    if(m_choix_menu == 2){
        //Message d'erreur
        std::cout << "Pas implanter" << std::endl << std::endl;
        this->DetectionTouche();
    }
    if(m_choix_menu == 3){
        m_sortie_menu = 1;
        //On va allouer et choisir la valeur pour un plateau modulaire
        int nbrJoueur, nbrAnimal, nbrMontagne, nbrColonne, nbrLigne;
        std::cout << "Rentrer le nombre de Joueur : ";
        std::cin >> nbrJoueur;
        std::cout << "Rentrer le nombre d'Animaux par Joueur : ";
        std::cin >> nbrAnimal;
        std::cout << "Rentrer le nombre de Montagne : ";
        std::cin >> nbrMontagne;
        std::cout << "Rentrer le nombre de Colonne : ";
        std::cin >> nbrColonne;
        std::cout << "Rentrer le nombre de Ligne : ";
        std::cin >> nbrLigne;
        //On initialise la partie avec les valeurs precedemment rentrée
        this->initialisation_partie(nbrJoueur, nbrAnimal, nbrMontagne, nbrColonne, nbrLigne, 0);
    }
    if(m_choix_menu == 4){
        m_sortie_menu = 1;
        m_sortie = 0;

    }
    if(m_choix_menu < 1 || m_choix_menu > 4){
        //On vide la console
        system("cls");
        std::cout << "Votre choix n'existe pas" << std::endl;
        //On appel la fonction qui va detecter si une touche est touché
        this->DetectionTouche();

    }
    system("cls");
}

//Méthodes gérant des evenements
void Partie::DetectionTouche(){
    while(!kbhit()){
    }
}

void Partie::FinDePartie(){
    std::vector <Pion> plat;
    plat = m_plateau_partie.getPlateau();

    //Circule dans le vecteur de pion du plateau, si l'une des montagnes est hors plateau, alors le jeu est terminé
    for(unsigned int i = 0; i < plat.size(); i++){
        if(plat[i].getNom() == 'M' && plat[i].getPresence_plateau() == false){
            m_fin_jeu = 0;
        }
    }
}

void Partie :: presentation()
{

    std::ifstream presentation("presentation.txt");

    if(presentation)
    {
        // On stock dans la chaine le fichier
        std::string texte;

        // Tant qu'on a pas atteint la fin de regles.txt
        while(getline(presentation,texte))
        {
            // On affiche les règles du jeu
            std::cout << texte << std::endl;
        }
    }

    // Blindage ouverture du fichier
    else
    {
        std::cout << "Erreur fichier presentation" << std::endl;
    }
}


//Méthodes affichant des pages de jeu
void Partie::pageAcceuil(){

    system("cls");

    std::ifstream presentation("presentation.txt");
    if(presentation)
    {
        // On stock dans la chaine le fichier
        std::string texte;

        // Tant qu'on a pas atteint la fin de regles.txt
        while(getline(presentation,texte))
        {
            // On affiche les règles du jeu
            std::cout << texte << std::endl;
        }
    }

    // Blindage ouverture du fichier
    else
    {
        std::cout << "Erreur fichier presentation" << std::endl;
    }

    system("PAUSE");
    system("cls");

    this->DetectionTouche();
    system("cls");
}

void Partie::pageVictoire(){
    std::cout << "Bien jouer" << std::endl << std::endl;
    ///Affiche la page de victoire
    this->DetectionTouche();
    system("cls");
}

void Partie::pageSortie(){
        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl << std::endl;
        std::cout << "                                                 " << std::endl << std::endl;
        std::cout << "                                                 " << std::endl << std::endl;
        std::cout << "                                                 " << std::endl << std::endl;
        std::cout << "                                                 " << std::endl << std::endl;
        std::cout << "              MERCI D'ETRE VENU                  " << std::endl << std::endl;
        std::cout << "          A BIENTOT POUR DE NOUVELLES            "<<std::endl;
        std::cout << "          AVENTURES AU MONDE DU SIAM             "<<std::endl;
        std::cout << "                    :)                           "<<std::endl;
        std::cout << "                                                 "<<std::endl;
        std::cout << "                                                 "<<std::endl;
        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl << std::endl;
    ///Affiche la page de victoire
    this->DetectionTouche();
    system("cls");
}

//Méthode de test
void Partie::DisplayPartie(){
    /*std::cout << "Nombre de tour : " << m_nb_tour << std::endl;
    std::cout << "Allegro : " << m_allegro << std::endl;
    std::cout << "Choix menu : " << m_choix_menu << std::endl;
    std::cout << "Choix sortie : " << m_sortie << std::endl;
    std::cout << "Choix sortie de menu : " << m_sortie_menu << std::endl;
    std::cout << "Fin de jeu : " << m_fin_jeu << std::endl;*/
    std::cout << "Nb de joueur : " << m_nb_joueur.size() << std::endl;
    for(unsigned int i = 0; i < m_nb_joueur.size(); i++){
        m_nb_joueur[i].DisplayJoueur();
    }
}


/// Getter & Setter
//Getter
Plateau Partie::getPlateau_partie(){
    return m_plateau_partie;
}

int Partie::getNb_tour(){
    return m_nb_tour;
}

int Partie::getAllegro(){
    return m_allegro;
}

int Partie::getChoixMenu(){
    return m_choix_menu;
}

int Partie::getSortie(){
    return m_sortie;
}

int Partie::getSortieMenu(){
    return m_sortie_menu;
}

int Partie::getFinJeu(){
    return m_fin_jeu;
}

std::vector <Joueur> Partie::getNb_joueur(){
    return m_nb_joueur;
}

//Setter
void Partie::setPlateau_partie(Plateau plateau_partie){
    m_plateau_partie = plateau_partie;
}

void Partie::setNb_tour(int nb_tour){
    m_nb_tour = nb_tour;
}

void Partie::setAllegro(int _allegro){
    m_allegro = _allegro;
}

void Partie::setChoixMenu(int _choix_menu){
    m_choix_menu = _choix_menu;
}

void Partie::setSortie(int _sortie){
    m_sortie = _sortie;
}

void Partie::setSortieMenu(int _sortie_menu){
    m_sortie_menu = _sortie_menu;
}

void Partie::setFinJeu(int _fin_jeu){
    m_fin_jeu = _fin_jeu;
}

void Partie::setNb_joueur(std::vector<Joueur> nb_joueur){
    m_nb_joueur = nb_joueur;
}
