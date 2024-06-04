#ifndef HERBE_H
#define HERBE_H

#include "Entite.h"
#include <memory>

class Herbe : public Entite {
public:
    Herbe(int x, int y);
    void action(Univers& univers) override; 
};

#endif // HERBE_H
