#include "joueur.h"
#include "console.h"
#include "partie.h"
#include "conio.h"

///Constructeur & Destructeur
// Constructeurs
Joueur::Joueur(){
}

//Constructeur surchargées
Joueur::Joueur(std::vector <Animal> _nb_animal, std::string _nom_joueur)
       :m_nb_animal(_nb_animal), m_nom_joueur(_nom_joueur){
}

// Destructeur
Joueur::~Joueur(){
}

/// Méthodes
void Joueur::entrer_un_animal(Plateau *plateau){

    ///Variable de la fonction
    Console *pConsole;
    pConsole->getInstance();
    std::vector<Animal> VectAnProv;
    int Col, Lig, sortie = 0;
    int trouverfalse = 0;
    char Ligc, Colc, direction;

    while(sortie == 0){

        ///Menu de choix de la position
        std::cout << "Sur quelle colonne doit entrer le Pion : ";
        std::cin >> Col;
        std::cout << "Sur quelle Ligne doit entrer le Pion : ";
        std::cin >> Ligc;
        std::cout << "Quelle est sa direction d'entrer : ";
        std::cin >> direction;
        std::cout << std::endl;

        ///Traduit la ligne et la colonne rentrer
        if(Ligc >= 65 && Ligc <= 90){
            Lig = Ligc - 64;
        }
        if(Ligc >= 97 && Ligc <= 122){
            Lig = Ligc - 102;
        }
        if(Ligc >= 49 && Ligc <= 57){
            Lig = Ligc - 50;
        }

        ///Verifie que l'on est bien sur les limites du Tableau
        if(Col == 1 || Col == plateau->getLongueur_plateau()){
            if(Lig >= 1 && Lig <= plateau->getLargeur_plateau()){
                sortie = 1;
            }
            else{
                std::cout << "Le pion n'est pas placer sur les bords du Plateau, donner de nouvelle coordonnes" << std::endl;
            }
        }
        else if(Lig == 1 || Lig == plateau->getLargeur_plateau()){
            if(Col >= 1 && Col <= plateau->getLongueur_plateau()){
                sortie = 1;
            }
            else{
                std::cout << "Le pion n'est pas placer sur les bords du Plateau, donner de nouvelle coordonnes" << std::endl;
            }
        }
        if(direction != 'h' && direction != 'b' && direction != 'd' && direction != 'g'){
            sortie = 0;
            std::cout << "La direction rentrer ne correspond à rien" << std::endl;
        }

        ///Verifie si il y a des Pion à pousser

    }
    ///Place le Pion sur le plateau
    Colc = Col + 96;
    pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
    //Trouve un Pion du Joueur qui n'est pas sur le Plateau
    for(unsigned int i = 0; i < m_nb_animal.size(); i++){
        //Dés qu'un pion non placé est trouvé, on le place sur le tableau
        if(m_nb_animal[i].getPresence_plateau() == false && trouverfalse == 0){
            m_nb_animal[i].setLigne_pion(Lig);
            m_nb_animal[i].setColonne_pion(Colc);
            m_nb_animal[i].setDirection(direction);
            m_nb_animal[i].setPresence_plateau(true);
            trouverfalse = 1;
            //Affiche le nom de l'Animal
            std::cout << m_nb_animal[i].getNom();
            //Rentre la direction du Pion
            //Peut mieux faire que les if en cascade, mais bug sinon (option)
            if(direction == 'h'){
                m_nb_animal[i].setDirection('h');
            }
            if(direction == 'b'){
                m_nb_animal[i].setDirection('b');
            }
            if(direction == 'd'){
                m_nb_animal[i].setDirection('d');
            }
            if(direction == 'g'){
                m_nb_animal[i].setDirection('g');
            }
            //Affiche la direction du Pion
            std::cout << m_nb_animal[i].getDirection();
        }
    }
    ///Modifie la position du Pion dans le Plateau
    trouverfalse = 0;
    for(unsigned int i = 0; i < plateau->getAnimal_plateau().size(); i++){
        //Dés qu'un pion non placé est trouvé, on le place sur le tableau
        if(plateau->getAnimal_plateau()[i].getPresence_plateau() == false && trouverfalse == 0 && plateau->getAnimal_plateau()[i].getNom() == m_nb_animal[0].getNom()){
            VectAnProv = plateau->getAnimal_plateau();
            VectAnProv[i].setLigne_pion(Lig);
            VectAnProv[i].setLigne_pion(Lig);
            VectAnProv[i].setColonne_pion(Colc);
            VectAnProv[i].setDirection(direction);
            VectAnProv[i].setPresence_plateau(true);
            //Actualise le vecteur d'Animaux
            plateau->setAnimal_plateau(VectAnProv);
            trouverfalse = 1;
            //Rentre la direction du Pion
            //Peut mieux faire que les if en cascade, mais bug sinon (option)
            if(direction == 'h'){
                plateau->getAnimal_plateau()[i].setDirection('h');
            }
            if(direction == 'b'){
                plateau->getAnimal_plateau()[i].setDirection('b');
            }
            if(direction == 'd'){
                plateau->getAnimal_plateau()[i].setDirection('d');
            }
            if(direction == 'g'){
                plateau->getAnimal_plateau()[i].setDirection('g');
            }
        }
    }

    ///Diminue de 1 le nbr de pion hors plateau (option d'affichage)
    m_nb_presence_animal_plateau = m_nb_presence_animal_plateau - 1;
    //a coder

    ///Deplace le curseur et efface le menu hors du tableau
    pConsole->gotoLigCol(plateau->getLargeur_plateau()*2 + 3, 0);
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    pConsole->gotoLigCol(plateau->getLargeur_plateau()*2 + 3, 0);
    /*std::cout << std::endl;
    this->DisplayJoueur();
    std::cout << std::endl << std::endl;
    plateau->DisplayPlateau();*/
    std::cout << std::endl;

    pConsole->deleteInstance();
}

