#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>   // Pour mesurer le temps d'exécution
#include <iomanip>  // Pour le formatage

using namespace std;
using namespace std::chrono;

// ============ COMPTEURS GLOBAUX DE DEBUG ============
long long compteurAppelsRecursifs = 0;  // Nombre d'appels à completerEchiquier
long long compteurPlacements = 0;        // Reines effectivement placées
long long compteurBacktracks = 0;        // Nombre de retours arrière
long long compteurVerifications = 0;     // Nombre d'appels à estSecurise
long long compteurIterationsBoucle = 0;  // Itérations internes de la boucle for

// ============ FONCTIONS ORIGINALES ============

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
    compteurVerifications++;
    for (int i = 0; i < ligne; i++) {
        int colExistante = reines[i];
        if (colExistante == col) return false;
        if (abs(i - ligne) == abs(colExistante - col)) return false;
    }
    return true;
}

bool completerEchiquier(int ligneActuelle, int N, vector<int>& reines) {
    compteurAppelsRecursifs++;

    if (ligneActuelle == N) return true;

    for (int col = 0; col < N; col++) {
        compteurIterationsBoucle++;
        if (estSecurise(ligneActuelle, col, reines)) {
            reines[ligneActuelle] = col;
            compteurPlacements++;

            if (completerEchiquier(ligneActuelle + 1, N, reines)) {
                return true;
            }

            reines[ligneActuelle] = -1;
            compteurBacktracks++;
        }
    }
    return false;
}

// ============ MAIN ============
int main() {
    int N = 10;
    vector<int> reines(N, -1);

    reines[0] = 1;
    reines[1] = 3;

    cout << "[Initialisation] Reine 1 fixee en (0, 1)" << endl;
    cout << "[Initialisation] Reine 2 fixee en (1, 3)" << endl;

    // ===== Mesure du temps d'exécution =====
    auto debut = high_resolution_clock::now();

    bool succes = completerEchiquier(2, N, reines);

    auto fin = high_resolution_clock::now();
    auto duree = duration_cast<nanoseconds>(fin - debut).count();

    // ===== Affichage du résultat =====
    if (succes) {
        cout << "\n--- Solution Finale Valide Trouvee ---" << endl;
        afficherEchiquier(reines, N);
        for(int i = 0; i < N; i++) {
            cout << "Reine placee en : Ligne " << i << ", Colonne " << reines[i] << endl;
        }
    } else {
        cout << "\nImpossible de completer l'echiquier avec cette configuration initiale." << endl;
    }

    // ===== TEMPS D'EXÉCUTION =====
    cout << "\n========== TEMPS D'EXECUTION ==========" << endl;
    cout << "Duree (nanosecondes) : " << duree << " ns" << endl;
    cout << "Duree (microsecondes): " << duree / 1000.0 << " us" << endl;
    cout << "Duree (millisecondes): " << duree / 1e6 << " ms" << endl;
    cout << "Duree (secondes)     : " << duree / 1e9 << " s" << endl;

    // ===== STATISTIQUES DE DEBUG =====
    cout << "\n========== STATISTIQUES DEBUG ==========" << endl;
    cout << "Appels recursifs         : " << compteurAppelsRecursifs << endl;
    cout << "Iterations de boucle for : " << compteurIterationsBoucle << endl;
    cout << "Verifications securite   : " << compteurVerifications << endl;
    cout << "Placements de reines     : " << compteurPlacements << endl;
    cout << "Backtracks effectues     : " << compteurBacktracks << endl;

    // ===== COMPLEXITE THEORIQUE =====
    cout << "\n========== COMPLEXITE THEORIQUE ==========" << endl;
    cout << "Complexite temporelle (pire cas)  : O(N!)" << endl;
    cout << "Complexite temporelle (pratique)  : O(N!) borne par backtracking" << endl;
    cout << "Complexite spatiale               : O(N) (profondeur recursion + tableau)" << endl;
    cout << "Complexite de estSecurise()       : O(N) par appel" << endl;
    cout << "Complexite d'un noeud complet     : O(N) * O(N) = O(N^2) par noeud" << endl;

    // ===== ANALYSE DES CAS =====
    cout << "\n========== ANALYSE DES CAS ==========" << endl;
    cout << "Meilleur cas : La 1ere colonne testee a chaque ligne est valide" << endl;
    cout << "  -> Complexite : O(N^2) (N appels x O(N) de verification)" << endl;
    cout << "  -> Soit environ " << N * N << " operations pour N = " << N << endl;

    cout << "\nPire cas : Il faut tester toutes les combinaisons possibles" << endl;
    cout << "  -> Complexite : O(N!) (permutations toutes explorees)" << endl;
    cout << "  -> Soit environ " << N << "! operations pour N = " << N << endl;

    cout << "\nCas moyen : Backtracking avec elagage partiel" << endl;
    cout << "  -> Complexite : entre O(N^2) et O(N!), generalement proche de O(N!)" << endl;

    // ===== ANALYSE EMPIRIQUE =====
    cout << "\n========== ANALYSE EMPIRIQUE (mesure reelle) ==========" << endl;
    cout << "Noeuds explores : " << compteurAppelsRecursifs << endl;
    cout << "  -> Pour N = " << N << ", borne theorique N! = ";
    long long factorielle = 1;
    for (int i = 2; i <= N; i++) factorielle *= i;
    cout << factorielle << endl;
    cout << "  -> Ratio explore/theorique : "
         << fixed << setprecision(6)
         << (double)compteurAppelsRecursifs / factorielle << endl;

    // ===== COMPARAISON AVEC LES AUTRES APPROCHES =====
    cout << "\n========== COMPARAISON ==========" << endl;
    cout << "Cette approche (backtracking) : O(N!) pire cas, efficace pour N <= 30" << endl;
    cout << "Construction modulo 6         : O(N) garantie, efficace pour tout N" << endl;
    cout << "Recherche locale (Sosic-Gu)   : ~O(N log N) en pratique, millions de reines" << endl;

    return 0;
}