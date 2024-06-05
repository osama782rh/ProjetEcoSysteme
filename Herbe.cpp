#include "Herbe.h"
#include "Univers.h"

using namespace std;

// Constructeur de Herbe
Herbe::Herbe(int x, int y)
    : Entite(x, y, 'H', 0, 0, 0, 0, 0) {}

// Méthode action pour Herbe
void Herbe::action(Univers& univers) {
    // Rien à faire pour l'herbe pour l'instant
}