void Joueur::deplacer_sur_plateau(Plateau *plateau){

    ///Variable de la fonction
    Console *pConsole;
    pConsole->getInstance();
    int Col, Lig, direction, valPion, choixDeplacement;
    int sortie = 0;
    bool presence = false;
    char Ligc, Colc;

    ///Choisit le Pion qui va bouger
    while(sortie == 0){

        ///Menu de choix de la position du Pion à faire bouger
        std::cout << "Sur quelle colonne est le Pion que vous souhaitez bouger : ";
        std::cin >> Col;
        std::cout << "Sur quelle Ligne est Pion que vous souhaitez bouger: ";
        std::cin >> Ligc;
        std::cout << std::endl;

        ///Traduit la ligne et la colonne rentrer
        if(Ligc >= 65 && Ligc <= 90){
            Lig = Ligc - 64;
        }
        if(Ligc >= 97 && Ligc <= 122){
            Lig = Ligc - 96;
        }
        if(Ligc >= 49 && Ligc <= 57){
            Lig = Ligc - 48;
        }
        Colc = Col + 96;

            ///Affichage de test
            /*std::cout << "la colonne : " << Colc << std::endl;
            std::cout << "la ligne : " << Lig << std::endl;*/

        ///Vérifie qu'il y a un Pion au coordonnés données
        for(unsigned int i = 0; i < m_nb_animal.size(); i++){
            if(m_nb_animal[i].getColonne_pion() == Colc && m_nb_animal[i].getLigne_pion() == Lig){
                presence = true;
                valPion = i;
            }
        }
        if(presence == true){
            sortie = 1;
            presence = false;
        }
        else{
            std::cout << "Il n'y a pas de Pion à cette position" << std::endl << std::endl;
        }
    }

    ///Boucle permettant la selection de la case d'arriver
    sortie = 0;
    while(sortie == 0){

        ///Rentre les coordonnées de la case d'arriver
        //Demande la nouvelle case du Pion
        //Affiche le menu
        std::cout << "1- Pour deplacer le Pion vers le haut." << std::endl
                    << "2- Pour deplacer le Pion vers le bas." << std::endl
                    << "3- Pour deplacer le Pion vers la gauche." << std::endl
                    << "4- Pour deplacer le Pion vers la droite." << std::endl
                    << "5- Pour ne changer que l'orientation du Pion." << std::endl << std::endl
                    << "Rentrer votre choix : ";
        std::cin >> choixDeplacement;
        std::cout << std::endl;
        //rentre la nouvelle orientation du pion
        std::cout << "Rentrer la nouvelle orientation du Pion : ";
        std::cin >> direction;
        std::cout << std::endl;

        if(choixDeplacement == 5){
            this->changer_orientation(valPion);
        }

        ///Regarde si la valeur rentrer correspond à une valeur existante
        if(choixDeplacement > 5 || choixDeplacement < 1){
            sortie = 0;
        }
        ///Regarde si la case visée sors le Pion
        if((choixDeplacement == 1 && m_nb_animal[valPion].getLigne_pion() == 1) ||
            (choixDeplacement == 2 && m_nb_animal[valPion].getLigne_pion() == plateau->getLargeur_plateau()+1) ||
            (choixDeplacement == 3 && m_nb_animal[valPion].getColonne_pion() == 1) ||
            (choixDeplacement == 4 && m_nb_animal[valPion].getColonne_pion() == plateau->getLongueur_plateau()+1)){

            ///Modifie les coordonnées du Pion
            m_nb_animal[valPion].setLigne_pion(-1);
            m_nb_animal[valPion].setColonne_pion('#');
            m_nb_animal[valPion].setPresence_plateau(false);
            m_nb_animal[valPion].setDirection('n');

            ///Augmente le nombre de Pion hors plateau du joueur (A faire)
            m_nb_presence_animal_plateau = m_nb_presence_animal_plateau + 1;
            //modifie le nbr de pion hors plateau sur la console (a coder)

            ///Sors le Pion du tableau (affichage)
            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
            std::cout << "  ";

            sortie = 1;
        }
        ///Si la case ne sors pas, appele la fonction de presence
        else if(presencePion(choixDeplacement, plateau, valPion) == true){
            sortie = 1;
        }
        else{
            std::cout << std::endl << "Impossible de pousser les Pions, choixissez une autre action" << std::endl;
        }

        ///Deplace le curseur et efface le menu hors du tableau
        pConsole->gotoLigCol(plateau->getLargeur_plateau()*2 + 3, 0);
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                std::cout << ' ';
            }
            std::cout << std::endl;
        }
        pConsole->gotoLigCol(plateau->getLargeur_plateau()*2 + 3, 0);
        std::cout << std::endl;
    }
    pConsole->deleteInstance();
}

