#include <fstream>
#include <iostream>
#include "fichier.h"

// Lire un fichier ligne par ligne
// Entrée : le chemin d'accès au fichier
void readFile(const std::string& path)
{
    std::ifstream ifs(path.c_str());
    if (ifs) // test si le fichier est bien ouvert
    {
        std::string line;
        while (std::getline(ifs, line)) // lecture ligne par ligne
        {
            std::cout << line << std::endl;
        }
        std::cout << "Reading " << path << " => OK" << std::endl;
        ifs.close(); // fermeture du flux
    }
    else // en cas d'erreur...
    {
        std::cout << "Cannot read " << path << std::endl;
    }
}
