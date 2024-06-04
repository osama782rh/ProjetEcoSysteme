#ifndef UNIVERS_H
#define UNIVERS_H

#include <vector>
#include <memory>
#include <string>
#include "Entite.h"

enum ModeDeplacement { NORMAL, INTELLIGENT };

class Univers {
public:
    Univers(int largeur, int hauteur, ModeDeplacement mode);

    ModeDeplacement getModeDeplacement() const;
    void afficher() const;
    void avancerTour();
    bool positionValide(int x, int y) const;
    bool estVide(int x, int y) const;
    void ajouterEntite(const std::shared_ptr<Entite>& entite, int x, int y);
    void retirerEntite(int x, int y);
    void deplacerEntite(const std::shared_ptr<Entite>& entite, int newX, int newY);
    std::shared_ptr<Entite> obtenirEntite(int x, int y) const;
    int getNombreLoups() const;
    int getNombreMoutons() const;

    void enregistrerEvenement(const std::string& evenement, int x, int y);

private:
    int largeur;
    int hauteur;
    int nombreLoups;
    int nombreMoutons;
    ModeDeplacement modeDeplacement;
    std::vector<std::vector<std::shared_ptr<Entite>>> grille;
    std::vector<std::string> evenements;

    void afficherEvenements() const;
    void nettoyerEvenements();
    void gererConflit(const std::shared_ptr<Entite>& entite, const std::shared_ptr<Entite>& cible, int newX, int newY);
};

#endif // UNIVERS_H
