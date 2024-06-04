#ifndef ENTITE_H
#define ENTITE_H

#include <memory>

class Univers;

class Entite : public std::enable_shared_from_this<Entite> {
public:
    Entite(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim, int age);

    char getSymbole() const;
    bool estVivante() const;
    bool doitEtreRetiree() const;
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    char getSexe() const;
    bool peutSeReproduire() const;
    int getAge() const;
    int getFaim() const;

    virtual void action(Univers& univers) = 0;
    virtual void vieillirEtAugmenterFaim();

protected:
    int x, y;
    char symbole;
    char sexe;
    int faimMax;
    int ageMax;
    int ageMaturite;
    int faim;
    int age;
    bool vivant;
    int toursDepuisReproduction;

    void resetReproduction();
};

#endif // ENTITE_H
