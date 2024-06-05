#include "Univers.h"
#include "Entite.h"
#include "Mouton.h"
#include "Loup.h"
#include "SelsMineraux.h"
#include "Herbe.h"
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

// Définition de l'opérateur de flux d'entrée pour ModeDeplacement
std::istream& operator>>(std::istream& in, ModeDeplacement& mode) {
    int val;
    in >> val;
    mode = static_cast<ModeDeplacement>(val);
    return in;
}

// Constructeur de la classe Univers
Univers::Univers(int largeur, int hauteur, ModeDeplacement mode)
    : largeur(largeur), hauteur(hauteur), nombreLoups(0), nombreMoutons(0), modeDeplacement(mode), grille(largeur, std::vector<std::shared_ptr<Entite>>(hauteur, nullptr)) {
}

// Retourne le mode de déplacement actuel
ModeDeplacement Univers::getModeDeplacement() const {
    return modeDeplacement;
}

// Affiche tous les événements enregistrés
void Univers::afficherEvenements() const {
    for (const auto& evenement : evenements) {
        std::cout << evenement << std::endl;
    }
    std::cout << std::endl;
}

// Efface tous les événements enregistrés
void Univers::nettoyerEvenements() {
    evenements.clear();
}

// Avance d'un tour dans la simulation
void Univers::avancerTour() {
    nettoyerEvenements(); // Effacer les événements du tour précédent
    std::vector<std::shared_ptr<Entite>> entitesActives;

    // Collecter toutes les entités actives
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (grille[x][y] != nullptr) {
                entitesActives.push_back(grille[x][y]);
            }
        }
    }

    // Exécuter l'action pour chaque entité active
    for (const auto& entite : entitesActives) {
        if (entite->estVivante()) {
            entite->action(*this);
            if (entite->doitEtreRetiree()) {
                enregistrerEvenement(entite->getSymbole() == 'M' ? "Un mouton meurt de faim." : "Un loup meurt de faim.", entite->getX(), entite->getY());
                // Ajouter des sels minéraux à la place de l'animal mort
                auto selsMineraux = std::make_shared<SelsMineraux>(entite->getX(), entite->getY(), 3);
                retirerEntite(entite->getX(), entite->getY());
                ajouterEntite(selsMineraux, entite->getX(), entite->getY());
            }
        }
    }

    // Vérification de la fin du jeu
    if (nombreLoups == 0 && nombreMoutons == 0) {
        std::cout << "Tous les animaux sont morts. Fin de la simulation." << std::endl;
    }
}

// Vérifie si une position est valide
bool Univers::positionValide(int x, int y) const {
    return x >= 0 && x < largeur && y >= 0 && y < hauteur;
}

// Vérifie si une position est vide
bool Univers::estVide(int x, int y) const {
    return positionValide(x, y) && grille[x][y] == nullptr;
}

// Obtient une entité à une position donnée
std::shared_ptr<Entite> Univers::obtenirEntite(int x, int y) const {
    if (positionValide(x, y)) {
        return grille[x][y];
    }
    return nullptr;
}

// Retire une entité d'une position donnée
void Univers::retirerEntite(int x, int y) {
    if (positionValide(x, y) && grille[x][y] != nullptr) {
        if (grille[x][y]->getSymbole() == 'M') {
            nombreMoutons--;
        } else if (grille[x][y]->getSymbole() == 'L') {
            nombreLoups--;
        }
        grille[x][y] = nullptr;
    }
}

// Déplace une entité à une nouvelle position
void Univers::deplacerEntite(const std::shared_ptr<Entite>& entite, int newX, int newY) {
    if (entite && positionValide(newX, newY) && estVide(newX, newY)) {
        int oldX = entite->getX();
        int oldY = entite->getY();
        grille[oldX][oldY] = nullptr;
        entite->setX(newX);
        entite->setY(newY);
        grille[newX][newY] = entite;
    }
}

// Ajoute une entité à une position donnée
void Univers::ajouterEntite(const std::shared_ptr<Entite>& entite, int x, int y) {
    if (positionValide(x, y) && estVide(x, y)) {
        if (entite->getSymbole() == 'M') {
            nombreMoutons++;
        } else if (entite->getSymbole() == 'L') {
            nombreLoups++;
        }
        grille[x][y] = entite;
    }
}

// Enregistre un événement
void Univers::enregistrerEvenement(const std::string& evenement, int x, int y) {
    std::string position = "[" + std::string(1, 'A' + y) + std::to_string(x + 1) + "]";
    evenements.push_back(position + " " + evenement);
}

// Affiche l'état actuel de l'univers
void Univers::afficher() const {
    // Affichage des indices de colonnes avec plus d'espace
    std::cout << "   ";
    for (int x = 0; x < largeur; ++x) {
        std::cout << " " << x + 1 << "  ";
    }
    std::cout << "\n  ";
    for (int x = 0; x < largeur; ++x) {
        std::cout << "+---";
    }
    std::cout << "+\n";

    // Affichage de la grille avec les entités
    for (int y = 0; y < hauteur; ++y) {
        std::cout << char('A' + y) << " ";
        for (int x = 0; x < largeur; ++x) {
            std::cout << "| ";
            if (grille[x][y] == nullptr) {
                std::cout << " ";
            } else {
                std::cout << grille[x][y]->getSymbole();
            }
            std::cout << " ";
        }
        std::cout << "|\n  ";
        for (int x = 0; x < largeur; ++x) {
            std::cout << "+---";
        }
        std::cout << "+\n";
    }

    afficherEvenements();
}

// Sauvegarde l'état actuel de l'univers dans un fichier
void Univers::sauvegarder(const std::string& fichier) const {
    std::ofstream ofs(fichier);
    if (ofs) {
        ofs << largeur << " " << hauteur << " " << static_cast<int>(modeDeplacement) << "\n";
        for (int x = 0; x < largeur; ++x) {
            for (int y = 0; y < hauteur; ++y) {
                if (grille[x][y] != nullptr) {
                    ofs << grille[x][y]->getSymbole() << " " << x << " " << y << " " << grille[x][y]->getAge() << " " << grille[x][y]->getFaim() << "\n";
                }
            }
        }
    }
}

// Charge l'état de l'univers à partir d'un fichier
void Univers::charger(const std::string& fichier) {
    std::ifstream ifs(fichier);
    if (ifs) {
        ifs >> largeur >> hauteur >> modeDeplacement;
        grille = std::vector<std::vector<std::shared_ptr<Entite>>>(largeur, std::vector<std::shared_ptr<Entite>>(hauteur, nullptr));
        nombreLoups = 0;
        nombreMoutons = 0;
        char symbole;
        int x, y, age, faim;
        while (ifs >> symbole >> x >> y >> age >> faim) {
            std::shared_ptr<Entite> entite;
            if (symbole == 'M') {
                entite = std::make_shared<Mouton>(x, y, 'M', faim, 5, age, 50);
                nombreMoutons++;
            } else if (symbole == 'L') {
                entite = std::make_shared<Loup>(x, y, 'M', faim, 10, age, 60);
                nombreLoups++;
            } else if (symbole == 'H') {
                entite = std::make_shared<Herbe>(x, y);
            } else if (symbole == 'S') {
                entite = std::make_shared<SelsMineraux>(x, y, 3);
            }
            grille[x][y] = entite;
        }
    }
}

// Retourne le nombre de loups dans l'univers
int Univers::getNombreLoups() const {
    return nombreLoups;
}

// Retourne le nombre de moutons dans l'univers
int Univers::getNombreMoutons() const {
    return nombreMoutons;
}
