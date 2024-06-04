#include "Loup.h"
#include "Univers.h"
#include <cstdlib>
#include <climits>

Loup::Loup(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax)
    : Animal(x, y, 'L', faimMax, ageMax, 10, faim, age) {
    this->sexe = sexe;
}

void Loup::action(Univers& univers) {
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
            auto moutonPosition = trouverNourritureProche(univers, 'M');
            if (moutonPosition.first != -1 && moutonPosition.second != -1) {
                univers.retirerEntite(moutonPosition.first, moutonPosition.second);
                univers.deplacerEntite(shared_from_this(), moutonPosition.first, moutonPosition.second);
                resetFaim();
                univers.enregistrerEvenement("Un mouton a été mangé par un loup.", moutonPosition.first, moutonPosition.second);
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
