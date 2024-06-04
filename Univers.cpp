#include "Univers.h"
#include "Entite.h"
#include "Animal.h"
#include "Mouton.h"
#include "Loup.h"
#include "Herbe.h"
#include "SelsMineraux.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

Univers::Univers(int largeur, int hauteur, ModeDeplacement mode)
    : largeur(largeur), hauteur(hauteur), nombreLoups(0), nombreMoutons(0), modeDeplacement(mode), grille(largeur, std::vector<std::shared_ptr<Entite>>(hauteur, nullptr)) {
}

ModeDeplacement Univers::getModeDeplacement() const {
    return modeDeplacement;
}

void Univers::afficherEvenements() const {
    for (const auto& evenement : evenements) {
        cout << evenement << endl;
    }
    cout << endl;
}

void Univers::nettoyerEvenements() {
    evenements.clear();
}

void Univers::avancerTour() {
    nettoyerEvenements(); // Effacer les événements du tour précédent
    std::vector<std::shared_ptr<Entite>> entitesActives;

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (grille[x][y] != nullptr) {
                entitesActives.push_back(grille[x][y]);
            }
        }
    }

    for (const auto& entite : entitesActives) {
        if (entite->estVivante()) {
            entite->action(*this);
            if (entite->doitEtreRetiree()) {
                enregistrerEvenement(entite->getSymbole() == 'M' ? "Un mouton meurt de faim." : "Un loup meurt de vieillesse.", entite->getX(), entite->getY());
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
        exit(0);
    }
}

bool Univers::positionValide(int x, int y) const {
    return x >= 0 && x < largeur && y >= 0 && y < hauteur;
}

bool Univers::estVide(int x, int y) const {
    return positionValide(x, y) && grille[x][y] == nullptr;
}

std::shared_ptr<Entite> Univers::obtenirEntite(int x, int y) const {
    if (positionValide(x, y)) {
        return grille[x][y];
    }
    return nullptr;
}

void Univers::deplacerEntite(const std::shared_ptr<Entite>& entite, int newX, int newY) {
    if (entite && positionValide(newX, newY)) {
        auto cible = obtenirEntite(newX, newY);
        if (cible == nullptr) {
            // Si la case est vide, déplace l'entité
            int oldX = entite->getX();
            int oldY = entite->getY();
            grille[oldX][oldY] = nullptr;

            entite->setX(newX);
            entite->setY(newY);
            grille[newX][newY] = entite;
        } else {
            // Si la case n'est pas vide, gère le conflit
            gererConflit(entite, cible, newX, newY);
        }
    }
}

void Univers::gererConflit(const std::shared_ptr<Entite>& entite, const std::shared_ptr<Entite>& cible, int newX, int newY) {
    if (entite->getSymbole() == 'L' && cible->getSymbole() == 'M') {
        // Le loup mange le mouton
        retirerEntite(newX, newY);
        grille[entite->getX()][entite->getY()] = nullptr;
        entite->setX(newX);
        entite->setY(newY);
        grille[newX][newY] = entite;
        dynamic_pointer_cast<Animal>(entite)->resetFaim();
        enregistrerEvenement("Un mouton a été mangé par un loup.", newX, newY);
    } else if (entite->getSymbole() == 'M' && cible->getSymbole() == 'H') {
        // Le mouton mange l'herbe
        retirerEntite(newX, newY);
        grille[entite->getX()][entite->getY()] = nullptr;
        entite->setX(newX);
        entite->setY(newY);
        grille[newX][newY] = entite;
        dynamic_pointer_cast<Animal>(entite)->resetFaim();
        enregistrerEvenement("Un mouton a mangé de l'herbe.", newX, newY);
    }
}

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

void Univers::enregistrerEvenement(const std::string& evenement, int x, int y) {
    std::string position = "[" + std::string(1, 'A' + y) + std::to_string(x + 1) + "]";
    evenements.push_back(position + " " + evenement);
}

void Univers::afficher() const {
    cout << "   ";
    for (int x = 0; x < largeur; ++x) {
        cout << " " << x + 1 << "  ";
    }
    cout << "\n  ";
    for (int x = 0; x < largeur; ++x) {
        cout << "+---";
    }
    cout << "+\n";

    for (int y = 0; y < hauteur; ++y) {
        cout << char('A' + y) << " ";
        for (int x = 0; x < largeur; ++x) {
            cout << "| ";
            if (grille[x][y] == nullptr) {
                cout << " ";
            } else {
                cout << grille[x][y]->getSymbole();
            }
            cout << " ";
        }
        cout << "|\n  ";
        for (int x = 0; x < largeur; ++x) {
            cout << "+---";
        }
        cout << "+\n";
    }

    afficherEvenements();
}

int Univers::getNombreLoups() const {
    // Réinitialiser le compteur de loups
    int compteurLoups = 0;
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (grille[x][y] != nullptr && grille[x][y]->getSymbole() == 'L') {
                compteurLoups++;
            }
        }
    }
    return compteurLoups;
}

int Univers::getNombreMoutons() const {
    // Réinitialiser le compteur de moutons
    int compteurMoutons = 0;
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (grille[x][y] != nullptr && grille[x][y]->getSymbole() == 'M') {
                compteurMoutons++;
            }
        }
    }
    return compteurMoutons;
}