int Joueur::menu(){
    Console *pConsole;
    pConsole->getInstance();
    int choix;
    int sortie;
    bool presencetot;

    do{

        ///Menu de choix de l'action
        std::cout << "Pour rentrer un Pion : 1" << std::endl
                  << "Pour deplacer un pion : 2" << std::endl << std::endl
                  << "Rentrer la valeur de votre choix : ";
        std::cin >> choix;
        //system("PAUSE");
        std::cout << std::endl << std::endl;

        ///Verifie qu'il y a encore des Pions hors du plateau
        if(choix == 1){
            presencetot = true;
            for(unsigned int i = 0; i < m_nb_animal.size(); i++){

                if(m_nb_animal[i].getPresence_plateau() == false){
                    presencetot = false;
                }

            }

            if(presencetot == true){
                std::cout << "Il n'y a plus de pion a placer sur le plateau : " << std::endl;
            }
            else{
                sortie = 1;
            }
        }
        ///Verifie qu'il y a encore des Pions sur le plateau
        if(choix == 2){
            presencetot = false;
            for(unsigned int i = 0; i < m_nb_animal.size(); i++){
                if(m_nb_animal[i].getPresence_plateau() == true){
                    presencetot = true;
                }

            }
            if(presencetot == false){
                std::cout << "Il n'y a plus de pion a deplacer sur le plateau : " << std::endl;
            }
            else{
                sortie = 1;
            }
        }
        ///Renvois un message d'erreur si le Choix ne correspond à aucune action
        else if(choix != 1 && choix != 2){
                //test
                std::cout << choix << std::endl;
            std::cout << "La valeur rentrer ne correspond à aucun choix" << std::endl << std::endl;
            sortie = 0;
        }
    }while(sortie == 0);

    ///retourne l'option choisit dans le menu
    pConsole->deleteInstance();
    return choix;
}

void Joueur::action(int choix, Plateau *plateau){

    if(choix == 1){
        this->entrer_un_animal(plateau);
    }
    if(choix == 2){
        this->deplacer_sur_plateau(plateau);
    }
}

