#include "SelsMineraux.h"
#include "Univers.h"
#include "Herbe.h"

SelsMineraux::SelsMineraux(int x, int y, int dureeTransformation)
    : Entite(x, y, 'S', 0, dureeTransformation, 0, 0, 0), dureeTransformation(dureeTransformation) {}

void SelsMineraux::action(Univers& univers) {
    age++;
    if (univers.getModeDeplacement() == INTELLIGENT || age >= dureeTransformation) {
        univers.retirerEntite(getX(), getY());
        auto herbe = std::make_shared<Herbe>(getX(), getY());
        univers.ajouterEntite(herbe, getX(), getY());
        univers.enregistrerEvenement("Les sels minéraux se sont transformés en herbe.", getX(), getY());
    }
}
