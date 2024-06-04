#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <atomic>
#include <iomanip>
#include "Univers.h"
#include "Mouton.h"
#include "Loup.h"
#include "Herbe.h"

using namespace std;

void afficherMenu() {
    cout << "----------------------------------------\n";
    cout << "|      Bienvenue dans la simulation     |\n";
    cout << "----------------------------------------\n";
    cout << "1. Mode normal (déplacements aléatoires)\n";
    cout << "2. Mode intelligent (déplacements vers la ressource la plus proche, reproduction des animaux)\n";
    cout << "Choisissez le type de jeu (1 ou 2): ";
}

void afficherMenuDifficulte() {
    cout << "----------------------------------------\n";
    cout << "|   Choisissez le niveau de difficulté  |\n";
    cout << "----------------------------------------\n";
    cout << "1. Facile (beaucoup d'herbe)\n";
    cout << "2. Moyen (quantité moyenne d'herbe)\n";
    cout << "3. Difficile (peu d'herbe)\n";
    cout << "Votre choix (1, 2 ou 3): ";
}

void sauvegarderParcours(const Univers& univers, const vector<pair<int, int>>& historique) {
    ofstream fichier("parcours.txt");
    if (fichier) {
        fichier << "Historique du jeu\n";
        fichier << left << setw(10) << "Tour" << setw(10) << "Loups" << setw(10) << "Moutons" << "\n";
        for (size_t i = 0; i < historique.size(); ++i) {
            fichier << left << setw(10) << i + 1 << setw(10) << historique[i].first << setw(10) << historique[i].second << "\n";
        }
    }
    fichier.close();
}

void simulation(int nombreTours, Univers& univers, vector<pair<int, int>>& historique) {
    bool simulationTerminee = false;
    for (int tour = 0; tour < nombreTours; ++tour) {
        cout << "Tour " << tour << " | Loups : " << univers.getNombreLoups() << " | Moutons : " << univers.getNombreMoutons() << "\n";
        historique.push_back({univers.getNombreLoups(), univers.getNombreMoutons()});
        univers.afficher();
        univers.avancerTour();

        if (univers.getNombreLoups() <= 0 && univers.getNombreMoutons() <= 0) {
            simulationTerminee = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    if (simulationTerminee) {
        cout << "Partie terminée | Loups : " << univers.getNombreLoups() << " | Moutons : " << univers.getNombreMoutons() << "\n";
        univers.afficher();
        univers.avancerTour();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (true) {
        int choixMode, choixDifficulte;
        int nombreMoutons, nombreLoups, nombreHerbe;
        ModeDeplacement modeDeplacement;

        afficherMenu();
        cin >> choixMode;
        modeDeplacement = (choixMode == 2) ? INTELLIGENT : NORMAL;

        cout << "Entrez le nombre de moutons (maximum 25): ";
        cin >> nombreMoutons;
        nombreMoutons = std::min(nombreMoutons, 25);

        cout << "Entrez le nombre de loups (maximum 15): ";
        cin >> nombreLoups;
        nombreLoups = std::min(nombreLoups, 15);

        afficherMenuDifficulte();
        cin >> choixDifficulte;
        if (choixDifficulte == 1) {
            nombreHerbe = 40; // Facile
        } else if (choixDifficulte == 2) {
            nombreHerbe = 30; // Moyen
        } else {
            nombreHerbe = 20; // Difficile
        }

        int largeur = 10;
        int hauteur = 10;
        Univers univers(largeur, hauteur, modeDeplacement);

        // Initialisation des entités dans l'univers
        for (int i = 0; i < nombreMoutons; ++i) {
            int x, y;
            do {
                x = rand() % largeur;
                y = rand() % hauteur;
            } while (!univers.estVide(x, y));

            char sexe = (rand() % 2 == 0) ? 'M' : 'F';
            auto mouton = std::make_shared<Mouton>(x, y, sexe, 0, 5, 0, 50);
            univers.ajouterEntite(std::static_pointer_cast<Entite>(mouton), x, y);
        }

        for (int i = 0; i < nombreLoups; ++i) {
            int x, y;
            do {
                x = rand() % largeur;
                y = rand() % hauteur;
            } while (!univers.estVide(x, y));

            char sexe = (rand() % 2 == 0) ? 'M' : 'F';
            auto loup = std::make_shared<Loup>(x, y, sexe, 0, 10, 0, 60);
            univers.ajouterEntite(std::static_pointer_cast<Entite>(loup), x, y);
        }

        for (int i = 0; i < nombreHerbe; ++i) {
            int x, y;
            do {
                x = rand() % largeur;
                y = rand() % hauteur;
            } while (!univers.estVide(x, y));

            auto herbe = std::make_shared<Herbe>(x, y);
            univers.ajouterEntite(std::static_pointer_cast<Entite>(herbe), x, y);
        }

        int nombreTours = 200;
        vector<pair<int, int>> historique;

        simulation(nombreTours, univers, historique);

        cout << "Tous les animaux sont morts. Fin de la simulation." << endl;

        while (true) {
            cout << "Voulez-vous sauvegarder votre parcours? (o/n): ";
            char sauvegarde;
            cin >> sauvegarde;
            if (sauvegarde == 'o' || sauvegarde == 'O') {
                sauvegarderParcours(univers, historique);
            }

            cout << "Voulez-vous recommencer le jeu? (o/n): ";
            char recommencer;
            cin >> recommencer;
            if (recommencer == 'o' || recommencer == 'O') {
                break;
            } else {
                return 0;
            }
        }
    }

    return 0;
}
