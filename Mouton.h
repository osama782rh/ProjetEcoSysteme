#ifndef MOUTON_H
#define MOUTON_H

#include "Animal.h"
#include <memory>

// Classe Mouton héritant de Animal
class Mouton : public Animal {
public:
    Mouton(int x, int y, char sexe, int faim = 0, int faimMax = 5, int age = 0, int ageMax = 50); // Constructeur
    void action(Univers& univers) override; // Méthode action
};

#endif
