#include "Herbe.h"
#include "Univers.h"

Herbe::Herbe(int x, int y)
    : Entite(x, y, 'H', 0, 0, 0, 0, 0) {}

void Herbe::action(Univers& univers) {
    // Rien à faire pour l'herbe pour l'instant
}
