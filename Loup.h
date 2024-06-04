#ifndef LOUP_H
#define LOUP_H

#include "Animal.h"

class Loup : public Animal {
public:
    Loup(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax);
    void action(Univers& univers) override;
};

#endif // LOUP_H
