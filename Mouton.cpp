#include "Mouton.h"
#include "Univers.h"
#include <cstdlib>
#include <climits>

Mouton::Mouton(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax)
    : Animal(x, y, 'M', faimMax, ageMax, 5, faim, age) {
    this->sexe = sexe;
}

void Mouton::action(Univers& univers) {
    vieillirEtAugmenterFaim();
    if (!estVivante()) {
        return;
    }

    bool deplace = false;

    if (univers.getModeDeplacement() == INTELLIGENT) {
        auto matePosition = isAdjacentToMate(univers, getSymbole());
        if (matePosition.first != -1 && matePosition.second != -1) {
            reproduire(univers, matePosition.first, matePosition.second);
            deplace = true;
        }

        if (!deplace) {
            auto herbePosition = trouverNourritureProche(univers, 'H');
            if (herbePosition.first != -1 && herbePosition.second != -1) {
                univers.retirerEntite(herbePosition.first, herbePosition.second);
                univers.deplacerEntite(shared_from_this(), herbePosition.first, herbePosition.second);
                resetFaim();
                univers.enregistrerEvenement("Un mouton a mangé de l'herbe.", herbePosition.first, herbePosition.second);
                deplace = true;
            }
        }

        if (!deplace) {
            deplacementAleatoire(univers);
        }
    } else {
        deplacementAleatoire(univers);
    }
}
