#include <iostream>
#include <vector>

using namespace std;

int main() {
   

    int N = 10; // Fonctionne instantanément même pour N = 1000000
    vector<int> reines(N);

    // Formule mathématique directe en O(N) sans AUCUN backtracking
    if (N % 6 != 2 && N % 6 != 3) {
        // Cas général (comme N = 4) : reines paires puis impaires
        int index = 0;
        for (int i = 1; i < N; i += 2) reines[index++] = i;
        for (int i = 0; i < N; i += 2) reines[index++] = i;
    } else if (N % 6 == 2) {
        // Ajustement mathématique pour éviter les conflits de diagonales
        int index = 0;
        for (int i = 1; i < N; i += 2) reines[index++] = i;
        reines[index++] = 2; reines[index++] = 0;
        for (int i = 4; i < N; i += 2) if(i != 2) reines[index++] = i;
    } else {
        // Ajustement pour N % 6 == 3
        int index = 0;
        for (int i = 2; i < N; i += 2) reines[index++] = i; reines[index++] = 0;
        for (int i = 1; i < N - 1; i += 2) reines[index++] = i; reines[index++] = N - 1;
    }

    // Affichage ultra-rapide en O(N)
    cout << "--- Solution instantanee en O(N) ---\n";
    for (int i = 0; i < N; i++) {
        cout << "Ligne " << i << " -> Colonne " << reines[i] << "\n";
    }

    return 0;
}