bool Joueur::presencePion(int choixDeplacement, Plateau *plateau, int valPion){

    ///Initialisation de variables
    float resistancetot = 1;
    int Lig, LigP, ColP, Col, posPlusUn = 0, l;
    int sortie = 0, LigInc = 1, ColInc = 1;
    char Colc, c;
    bool Mouvement = false;
    Console *pConsole;
    pConsole->getInstance();
    std::vector<Animal> VectAnProv;
    std::vector<Pion> VecMoProv;

    ///rentre les valeurs de comparaison
    Lig = m_nb_animal[valPion].getLigne_pion();
    Colc = m_nb_animal[valPion].getColonne_pion();
    //trnasiforme la position colonne en un int
    Col = Colc - 96;

    ///Si le Pion monte d'une case
    if(choixDeplacement == 1){
            ///On parcour le vecteur contenant les Montagnes
            for(unsigned int i = plateau->getPlateau().size(); i > 0; i++){
                ///On parcours le vecteur contenant les Pions
                for(unsigned int j = plateau->getPlateau().size(); j > 0; j++){
                    ///Si il y a un Pion sur la case d'au dessus
                        //test
                        /*std::cout << "Position Ligne Pion dessus : " << plateau->getAnimal_plateau()[j].getLigne_pion() << std::endl;
                        std::cout << "Position Ligne Pion pousse : " << Lig << std::endl;
                        std::cout << "Position Colonne Pion dessus : " << plateau->getAnimal_plateau()[j].getColonne_pion() << std::endl;
                        std::cout << "Position Colonne Pion pousse : " << Colc << std::endl;
                        std::cout << "Position LigneTot : " << Lig - LigInc << std::endl;*/

                    if(((Lig - LigInc == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc == plateau->getAnimal_plateau()[j].getColonne_pion())
                        || (Lig - LigInc == plateau->getPlateau()[i].getLigne_pion() && Colc == plateau->getPlateau()[i].getColonne_pion()))
                        && posPlusUn == 0){

                        //Si le Pion est dans la meme direction
                        if(plateau->getAnimal_plateau()[j].getDirection() == 'h'){
                            resistancetot = resistancetot + 1;
                        }
                        //Si le pion est dans la direction opposée
                        else if(plateau->getAnimal_plateau()[j].getDirection() == 'b'){
                            resistancetot = resistancetot - 1;
                        }
                        //Si le Pion est une montagne
                        else if(plateau->getPlateau()[i].getNom() == 'M'){
                            resistancetot = resistancetot - 0.9;
                        }
                        l = Lig;
                        c = Colc;
                    }
                    //Verifie si il manque un Pion sur la case supérieur
                    else if(Lig == l - 1 && Colc == c){
                        posPlusUn = 1;
                    }
                }
            }
            posPlusUn = 1;
            LigInc++;

        if(m_nb_animal[valPion].getDirection() != 'h'){
            resistancetot = -1;
        }
        std::cout << resistancetot << std::endl;
        ///Verifie que la resisance totale permet de bouger
        if(resistancetot > 0){
            sortie = 0;
            LigInc = 1;
            posPlusUn = 0;
            bool Mouvement = true;

            ///Tant qu'il y a des Pions au dessus du Pion initiale sans trou
            while(posPlusUn == 0){

                    //test
                    plateau->DisplayPlateau();
                ///On parcour le vecteur contenant les Montagnes
                for(unsigned int i = 0; i < plateau->getPlateau().size(); i++){
                    ///On parcours le vecteur contenant les Pions
                    for(unsigned int j = 0; j< plateau->getAnimal_plateau().size(); j++){

                        ///Si il y a un Animal sur la case d'au dessus
                        if(Lig - LigInc == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc == plateau->getAnimal_plateau()[j].getColonne_pion() && sortie == 0){
                            //Supprime l'Animal de son ancienne case (affichage)
                            LigP = plateau->getAnimal_plateau()[j].getLigne_pion();
                            ColP = plateau->getAnimal_plateau()[j].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de l'animal
                            VectAnProv = plateau->getAnimal_plateau();
                            VectAnProv[j].setLigne_pion(VectAnProv[j].getLigne_pion()+1);
                            //Si l'Animal sors du plateau
                            if(VectAnProv[j].getLigne_pion() < 1){
                                VectAnProv[j].setLigne_pion(-1);
                                VectAnProv[j].setColonne_pion('#');
                                VectAnProv[j].setPresence_plateau(false);
                                VectAnProv[j].setDirection('n');
                                plateau->setAnimal_plateau(VectAnProv);
                            }
                            //Si l'Animal ne sors pas du Plateau
                            else{
                                LigP = VectAnProv[j].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VectAnProv[j].getNom();
                                std::cout << VectAnProv[j].getDirection();
                            }

                        }
                        ///Si il y a une Montagne sur la case au dessus du Pion
                        else if(Lig - LigInc == plateau->getPlateau()[i].getLigne_pion() && Colc == plateau->getPlateau()[i].getColonne_pion() && sortie == 0){
                            //Supprime la Montagne de son ancienne case (affichage)
                            LigP = plateau->getPlateau()[i].getLigne_pion();
                            ColP = plateau->getPlateau()[i].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de la montagnes
                            VecMoProv = plateau->getPlateau();
                            VecMoProv[i].setLigne_pion(VecMoProv[i].getLigne_pion()-1);
                            //Si le Pions sors du Plateau
                            if(VecMoProv[i].getLigne_pion() < 1){
                                //On sors la monatagne du plateau dans ses attributs
                                VecMoProv[i].setLigne_pion(-1);
                                VecMoProv[i].setColonne_pion('#');
                                VecMoProv[i].setPresence_plateau(false);
                                plateau->setPlateau(VecMoProv);
                            }
                            //Si le Pion ne sors pas du Plateau
                            else{
                                //Affiche la montagne sur sa nouvelle case
                                LigP = VecMoProv[i].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VecMoProv[i].getNom();
                            }
                        }
                        ///Si il n'y a plus de Pions au dessus de l'Animal poussant
                        else if(posPlusUn == 0){
                            //Enleve l'Animal qui pousse de sa case(affichage)
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << "  ";
                            //Change les valeurs de positions de l'Animal
                            m_nb_animal[valPion].setLigne_pion(m_nb_animal[valPion].getLigne_pion()-1);
                            Lig = m_nb_animal[valPion].getLigne_pion();
                            //Affiche l'Animal sur sa nouvelle case
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << m_nb_animal[valPion].getNom() << m_nb_animal[valPion].getDirection();
                            //Sors de la boucle
                            posPlusUn = 1;
                        }
                        LigInc--;
                    }
                }
            }
        }
    }
    ///Si le Pion descend d'une case
    if(choixDeplacement == 2){
        ///On parcour le vecteur contenant les Montagnes
        for(unsigned int i = 0; i < plateau->getPlateau().size(); i++){
            ///On parcours le vecteur contenant les Pions
            for(unsigned int j = 0; j< plateau->getAnimal_plateau().size(); j++){
                //Si il y a un pion sur la case d'au dessous
                            //test
                        /*std::cout << "Position Ligne Pion dessus : " << plateau->getAnimal_plateau()[j].getLigne_pion() << std::endl;
                        std::cout << "Position Ligne Pion pousse : " << Lig << std::endl;
                        std::cout << "Position Colonne Pion dessus : " << plateau->getAnimal_plateau()[j].getColonne_pion() << std::endl;
                        std::cout << "Position Colonne Pion pousse : " << Colc << std::endl;
                        std::cout << "Position LigneTot : " << Lig - LigInc << std::endl;*/

                    if(((Lig + LigInc == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc == plateau->getAnimal_plateau()[j].getColonne_pion())
                        || (Lig + LigInc == plateau->getPlateau()[i].getLigne_pion() && Colc == plateau->getPlateau()[i].getColonne_pion()))
                        && posPlusUn == 0){
                        //Si le Pion est dans la meme direction
                        if(plateau->getAnimal_plateau()[j].getDirection() == 'h'){
                            resistancetot = resistancetot + 1;
                        }
                        //Si le pion est dans la direction opposée
                        else if(plateau->getAnimal_plateau()[j].getDirection() == 'b'){
                            resistancetot = resistancetot - 1;
                        }
                        //Si le Pion est une montagne
                        else if(plateau->getPlateau()[i].getNom() == 'M'){
                            resistancetot = resistancetot - 0.9;
                        }
                        l = Lig;
                        c = Colc;
                    }
                    //Verifie si il manque un Pion sur la case supérieur
                    else if(Lig == l + 1 && Colc == c){
                        posPlusUn = 1;
                    }
                }
            }
            posPlusUn = 1;
            LigInc++;

        if(m_nb_animal[valPion].getDirection() != 'b'){
            resistancetot = -1;
        }
        std::cout << resistancetot << std::endl;
        ///Verifie que la resisance totale permet de bouger
        if(resistancetot > 0){
            sortie = 0;
            LigInc = 1;
            posPlusUn = 0;
            bool Mouvement = true;

            ///Tant qu'il y a des Pions au dessous du Pion initiale sans trou
            while(posPlusUn == 0){

                    //test
                    plateau->DisplayPlateau();
                ///On parcour le vecteur contenant les Montagnes
                for(unsigned int i = 0; i < plateau->getPlateau().size(); i++){
                    ///On parcours le vecteur contenant les Pions
                    for(unsigned int j = 0; j< plateau->getAnimal_plateau().size(); j++){

                        ///Si il y a un Animal sur la case d'au dessous
                        if(Lig + LigInc == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc == plateau->getAnimal_plateau()[j].getColonne_pion() && sortie == 0){
                            //Supprime l'Animal de son ancienne case (affichage)
                            LigP = plateau->getAnimal_plateau()[j].getLigne_pion();
                            ColP = plateau->getAnimal_plateau()[j].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de l'animal
                            VectAnProv = plateau->getAnimal_plateau();
                            VectAnProv[j].setLigne_pion(VectAnProv[j].getLigne_pion()+1);
                            //Si l'Animal sors du plateau
                            if(VectAnProv[j].getLigne_pion() < plateau->getLargeur_plateau()+1){
                                VectAnProv[j].setLigne_pion(-1);
                                VectAnProv[j].setColonne_pion('#');
                                VectAnProv[j].setPresence_plateau(false);
                                VectAnProv[j].setDirection('n');
                                plateau->setAnimal_plateau(VectAnProv);
                            }
                            //Si l'Animal ne sors pas du Plateau
                            else{
                                LigP = VectAnProv[j].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VectAnProv[j].getNom();
                                std::cout << VectAnProv[j].getDirection();
                            }

                        }
                        ///Si il y a une Montagne sur la case au dessous du Pion
                        else if(Lig + LigInc == plateau->getPlateau()[i].getLigne_pion() && Colc == plateau->getPlateau()[i].getColonne_pion() && sortie == 0){
                            //Supprime la Montagne de son ancienne case (affichage)
                            LigP = plateau->getPlateau()[i].getLigne_pion();
                            ColP = plateau->getPlateau()[i].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de la montagnes
                            VecMoProv = plateau->getPlateau();
                            VecMoProv[i].setLigne_pion(VecMoProv[i].getLigne_pion()-1);
                            //Si le Pions sors du Plateau
                            if(VecMoProv[i].getLigne_pion() > plateau->getLargeur_plateau()+1){
                                //On sors la monatagne du plateau dans ses attributs
                                VecMoProv[i].setLigne_pion(-1);
                                VecMoProv[i].setColonne_pion('#');
                                VecMoProv[i].setPresence_plateau(false);
                                plateau->setPlateau(VecMoProv);
                            }
                            //Si le Pion ne sors pas du Plateau
                            else{
                                //Affiche la montagne sur sa nouvelle case
                                LigP = VecMoProv[i].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VecMoProv[i].getNom();
                            }
                        }
                        ///Si il n'y a plus de Pions au dessous de l'Animal poussant
                        else if(posPlusUn == 0){
                            //Enleve l'Animal qui pousse de sa case(affichage)
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << "  ";
                            //Change les valeurs de positions de l'Animal
                            m_nb_animal[valPion].setLigne_pion(m_nb_animal[valPion].getLigne_pion()+1);
                            Lig = m_nb_animal[valPion].getLigne_pion();
                            //Affiche l'Animal sur sa nouvelle case
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << m_nb_animal[valPion].getNom() << m_nb_animal[valPion].getDirection();
                            //Sors de la boucle
                            posPlusUn = 1;
                        }
                    LigInc++;
                    }
                }
            }
        }
    }
    ///Si le Pion va a gauche d'une case
    if(choixDeplacement == 3){
        ///On parcour le vecteur contenant les Montagnes
        for(unsigned int i = plateau->getAnimal_plateau().size(); i > 0; i--){
            ///On parcours le vecteur contenant les Pions
            for(unsigned int j = plateau->getAnimal_plateau().size(); j > 0; j--){
                //Si il y a un Pion à gauche
                            //test
                        /*std::cout << "Position Ligne Pion dessus : " << plateau->getAnimal_plateau()[j].getLigne_pion() << std::endl;
                        std::cout << "Position Ligne Pion pousse : " << Lig << std::endl;
                        std::cout << "Position Colonne Pion dessus : " << plateau->getAnimal_plateau()[j].getColonne_pion() << std::endl;
                        std::cout << "Position Colonne Pion pousse : " << Colc << std::endl;
                        std::cout << "Position LigneTot : " << Lig - LigInc << std::endl;*/

                    if(((Lig == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc - ColInc == plateau->getAnimal_plateau()[j].getColonne_pion())
                        || (Lig == plateau->getPlateau()[i].getLigne_pion() && Colc - ColInc == plateau->getPlateau()[i].getColonne_pion()))
                        && posPlusUn == 0){
                        //Si le Pion est dans la meme direction
                        if(plateau->getAnimal_plateau()[j].getDirection() == 'h'){
                            resistancetot = resistancetot + 1;
                        }
                        //Si le pion est dans la direction opposée
                        else if(plateau->getAnimal_plateau()[j].getDirection() == 'b'){
                            resistancetot = resistancetot - 1;
                        }
                        //Si le Pion est une montagne
                        else if(plateau->getPlateau()[i].getNom() == 'M'){
                            resistancetot = resistancetot - 0.9;
                        }
                        l = Lig;
                        c = Colc;
                    }
                    //Verifie si il manque un Pion sur la case supérieur
                    else if(Lig == l && Colc == c - 1){
                        posPlusUn = 1;
                    }
                }
            }
            LigInc++;

        if(m_nb_animal[valPion].getDirection() != 'g'){
            resistancetot = -1;
        }
        std::cout << resistancetot << std::endl;
        ///Verifie que la resisance totale permet de bouger
        if(resistancetot > 0){
            sortie = 0;
            LigInc = 1;
            posPlusUn = 0;
            bool Mouvement = true;

            ///Tant qu'il y a des Pions au dessous du Pion initiale sans trou
            while(posPlusUn == 0){

                    //test
                    plateau->DisplayPlateau();
                ///On parcour le vecteur contenant les Montagnes
                for(unsigned int i = plateau->getPlateau().size(); i > 0; i++){
                    ///On parcours le vecteur contenant les Pions
                    for(unsigned int j = plateau->getPlateau().size(); j > 0; j++){

                        ///Si il y a un Animal sur la case d'au dessous
                        if(Lig == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc - ColInc == plateau->getAnimal_plateau()[j].getColonne_pion() && sortie == 0){
                            //Supprime l'Animal de son ancienne case (affichage)
                            LigP = plateau->getAnimal_plateau()[j].getLigne_pion();
                            ColP = plateau->getAnimal_plateau()[j].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de l'animal
                            VectAnProv = plateau->getAnimal_plateau();
                            VectAnProv[j].setLigne_pion(VectAnProv[j].getLigne_pion()-1);
                            //Si l'Animal sors du plateau
                            if(VectAnProv[j].getLigne_pion() > 0){
                                VectAnProv[j].setLigne_pion(-1);
                                VectAnProv[j].setColonne_pion('#');
                                VectAnProv[j].setPresence_plateau(false);
                                VectAnProv[j].setDirection('n');
                                plateau->setAnimal_plateau(VectAnProv);
                            }
                            //Si l'Animal ne sors pas du Plateau
                            else{
                                LigP = VectAnProv[j].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VectAnProv[j].getNom();
                                std::cout << VectAnProv[j].getDirection();
                            }

                        }
                        ///Si il y a une Montagne sur la case au dessous du Pion
                        else if(Lig == plateau->getPlateau()[i].getLigne_pion() && Colc - ColInc == plateau->getPlateau()[i].getColonne_pion() && sortie == 0){
                            //Supprime la Montagne de son ancienne case (affichage)
                            LigP = plateau->getPlateau()[i].getLigne_pion();
                            ColP = plateau->getPlateau()[i].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de la montagnes
                            VecMoProv = plateau->getPlateau();
                            VecMoProv[i].setLigne_pion(VecMoProv[i].getLigne_pion()-1);
                            //Si le Pions sors du Plateau
                            if(VecMoProv[i].getLigne_pion() < 0){
                                //On sors la monatagne du plateau dans ses attributs
                                VecMoProv[i].setLigne_pion(-1);
                                VecMoProv[i].setColonne_pion('#');
                                VecMoProv[i].setPresence_plateau(false);
                                plateau->setPlateau(VecMoProv);
                            }
                            //Si le Pion ne sors pas du Plateau
                            else{
                                //Affiche la montagne sur sa nouvelle case
                                LigP = VecMoProv[i].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VecMoProv[i].getNom();
                            }
                        }
                        ///Si il n'y a plus de Pions au dessous de l'Animal poussant
                        else if(posPlusUn == 0){
                            //Enleve l'Animal qui pousse de sa case(affichage)
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << "  ";
                            //Change les valeurs de positions de l'Animal
                            m_nb_animal[valPion].setLigne_pion(m_nb_animal[valPion].getLigne_pion()-1);
                            Lig = m_nb_animal[valPion].getLigne_pion();
                            //Affiche l'Animal sur sa nouvelle case
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << m_nb_animal[valPion].getNom() << m_nb_animal[valPion].getDirection();
                            //Sors de la boucle
                            posPlusUn = 1;
                        }
                    LigInc++;
                    }
                }
            }
        }
    }
    ///Si le Pion va a droite d'une case
    if(choixDeplacement == 4){
        ///On parcour le vecteur contenant les Montagnes
        for(unsigned int i = 0; i < plateau->getPlateau().size(); i++){
            ///On parcours le vecteur contenant les Pions
            for(unsigned int j = 0; j< plateau->getAnimal_plateau().size(); j++){
                //Si il y a un Pion à droite
                            //test
                        /*std::cout << "Position Ligne Pion dessus : " << plateau->getAnimal_plateau()[j].getLigne_pion() << std::endl;
                        std::cout << "Position Ligne Pion pousse : " << Lig << std::endl;
                        std::cout << "Position Colonne Pion dessus : " << plateau->getAnimal_plateau()[j].getColonne_pion() << std::endl;
                        std::cout << "Position Colonne Pion pousse : " << Colc << std::endl;
                        std::cout << "Position LigneTot : " << Lig - LigInc << std::endl;*/

                    if(((Lig == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc + ColInc == plateau->getAnimal_plateau()[j].getColonne_pion())
                        || (Lig == plateau->getPlateau()[i].getLigne_pion() && Colc + ColInc == plateau->getPlateau()[i].getColonne_pion()))
                        && posPlusUn == 0){
                        //Si le Pion est dans la meme direction
                        if(plateau->getAnimal_plateau()[j].getDirection() == 'h'){
                            resistancetot = resistancetot + 1;
                        }
                        //Si le pion est dans la direction opposée
                        else if(plateau->getAnimal_plateau()[j].getDirection() == 'b'){
                            resistancetot = resistancetot - 1;
                        }
                        //Si le Pion est une montagne
                        else if(plateau->getPlateau()[i].getNom() == 'M'){
                            resistancetot = resistancetot - 0.9;
                        }
                        l = Lig;
                        c = Colc;
                    }
                    //Verifie si il manque un Pion sur la case supérieur
                    else if(Lig == l && Colc == c + 1){
                        posPlusUn = 1;
                    }
                }
            }
            LigInc++;

        if(m_nb_animal[valPion].getDirection() != 'd'){
            resistancetot = -1;
        }
        std::cout << resistancetot << std::endl;
        ///Verifie que la resisance totale permet de bouger
        if(resistancetot > 0){
            sortie = 0;
            LigInc = 1;
            posPlusUn = 0;
            bool Mouvement = true;

            ///Tant qu'il y a des Pions au dessous du Pion initiale sans trou
            while(posPlusUn == 0){

                    //test
                    plateau->DisplayPlateau();
                ///On parcour le vecteur contenant les Montagnes
                for(unsigned int i = plateau->getPlateau().size(); i > 0; i++){
                    ///On parcours le vecteur contenant les Pions
                    for(unsigned int j = plateau->getPlateau().size(); j > 0; j++){

                        ///Si il y a un Animal sur la case d'au dessous
                        if(Lig == plateau->getAnimal_plateau()[j].getLigne_pion() && Colc + ColInc == plateau->getAnimal_plateau()[j].getColonne_pion() && sortie == 0){
                            //Supprime l'Animal de son ancienne case (affichage)
                            LigP = plateau->getAnimal_plateau()[j].getLigne_pion();
                            ColP = plateau->getAnimal_plateau()[j].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de l'animal
                            VectAnProv = plateau->getAnimal_plateau();
                            VectAnProv[j].setLigne_pion(VectAnProv[j].getLigne_pion()+1);
                            //Si l'Animal sors du plateau
                            if(VectAnProv[j].getLigne_pion() < plateau->getLongueur_plateau()){
                                VectAnProv[j].setLigne_pion(-1);
                                VectAnProv[j].setColonne_pion('#');
                                VectAnProv[j].setPresence_plateau(false);
                                VectAnProv[j].setDirection('n');
                                plateau->setAnimal_plateau(VectAnProv);
                            }
                            //Si l'Animal ne sors pas du Plateau
                            else{
                                LigP = VectAnProv[j].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VectAnProv[j].getNom();
                                std::cout << VectAnProv[j].getDirection();
                            }

                        }
                        ///Si il y a une Montagne sur la case au dessous du Pion
                        else if(Lig == plateau->getPlateau()[i].getLigne_pion() && Colc + ColInc == plateau->getPlateau()[i].getColonne_pion() && sortie == 0){
                            //Supprime la Montagne de son ancienne case (affichage)
                            LigP = plateau->getPlateau()[i].getLigne_pion();
                            ColP = plateau->getPlateau()[i].getColonne_pion() + 96;
                            pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                            std::cout << "  ";
                            //Change les positions de la montagnes
                            VecMoProv = plateau->getPlateau();
                            VecMoProv[i].setLigne_pion(VecMoProv[i].getLigne_pion()+1);
                            //Si le Pions sors du Plateau
                            if(VecMoProv[i].getLigne_pion() > plateau->getLongueur_plateau()){
                                //On sors la monatagne du plateau dans ses attributs
                                VecMoProv[i].setLigne_pion(-1);
                                VecMoProv[i].setColonne_pion('#');
                                VecMoProv[i].setPresence_plateau(false);
                                plateau->setPlateau(VecMoProv);
                            }
                            //Si le Pion ne sors pas du Plateau
                            else{
                                //Affiche la montagne sur sa nouvelle case
                                LigP = VecMoProv[i].getLigne_pion();
                                pConsole->gotoLigCol(LigP*2 + 1, ColP*2 + ColP);
                                std::cout << VecMoProv[i].getNom();
                            }
                        }
                        ///Si il n'y a plus de Pions au dessous de l'Animal poussant
                        else if(posPlusUn == 0){
                            //Enleve l'Animal qui pousse de sa case(affichage)
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << "  ";
                            //Change les valeurs de positions de l'Animal
                            m_nb_animal[valPion].setLigne_pion(m_nb_animal[valPion].getLigne_pion()+1);
                            Lig = m_nb_animal[valPion].getLigne_pion();
                            //Affiche l'Animal sur sa nouvelle case
                            pConsole->gotoLigCol(Lig*2 + 1, Col*2 + Col);
                            std::cout << m_nb_animal[valPion].getNom() << m_nb_animal[valPion].getDirection();
                            //Sors de la boucle
                            posPlusUn = 1;
                        }
                    LigInc++;
                    }
                }
            }
        }
    }

    pConsole->deleteInstance();
    return Mouvement;
}

