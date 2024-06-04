#ifndef SELSMINERAUX_H
#define SELSMINERAUX_H

#include "Entite.h"

class SelsMineraux : public Entite {
public:
    SelsMineraux(int x, int y, int dureeTransformation);
    void action(Univers& univers) override;

private:
    int dureeTransformation;
};

#endif // SELSMINERAUX_H
