#pragma once

class Univers; // Déclaration avancée

class Entite {
public:
    Entite(int x, int y, char symbole, int faimMax, int ageMax, int ageMaturite, int faim = 0, int age = 0);
    virtual ~Entite() = default;

    virtual void action(Univers& univers) = 0;
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
    void vieillirEtAugmenterFaim();

protected:
    int x, y;
    char symbole;
    int faimMax, ageMax, ageMaturite;
    int faim, age;
    bool vivant;
    char sexe;
};
