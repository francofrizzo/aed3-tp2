#include "../main.h"
#include "./UnaNuevaEsperanza.h"

#include <algorithm>       // random_shuffle

/*
**  Ejercicio 1: Una nueva esperanza
**  Pruebas de performance
*/

using namespace std;
typedef vector<vector<pair<int, bool>>> listas_ady;

listas_ady generar_arbol_aleatorio(int N, float c) {
    vector<int> nodos_usados;
    vector<int> nodos_restantes;
    listas_ady grafo(N);

    if (N < 2) {
        return grafo;
    }

    for (int i = 0; i < N; i++) {
        nodos_restantes.push_back(i);
    }
    random_shuffle(nodos_restantes.begin(), nodos_restantes.end());

    // Elegir un primer nodo y agregarlo al árbol
    int primer_nodo = nodos_restantes.back();
    nodos_restantes.pop_back();
    nodos_usados.push_back(primer_nodo);

    // Asegurarse de que al menos una arista sea especial
    int arista_especial = (rand() % (N - 1)) + 1;

    // Agregar aristas al azar entre un nodo que esté en el árbol y uno que no
    for (int i = 1; i < N; i++) {
        int nodo1 = nodos_restantes.back();
        nodos_restantes.pop_back();

        int nodo2 = nodos_usados[rand() % i];
        nodos_usados.push_back(nodo1);

        bool especial = i == arista_especial
                        ? true
                        : (rand() < RAND_MAX * c);

        grafo[nodo1].push_back({nodo2, especial});
        grafo[nodo2].push_back({nodo1, especial});
    }

    return grafo;
}

listas_ady generar_completo_aleatorio(int N, float c) {
    listas_ady grafo(N);

    // Agregar aristas entre todos los pares posibles de nodos
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            bool especial = rand() < RAND_MAX * c;
            grafo[i].push_back({j, especial});
            grafo[j].push_back({i, especial});
        }
    }

    // Asegurarse de que al menos una arista sea especial
    grafo[rand() % N][rand() % N].second = true;

    return grafo;
}

enum tipo_prueba {arboles, completos};

vector<pair<int,vector<double>>> prueba_variando_M(
    tipo_prueba tipo,
    int min_M,
    int max_M,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones,
    float prop_aristas_esp
) {
    vector<pair<int,vector<double>>> tiempos(cant_muestras,
        {0, vector<double>(cant_repeticiones)});

    if (verbose) {
        switch (tipo) {
            case arboles:
                cout << "Escenario: árboles" << endl;
                break;
            case completos:
                cout << "Escenario: grafos completos" << endl;
                break;
        }
        cout << "   #         M         N    It" << endl;
    }

    for (int i = 0; i < cant_muestras; i++) {
        int M = min_M + (i * (max_M - min_M) / (cant_muestras - 1));
        int N = 0;

        switch (tipo) {
            case arboles:
                N = M + 1;
                break;
            case completos:
                N = (1 + sqrt(1 + 8 * M)) / 2;
                M = N * (N - 1) / 2;
                break;
        }

        if (verbose) {
            cout             << setfill(' ') << setw(4) << i
                 << "  "     << setfill(' ') << setw(8) << M
                 << "  "     << setfill(' ') << setw(8) << N
                 << "   ..." << flush;
        }

        listas_ady grafo;

        switch (tipo) {
            case arboles:
                grafo = generar_arbol_aleatorio(N, prop_aristas_esp);
                break;
            case completos:
                grafo = generar_completo_aleatorio(N, prop_aristas_esp);
                break;
        }

        tiempos[i].first = M;

        for (int j = - cant_descartadas; j < cant_repeticiones; j++) {
            if (verbose) {
                cout << "\b\b\b\b" << setfill(' ') << setw(4) << j << flush;
            }

            start_timer();
            resolver(N, grafo);
            double tiempo = stop_timer();

            if (j >= 0) {
                tiempos[i].second[j] = tiempo;
            }
        }

        if (verbose) {
            cout << "\b\b\b\b" << "   ✓" << endl;
        }
    }

    return tiempos;
}

void imprimir_tiempos(ofstream& os, vector<pair<int,vector<double>>> tiempos) {
    for (uint i = 0; i < tiempos.size(); i++) {
        int x             = tiempos[i].first;
        vector<double> ys = tiempos[i].second;

        double promedio = 0;
        double desv_estandar = 0;

        for (uint j = 0; j < ys.size(); j++) {
            promedio += ys[j];
        }
        promedio = promedio / ys.size();

        for (uint j = 0; j < ys.size(); j++) {
            desv_estandar += pow(ys[j] - promedio, 2);
        }
        desv_estandar = sqrt(desv_estandar / ys.size());

        os << x << " " << promedio << " " << desv_estandar << endl;
    }
}

void correr_pruebas_performance() {
    vector<pair<int,vector<double>>> tiempos;
    ofstream archivo_salida;

    // Prueba con árboles aleatorios
    tiempos = prueba_variando_M(
        arboles,    // tipo,
        100000,     // min_M,
        200000,     // max_M,
        30,         // cant_muestras,
        10,         // cant_descartadas,
        20,         // cant_repeticiones,
        .5          // prop_aristas_esp
    );
    archivo_salida.open("../exp/UnaNuevaEsperanza-varM-arboles");
    imprimir_tiempos(archivo_salida, tiempos);
    archivo_salida.close();

    // Prueba con grafos completos
    tiempos = prueba_variando_M(
        completos,  // tipo,
        100000,     // min_M,
        200000,     // max_M,
        30,         // cant_muestras,
        10,         // cant_descartadas,
        20,         // cant_repeticiones,
        .5          // prop_aristas_esp
    );
    archivo_salida.open("../exp/UnaNuevaEsperanza-varM-completos");
    imprimir_tiempos(archivo_salida, tiempos);
    archivo_salida.close();
}
