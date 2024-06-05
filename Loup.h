#ifndef LOUP_H
#define LOUP_H

#include "Animal.h"
#include <memory>

// Classe Loup héritant de Animal
class Loup : public Animal {
public:
    Loup(int x, int y, char sexe, int faim = 0, int faimMax = 10, int age = 0, int ageMax = 60); // Constructeur
    void action(Univers& univers) override; // Méthode action
};

#endif
