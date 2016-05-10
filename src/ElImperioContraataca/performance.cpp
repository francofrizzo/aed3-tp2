#include "../main.h"
#include "./ElImperioContraataca.h"

#include <cmath>

/*
**  Ejercicio 2: El Imperio contraataca
**  Pruebas de performance
*/

using namespace std;

#define MAX_N                   12
#define CANT_REPETICIONES       40
#define CANT_INST_DESCARTADAS   20
#define CANT_REP_COMPLETAS      1

#define PRUEBA_PEOR_CASO        0
#define PRUEBA_CASO_INTERMEDIO  1
#define PRUEBA_MEJOR_CASO       2
#define PRUEBA_RANDOM           3

#define N_FIJO                  100
#define LONG_MAX_ARISTA         100

// Genera una instancia del problema de tamaño n donde todos los planetas
// estan conectados con todos con el mismo peso
vector<vector<pair<int, int>>> generarMejorCaso(unsigned int n){
    vector<vector<pair<int, int>>> rutas;

    for(unsigned int i = 0; i < n; i++){
        for(unsigned int j = 0; j < n; j++){
            if(i != j)
                rutas[i].push_back(pair<int, int>(j, 1));
        }
    }

    return rutas;
}

vector<vector<pair<int, int>>> generarCasoIntermedio(unsigned int n){
    vector<vector<pair<int, int>>> rutas;

    rutas[0].push_back(pair<int, int>(1, 1));
    rutas[n - 1].push_back(pair<int, int>(n - 2, 1));

    for(unsigned int i = 1; i < n - 1; i++){
        rutas[i].push_back(pair<int, int>(i - 1, 1));
        rutas[i].push_back(pair<int, int>(i + 1, 1));
    }

    return rutas;
}

// Genera una instancia del problema de tamaño n donde todos los planetas
// estan conectados de manera de formar un camino simple
// Pre: n ≥ 2
vector<vector<pair<int, int>>> generarPeorCaso(unsigned int n){
    vector<vector<pair<int, int>>> rutas;

    rutas[0].push_back(pair<int, int>(1, 1));
    rutas[n - 1].push_back(pair<int, int>(n - 2, 1));

    for(unsigned int i = 1; i < n - 1; i++){
        rutas[i].push_back(pair<int, int>(i - 1, 1));
        rutas[i].push_back(pair<int, int>(i + 1, 1));
    }

    return rutas;
}

vector<vector<pair<int, int>>> generarCasoRandom(unsigned int n, unsigned int m){
    vector<vector<pair<int, int>>> rutas(n, vector<pair<int, int>>());

    // Inicializar semilla
    srand(time(NULL));

    // Camino simple (no random)
    rutas[0].push_back(pair<int, int>(1, 1));
    rutas[n - 1].push_back(pair<int, int>(n - 2, 1));
    for(unsigned int i = 1; i < n - 1; i++){
        rutas[i].push_back(pair<int, int>(i - 1, 1));
        rutas[i].push_back(pair<int, int>(i + 1, 1));
    }

    // Agregar aristas restantes
    int aristasRestantes = m - (n  - 1);
    while(aristasRestantes > 0){
        int nodo1 = rand() % n;
        int nodo2 = rand() % n;

        // Busca la arista para no repetir
        vector<pair<int, int>> vecinosDeNodo1 = rutas[nodo1];
        bool esta = false;
        int i = 0;
        while(!esta && i < vecinosDeNodo1.size()){
            if(vecinosDeNodo1[i].first == nodo2)
                esta = true;
            i++;
        }

        if(nodo1 != nodo2 && !esta){
            // Agrega la arista
            int longitud = rand() % LONG_MAX_ARISTA;
            rutas[nodo1].push_back(pair<int, int>(nodo2, longitud));
            rutas[nodo2].push_back(pair<int, int>(nodo1, longitud));
            aristasRestantes--;
        }
    }

    return rutas;
}

void ejecutarPruebaConNFijo(ofstream& archivoSalida, bool quiet, int n) {
    if (!quiet)
        cout << "Escenario: N = " << n << endl;

    vector<vector<pair<int, int>>> rutas;
    int maxAristas = n * (n - 1) / 2;
    int minAristas = n - 1;
    int rangoAristas =  maxAristas - minAristas;

    for (unsigned int i = 1; i <= MAX_N; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;
        
        int m;
        if (r < 0) {
            m = rand() % rangoAristas + minAristas;
        }
        else if (r > 0) {
            m += rangoAristas / n;
        }
        else {
            m = minAristas;
        }
        
        for (int r = -CANT_INST_DESCARTADAS; r < CANT_REPETICIONES; r++) {
            if (!quiet)
                cout << "\b\b\b" << setfill(' ') << setw(3) << r << flush;


            rutas = generarCasoRandom(n, m);
            
            double tiempo;
            start_timer();
            vector<int> agm = prim(rutas);
            peso_arbol_generador(agm, rutas);
            tiempo = stop_timer();

            if (r >= 0) {
                tiempos[r] = tiempo;
                tiempo_promedio += tiempos[r];
            }
        }

        tiempo_promedio = tiempo_promedio / CANT_REPETICIONES;

        for (unsigned int r = 0; r < CANT_REPETICIONES; r++)
            desv_estandar += pow(tiempos[r] - tiempo_promedio, 2);

        desv_estandar = sqrt(desv_estandar / CANT_REPETICIONES);

        archivoSalida << m  << " " << tiempo_promedio << " " << desv_estandar << endl;

        if (!quiet)
            cout << "\b\b\b  ✓" << endl;
    
    }
}

void correr_pruebas_performance() {
    bool quiet = ! verbose;

    ofstream archivoSalida;
    for (int i = 0; i < CANT_REP_COMPLETAS; i++) {

        // archivoSalida.open("../exp/elImplerioContraatacaPeor");
        // ejecutarPruebas(PRUEBA_PEOR_CASO, archivoSalida, quiet);
        // archivoSalida.close();

        // archivoSalida.open("../exp/elImplerioContraatacaIntermedio");
        // ejecutarPruebas(PRUEBA_CASO_INTERMEDIO, archivoSalida, quiet);
        // archivoSalida.close();

        // archivoSalida.open("../exp/elImplerioContraatacaMejor");
        // ejecutarPruebas(PRUEBA_MEJOR_CASO, archivoSalida, quiet);
        // archivoSalida.close();

        archivoSalida.open("../exp/elImplerioContraatacaRandom");
        ejecutarPruebaConNFijo(archivoSalida, quiet, N_FIJO);
        archivoSalida.close();
    }
}
