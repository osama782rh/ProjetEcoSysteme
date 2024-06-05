#ifndef HERBE_H
#define HERBE_H

#include "Entite.h"
#include <memory>

// Classe Herbe héritant de Entite
class Herbe : public Entite {
public:
    Herbe(int x, int y); // Constructeur
    void action(Univers& univers) override; // Méthode action
};

#endif
