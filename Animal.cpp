#include "Animal.h"
#include "Univers.h"
#include <climits>

using namespace std;

// Constructeur de la classe Animal
Animal::Animal(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age)
    : Entite(x, y, symbole, faimMax, ageMax, ageMaturite, faim, age) {
    this->sexe = (rand() % 2 == 0) ? 'M' : 'F'; // Assigne un sexe aléatoire si non spécifié
}

// Méthode pour déplacement aléatoire
void Animal::deplacementAleatoire(Univers& univers) {
    int newX = x + (rand() % 3 - 1);
    int newY = y + (rand() % 3 - 1);
    if (univers.positionValide(newX, newY) && univers.estVide(newX, newY)) {
        univers.deplacerEntite(shared_from_this(), newX, newY);
    }
}

// Méthode pour trouver la nourriture la plus proche
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
