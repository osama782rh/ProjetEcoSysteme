#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Entite.h" // Inclusions nécessaires pour Entite

class Entite; // Déclaration avancée

// Enumération pour le mode de déplacement
enum ModeDeplacement {
    NORMAL,     // Déplacement aléatoire
    INTELLIGENT // Déplacement vers la ressource la plus proche
};

class Univers {
public:
    Univers(int largeur, int hauteur, ModeDeplacement mode);
    ModeDeplacement getModeDeplacement() const;
    void afficherEvenements() const;
    void nettoyerEvenements();
    void avancerTour();
    bool positionValide(int x, int y) const;
    bool estVide(int x, int y) const;
    std::shared_ptr<Entite> obtenirEntite(int x, int y) const;
    void retirerEntite(int x, int y);
    void deplacerEntite(const std::shared_ptr<Entite>& entite, int newX, int newY);
    void ajouterEntite(const std::shared_ptr<Entite>& entite, int x, int y);
    void enregistrerEvenement(const std::string& evenement, int x, int y);
    void afficher() const;
    void sauvegarder(const std::string& fichier) const;
    void charger(const std::string& fichier);
    int getNombreLoups() const;
    int getNombreMoutons() const;

private:
    int largeur, hauteur;
    int nombreLoups, nombreMoutons;
    ModeDeplacement modeDeplacement;
    std::vector<std::vector<std::shared_ptr<Entite>>> grille;
    std::vector<std::string> evenements;
};
