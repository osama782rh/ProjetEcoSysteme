#include "Entite.h"

Entite::Entite(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age)
    : x(x), y(y), symbole(symbole), faimMax(faimMax), ageMax(ageMax), ageMaturite(ageMaturite), faim(faim), age(age), vivant(true), toursDepuisReproduction(0) {}

char Entite::getSymbole() const {
    return symbole;
}

bool Entite::estVivante() const {
    return vivant;
}

bool Entite::doitEtreRetiree() const {
    return !vivant;
}

int Entite::getX() const {
    return x;
}

int Entite::getY() const {
    return y;
}

void Entite::setX(int x) {
    this->x = x;
}

void Entite::setY(int y) {
    this->y = y;
}

char Entite::getSexe() const {
    return sexe;
}

bool Entite::peutSeReproduire() const {
    return age >= ageMaturite && faim < faimMax / 2 && toursDepuisReproduction >= 3;
}

int Entite::getAge() const { 
    return age;
}

int Entite::getFaim() const { 
    return faim;
}

void Entite::vieillirEtAugmenterFaim() {
    age++;
    faim++;
    toursDepuisReproduction++;
    if (faim > faimMax || age > ageMax) {
        vivant = false;
    }
}

void Entite::resetReproduction() {
    toursDepuisReproduction = 0;
}
