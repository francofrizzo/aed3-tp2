#include "../main.h"
#include "./ElRetornoDelJedi.h"

/*
**  Ejercicio 3: El retorno del (que te) jedi
**  Pruebas de performance
*/

using namespace std;

#define MAX_N                 50000
#define MAX_NxM               1000
#define CANT_REPETICIONES     50
#define CANT_INST_DESCARTADAS 30
#define CANT_REP_COMPLETAS     1

#define PRUEBA_VARIAR_FILAS                   0
#define PRUEBA_VARIAR_COLUMNAS                1
#define PRUEBA_VARIAR_COLUMNAS_Y_FILAS        2
#define PRUEBA_VARIAR_NIVEL_DE_ENTRENAMIENTO  3

vector < vector <int> >  generarMapa(int N,int M){
    vector < vector <int> > E = vector< vector<int> >(N, vector < int >(M));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            E[i][j] = rand();
        }
    }
    return E;
}

void ejecutarPruebas(int prueba_id, ofstream& archivoSalida, bool quiet,int MaxN , int step ) {
    if (!quiet) {
        switch (prueba_id) {
            case PRUEBA_VARIAR_FILAS:
                cout << "Escenario: variar filas" << endl; break;

            case PRUEBA_VARIAR_COLUMNAS:
                cout << "Escenario: variar columnas" << endl; break;
            case PRUEBA_VARIAR_COLUMNAS_Y_FILAS:
                cout << "Escenario: variar filas y columnas" << endl; break;
            case PRUEBA_VARIAR_NIVEL_DE_ENTRENAMIENTO:
                cout << "Escenario: variando el nivel de entremiento" << endl; break;
        }
    }

    for ( int i = 1; i <= MaxN; i+=step) {
        int H = 0;
        int N = 0,M = 0 ;
        vector < vector <int> > E;
        vector < vector < pair < int, char > > > DP;

        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;

        if (!quiet) {
            cout << "  N = " << setfill(' ') << setw(2) << i << "    " << flush;
        }


        switch (prueba_id) {
            case PRUEBA_VARIAR_FILAS:
                E = generarMapa(i,1);
                N = i;
                M = 1;
                H = rand();
                break;

            case PRUEBA_VARIAR_COLUMNAS:
                E = generarMapa(1,i);
                N = 1;
                M = i;
                H = rand();
                break;

            case PRUEBA_VARIAR_COLUMNAS_Y_FILAS:
                E = generarMapa(i,i);
                N = i;
                M = i;
                H = rand();
                break;

            case PRUEBA_VARIAR_NIVEL_DE_ENTRENAMIENTO:
                N = MAX_NxM;
                M = MAX_NxM;
                E = generarMapa(MAX_NxM,MAX_NxM);
                H = i;
                break;
        }

        for (int r = -CANT_INST_DESCARTADAS; r < CANT_REPETICIONES; r++) {
            if (!quiet) {
                cout << "\b\b\b" << setfill(' ') << setw(3) << r << flush;
            }

            double tiempo;
            start_timer();
            resolver(N, M , H, E , DP);
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

        // archivoSalida.open("../exp/elRetornoDelJediFilas");
        // ejecutarPruebas(PRUEBA_VARIAR_FILAS, archivoSalida, quiet,MAX_N,200);
        // archivoSalida.close();

        // archivoSalida.open("../exp/elRetornoDelJediColumnas");
        // ejecutarPruebas(PRUEBA_VARIAR_COLUMNAS, archivoSalida, quiet,MAX_N,200);
        // archivoSalida.close();

        archivoSalida.open("../exp/elRetornoDelJediFilasYColumnas");
        ejecutarPruebas(PRUEBA_VARIAR_COLUMNAS_Y_FILAS, archivoSalida, quiet,MAX_NxM,10);
        archivoSalida.close();

        // archivoSalida.open("../exp/elRetornoDelJediNivelDeEntrenamiento");
        // ejecutarPruebas(PRUEBA_VARIAR_NIVEL_DE_ENTRENAMIENTO, archivoSalida, quiet,MAX_N,200);
        // archivoSalida.close();
    }
}
