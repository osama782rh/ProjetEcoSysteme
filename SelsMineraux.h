#ifndef SELS_MINERAUX_H
#define SELS_MINERAUX_H

#include "Entite.h"

class SelsMineraux : public Entite {
public:
    SelsMineraux(int x, int y, int dureeTransformation);
    void action(Univers& univers) override;
private:
    int dureeTransformation;
};

#endif