void Joueur::changer_orientation( int i)
{
            char direction ;
            std::cout << "Si vous voulez changer l'orientation :"<<std::endl;
            std::cout << "Entrez 'h' si vous voulez vous diriger vers le haut"<<std::endl;
            std::cout << "Entrez 'b' si vous voulez vous diriger vers le bas"<<std::endl;
            std::cout << "Entrez 'd' si vous voulez vous diriger vers la droite"<<std::endl;
            std::cout << "Entrez 'g' si vous voulez vous diriger vers la gauche"<<std::endl;
            std::cin>> direction;
            std::cout << std::endl; /// AVERIFIER
            if(direction == 'h'){
                m_nb_animal[i].setDirection('h');
            }
            if(direction == 'b'){
                m_nb_animal[i].setDirection('b');
            }
            if(direction == 'd'){
                m_nb_animal[i].setDirection('d');
            }
            if(direction == 'g'){
                m_nb_animal[i].setDirection('g');
            }
            else
            {
                std::cout<< "Veuillez ressaisir l'orientation de votre pion"<<std:: endl;
            }
}
//Méthodes de test
void Joueur::DisplayJoueur(){
    std::cout << std::endl;
    std::cout << "Nom Joueur : " << m_nom_joueur << std::endl;
    std::cout << "Nb animal : " << m_nb_animal.size() << std::endl;
    for(unsigned int i = 0; i < m_nb_animal.size(); i++){
        m_nb_animal[i].DisplayAnimal();
    }
}

///Getter & Setter
//Getter
std::vector <Animal> Joueur::getNb_animal(){
    return m_nb_animal;
}

std::string Joueur::getNom_joueur(){
    return m_nom_joueur;
}

int Joueur::getNb_presence_animal_plateau(){
    return m_nb_presence_animal_plateau;
}

//Setter
void Joueur::setNb_animal(std::vector <Animal> nb_animal){
    m_nb_animal = nb_animal;
}

void Joueur::setNom_joueur(std::string nom_joueur){
    m_nom_joueur = nom_joueur;
}

void Joueur::setNb_presence_animal_plateau(int nb_presence_animal_plateau){
    m_nb_presence_animal_plateau = nb_presence_animal_plateau;
}
