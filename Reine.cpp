#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Fonction d'affichage de l'échiquier
void afficherEchiquier(const vector<int>& reines, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reines[i] == j) {
                cout << " Q ";
            } else {
                cout << " . ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

bool estSecurise(int ligne, int col, const vector<int>& reines) {
    for (int i = 0; i < ligne; i++) {
        int colExistante = reines[i];
        
        // 1. Vérification de la même colonne
        if (colExistante == col) return false;
        
        // 2. Vérification des deux diagonales (distance_ligne == distance_colonne)
        if (abs(i - ligne) == abs(colExistante - col)) return false;
    }
    return true;
}

// Algorithme de backtracking pour compléter le placement
bool completerEchiquier(int ligneActuelle, int N, vector<int>& reines) {
    // Si toutes les lignes sont remplies, la solution complète est trouvée
    if (ligneActuelle == N) return true;

    // Tenter de placer une reine sur chaque colonne de la ligne actuelle
    for (int col = 0; col < N; col++) {
        if (estSecurise(ligneActuelle, col, reines)) {
            reines[ligneActuelle] = col; // Placer

            // Passer à la ligne suivante
            if (completerEchiquier(ligneActuelle + 1, N, reines)) {
                return true;
            }

            reines[ligneActuelle] = -1; // Backtrack si impasse
        }
    }
    return false; // Aucune position valide trouvée sur cette ligne
}

int main() {
    int N = 10;
    vector<int> reines(N, -1);

    // --- APPLICATION STRICTE DE VOS CONTRAINTES DE DEPART ---
    reines[0] = 1; // Première reine forcée en Ligne 0, Colonne 1
    reines[1] = 3; // Deuxième reine forcée en Ligne 1, Colonne 3

    cout << "[Initialisation] Reine 1 fixee en (0, 1)" << endl;
    cout << "[Initialisation] Reine 2 fixee en (1, 3)" << endl;

    // L'algorithme prend le relais à partir de la ligne 2 pour compléter de manière sécurisée
    if (completerEchiquier(2, N, reines)) {
        cout << "\n--- Solution Finale Valide Trouvee ---" << endl;
        afficherEchiquier(reines, N);

        for(int i = 0; i < N; i++) {
            cout << "Reine placee en : Ligne " << i << ", Colonne " << reines[i] << endl;
        }
    } else {
        cout << "\nImpossible de completer l'echiquier avec cette configuration initiale." << endl;
    }

    return 0;
}
