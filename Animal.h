#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entite.h"
#include <utility>

class Animal : public Entite {
public:
    Animal(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age);
    void resetFaim(); // Ajout de la méthode resetFaim

protected:
    void deplacementAleatoire(Univers& univers);
    std::pair<int, int> trouverNourritureProche(const Univers& univers, char symboleNourriture) const;
    std::pair<int, int> isAdjacentToMate(const Univers& univers, char symbol) const;
    void reproduire(Univers& univers, int mateX, int mateY);
};

#endif // ANIMAL_H
