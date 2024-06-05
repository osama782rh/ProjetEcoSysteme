#include "Mouton.h"
#include "Univers.h"

using namespace std;

// Constructeur de Mouton
Mouton::Mouton(int x, int y, char sexe, int faim, int faimMax, int age, int ageMax)
    : Animal(x, y, 'M', faimMax, ageMax, 5, faim, age) {
    this->sexe = sexe;
}

// Méthode action pour Mouton
void Mouton::action(Univers& univers) {
    vieillirEtAugmenterFaim();
    if (!estVivante()) {
        return;
    }

    
    if (univers.getModeDeplacement() == INTELLIGENT) {
        auto herbePosition = trouverNourritureProche(univers, 'H');
        if (herbePosition.first != -1 && herbePosition.second != -1) {
            univers.deplacerEntite(shared_from_this(), herbePosition.first, herbePosition.second);
            faim = 0;
            univers.retirerEntite(herbePosition.first, herbePosition.second);
            univers.enregistrerEvenement("Un mouton a mangé de l'herbe.", herbePosition.first, herbePosition.second);
        }
    } else {
        deplacementAleatoire(univers);
    }
}
