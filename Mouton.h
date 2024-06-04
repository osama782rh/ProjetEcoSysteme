#ifndef MOUTON_H
#define MOUTON_H

#include "Animal.h"

class Mouton : public Animal {
public:
    Mouton(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax);
    void action(Univers& univers) override;
};

#endif // MOUTON_H
