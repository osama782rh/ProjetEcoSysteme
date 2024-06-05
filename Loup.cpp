#include "Loup.h"
#include "Univers.h"

using namespace std;

// Constructeur de Loup
Loup::Loup(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax)
    : Animal(x, y, 'L', faimMax, ageMax, 10, faim, age) {
    this->sexe = sexe;
}

// Méthode action pour Loup
void Loup::action(Univers& univers) {
    vieillirEtAugmenterFaim();
    if (!estVivante()) {
        return;
    }

    
    if (univers.getModeDeplacement() == INTELLIGENT) {
        auto moutonPosition = trouverNourritureProche(univers, 'M');
        if (moutonPosition.first != -1 && moutonPosition.second != -1) {
            univers.deplacerEntite(shared_from_this(), moutonPosition.first, moutonPosition.second);
            faim = 0;
            univers.retirerEntite(moutonPosition.first, moutonPosition.second);
            univers.enregistrerEvenement("Un mouton a été mangé par un loup.", moutonPosition.first, moutonPosition.second);
        }
    } else {
        deplacementAleatoire(univers);
    }
}
