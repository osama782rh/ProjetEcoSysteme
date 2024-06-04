#include "Animal.h"
#include "Univers.h"
#include "Mouton.h"
#include "Loup.h"
#include <cstdlib>
#include <climits>

using namespace std;

Animal::Animal(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age)
    : Entite(x, y, symbole, faimMax, ageMax, ageMaturite, faim, age) {
    this->sexe = (rand() % 2 == 0) ? 'M' : 'F';
}

void Animal::resetFaim() {
    faim = 0;
}

void Animal::deplacementAleatoire(Univers& univers) {
    int newX = x + (rand() % 3 - 1);
    int newY = y + (rand() % 3 - 1);
    if (univers.positionValide(newX, newY)) {
        auto cible = univers.obtenirEntite(newX, newY);
        if (cible == nullptr) {
            univers.deplacerEntite(shared_from_this(), newX, newY);
        } else if (symbole == 'M' && cible->getSymbole() == 'H') {
            univers.retirerEntite(newX, newY);
            univers.deplacerEntite(shared_from_this(), newX, newY);
            faim = 0;
            univers.enregistrerEvenement("Un mouton a mangé de l'herbe.", newX, newY);
        } else if (symbole == 'L' && cible->getSymbole() == 'M') {
            univers.retirerEntite(newX, newY);
            univers.deplacerEntite(shared_from_this(), newX, newY);
            faim = 0;
            univers.enregistrerEvenement("Un mouton a été mangé par un loup.", newX, newY);
        }
    }
}

std::pair<int, int> Animal::trouverNourritureProche(const Univers& univers, char symboleNourriture) const {
    int minDistance = INT_MAX;
    int targetX = -1, targetY = -1;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int newX = x + dx;
            int newY = y + dy;
            if (univers.positionValide(newX, newY)) {
                auto entite = univers.obtenirEntite(newX, newY);
                if (entite && entite->getSymbole() == symboleNourriture) {
                    int distance = abs(newX - x) + abs(newY - y);
                    if (distance < minDistance) {
                        minDistance = distance;
                        targetX = newX;
                        targetY = newY;
                    }
                }
            }
        }
    }
    return std::make_pair(targetX, targetY);
}

pair<int, int> Animal::isAdjacentToMate(const Univers& univers, char symbol) const {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx != 0 || dy != 0) {
                int newX = x + dx;
                int newY = y + dy;
                if (univers.positionValide(newX, newY)) {
                    auto entite = univers.obtenirEntite(newX, newY);
                    if (entite && entite->getSymbole() == symbol && entite->getSexe() != getSexe() && entite->peutSeReproduire()) {
                        return std::make_pair(newX, newY);
                    }
                }
            }
        }
    }
    return std::make_pair(-1, -1);
}

void Animal::reproduire(Univers& univers, int mateX, int mateY) {
    if (age >= ageMaturite && faim < faimMax / 2) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = x + dx;
                int newY = y + dy;
                if (univers.positionValide(newX, newY) && univers.estVide(newX, newY)) {
                    std::shared_ptr<Animal> nouveau;
                    if (symbole == 'M') {
                        auto mouton = std::make_shared<Mouton>(newX, newY, (rand() % 2 == 0) ? 'M' : 'F', 0, faimMax, 0, ageMax);
                        nouveau = std::dynamic_pointer_cast<Animal>(mouton);
                    } else if (symbole == 'L') {
                        auto loup = std::make_shared<Loup>(newX, newY, (rand() % 2 == 0) ? 'M' : 'F', 0, faimMax, 0, ageMax);
                        nouveau = std::dynamic_pointer_cast<Animal>(loup);
                    }
                    univers.ajouterEntite(nouveau, newX, newY);
                    univers.enregistrerEvenement("Un nouveau " + std::string(1, symbole) + " est né.", newX, newY);
                    return;
                }
            }
        }
    }
}
