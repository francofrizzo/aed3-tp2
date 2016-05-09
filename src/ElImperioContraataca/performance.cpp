#include "../main.h"
#include "./ElImperioContraataca.h"

/*
**  Ejercicio 2: El Imperio contraataca
**  Pruebas de performance
*/

#define MAX_N                 12
#define CANT_REPETICIONES     40
#define CANT_INST_DESCARTADAS 20
#define CANT_REP_COMPLETAS     1

#define PRUEBA_PEOR_CASO       0
#define PRUEBA_CASO_INTERMEDIO 1
#define PRUEBA_MEJOR_CASO      2
#define PRUEBA_RANDOM          3

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

vector<vector<pair<int, int>>> generarCasoRandom(unsigned int n){
    vector<vector<pair<int, int>>> rutas;

    rutas[0].push_back(pair<int, int>(1, 1));
    rutas[n - 1].push_back(pair<int, int>(n - 2, 1));

    for(unsigned int i = 1; i < n - 1; i++){
        rutas[i].push_back(pair<int, int>(i - 1, 1));
        rutas[i].push_back(pair<int, int>(i + 1, 1));
    }

    return rutas;
}

void ejecutarPruebas(int prueba_id, ofstream& archivoSalida, bool quiet) {
    if (!quiet) {
        switch (prueba_id) {
            case PRUEBA_MEJOR_CASO:
                cout << "Escenario: mejor caso" << endl; break;
            case PRUEBA_CASO_INTERMEDIO:
                cout << "Escenario: caso intermedio" << endl; break;
            case PRUEBA_PEOR_CASO:
                cout << "Escenario: peor caso" << endl; break;
            case PRUEBA_RANDOM:
                cout << "Escenario: aleatorio" << endl; break;
        }
    }

    vector<vector<pair<int, int>>> rutas;

    for (unsigned int i = 1; i <= MAX_N; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;
        bool instancias_random = false;

        N = i;

        if (!quiet) {
            cout << "  N = " << setfill(' ') << setw(2) << i << "    " << flush;
        }

        switch (prueba_id) {
            case PRUEBA_MEJOR_CASO:
                rutas = generarMejorCaso(N);
                break;

            case PRUEBA_CASO_INTERMEDIO:
                rutas = generarCasoIntermedio(N);
                break;

            case PRUEBA_PEOR_CASO:
                rutas = generarPeorCaso(N);
                break;

            case PRUEBA_RANDOM:
                instancias_random = true;
                break;
        }
        
        for (int r = -CANT_INST_DESCARTADAS; r < CANT_REPETICIONES; r++) {
            if (!quiet) {
                cout << "\b\b\b" << setfill(' ') << setw(3) << r << flush;
            }

            double tiempo;
            if (instancias_random) {
                rutas = generarCasoRandom(N);
            }
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

        for (unsigned int r = 0; r < CANT_REPETICIONES; r++) {
            desv_estandar += pow(tiempos[r] - tiempo_promedio, 2);
        }
        desv_estandar = sqrt(desv_estandar / CANT_REPETICIONES);

        archivoSalida << i << " " << tiempo_promedio << " " << desv_estandar << endl;

        if (!quiet) {
            cout << "\b\b\b  ✓" << endl;
        }
    }
}

void correr_pruebas_performance() {
    bool quiet = ! verbose;

    ofstream archivoSalida;
    for (int i = 0; i < CANT_REP_COMPLETAS; i++) {

        archivoSalida.open("../exp/elImplerioContraatacaPeor");
        ejecutarPruebas(PRUEBA_PEOR_CASO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/elImplerioContraatacaIntermedio");
        ejecutarPruebas(PRUEBA_CASO_INTERMEDIO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/elImplerioContraatacaMejor");
        ejecutarPruebas(PRUEBA_MEJOR_CASO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/elImplerioContraatacaRandom");
        ejecutarPruebas(PRUEBA_RANDOM, archivoSalida, quiet);
        archivoSalida.close();
    }
}
