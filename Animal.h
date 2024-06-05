#pragma once

#include "Entite.h"
#include <memory>

// Déclaration avancée de la classe Univers
class Univers;

// Classe Animal héritant de Entite et utilisant enable_shared_from_this
class Animal : public Entite, public std::enable_shared_from_this<Animal> {
public:
    Animal(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age);
    virtual void action(Univers& univers) override = 0; // Méthode action virtuelle pure

protected:
    std::pair<int, int> trouverNourritureProche(const Univers& univers, char symboleNourriture) const; // Trouver la nourriture la plus proche
    void deplacementAleatoire(Univers& univers); // Déplacement aléatoire
    void reproduire(Univers& univers, int mateX, int mateY); // Reproduction
};
