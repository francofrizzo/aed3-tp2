#include "../main.h"
#include "./UnaNuevaEsperanza.h"

#include <algorithm>       // random_shuffle

/*
**  Ejercicio 1: Una nueva esperanza
**  Pruebas de performance
*/

using namespace std;
typedef vector<vector<pair<int, bool>>> listas_ady;
typedef vector<pair<double,vector<double>>> vec_tiempos;


/* --------------------
 * Funciones auxiliares
 * -------------------- */

void imprimir_grafo(ostream& os, listas_ady grafo) {
    for (uint i = 0; i < grafo.size(); i++) {
        os << i << ": ";
        for (uint j = 0; j < grafo[i].size(); j++) {
            os << " " << grafo[i][j].first << "(" << grafo[i][j].second << ")";
        }
        os << endl;
    }
}

void imprimir_tiempos_resumen(ostream& os, vec_tiempos tiempos) {
    for (uint i = 0; i < tiempos.size(); i++) {
        float x           = tiempos[i].first;
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

void imprimir_tiempos_detalle(ostream& os, vec_tiempos tiempos) {
    for (uint i = 0; i < tiempos.size(); i++) {
        os << tiempos[i].first;

        for (uint j = 0; j < tiempos[i].second.size(); j++) {
            os << " " << tiempos[i].second[j];
        }

        os << endl;
    }
}

void guardar_resultados(string path, vec_tiempos tiempos) {
    ofstream archivo_salida;

    archivo_salida.open(path);
    imprimir_tiempos_resumen(archivo_salida, tiempos);
    archivo_salida.close();

    // archivo_salida.open(path + "-d");
    // imprimir_tiempos_detalle(archivo_salida, tiempos);
    // archivo_salida.close();
}

/* ------------------------------
 * Generadores de casos de prueba
 * ------------------------------ */

listas_ady generar_camino_simple(int N) {
    listas_ady grafo(N);

    grafo[0] = {{1, 0}};

    for (int i = 1; i < N - 2; i ++) {
        grafo[i] = {{i - 1, 0}, {i + 1, 0}};
    }

    if (N > 2) {
        grafo[N - 2] = {{N - 3, 0}, {N - 1, 1}};
    }

    grafo[N - 1] = {{N - 2, 1}};

    return grafo;
}

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

    // Agregar aristas al azar entre un nodo que esté en el árbol y uno que no
    for (int i = 1; i < N; i++) {
        int nodo1 = nodos_restantes.back();
        nodos_restantes.pop_back();

        int nodo2 = nodos_usados[rand() % i];
        nodos_usados.push_back(nodo1);

        bool especial = rand() < RAND_MAX * c;

        grafo[nodo1].push_back({nodo2, especial});
        grafo[nodo2].push_back({nodo1, especial});
    }

    return grafo;
}

listas_ady& expandir_arbol_aleatorio(
    listas_ady& grafo,
    int cant_nuevos_nodos,
    float c
) {
    int N = grafo.size();

    for (int i = 0; i < cant_nuevos_nodos; i++) {
        int nodo1 = (rand() % N);
        int nodo2 = N + 1;
        bool especial = rand() < RAND_MAX * c;

        grafo[nodo1].push_back({nodo2, especial});
        grafo.push_back({{nodo1, especial}});

        N++;
    }

    return grafo;
}

listas_ady generar_arbol_k_ario(int N, int k, float c) {
    listas_ady grafo(N);
    int padre = 0;
    int hermanos = 0;

    for (int i = 1; i < N; i++) {
        if (hermanos < k) {
            hermanos++;
        } else {
            padre++;
            hermanos = 1;
        }

        bool especial = (rand() < RAND_MAX * c);
        // bool especial = (i == N - 1);

        grafo[padre].push_back({i, especial});
        grafo[i].push_back({padre, especial});
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
    // grafo[rand() % N][rand() % N].second = true;

    return grafo;
}

listas_ady generar_conexo_aleatorio(int N, int M, float c) {
    listas_ady grafo(N);
    vector<vector<bool>> matr_ady(N, vector<bool>(N, false));

    grafo = generar_arbol_aleatorio(N, c);

    for (int i = 0; i < N; i++) {
        for (uint j = 0; j < grafo[i].size(); j++) {
            matr_ady[i][grafo[i][j].first] = true;
        }
    }

    for (int i = N - 1; i < M; i++) {
        int nodo1, nodo2, aux1, aux2;
        do {
            nodo1 = rand() % N;
        } while (grafo[nodo1].size() == (uint) (N - 1));

        aux1 = rand() % (N - 1 - grafo[nodo1].size());
        aux2 = 0;
        nodo2 = 0;

        while (aux2 <= aux1) {
            if ((nodo1 != nodo2) & (! matr_ady[nodo1][nodo2])) {
                aux2++;
            }
            nodo2++;
        }
        nodo2--;

        bool especial = rand() < RAND_MAX * c;

        grafo[nodo1].push_back({nodo2, especial});
        grafo[nodo2].push_back({nodo1, especial});
        matr_ady[nodo1][nodo2] = true;
        matr_ady[nodo2][nodo1] = true;
    }

    return grafo;
}


/* --------------------
 * Escenarios de prueba
 * -------------------- */

enum tipo_prueba {completos,
                  arboles,
                  caminos, caminos_alt,
                  m_arios};

vec_tiempos prueba_variando_M_nuevos(
    tipo_prueba tipo,
    int min_M,
    int max_M,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones,
    float prop_aristas_esp
) {
    vec_tiempos tiempos(cant_muestras, {0, vector<double>(cant_repeticiones)});

    if (verbose) {
        cout << "Prueba: M variable, instancias nuevas. ";
        switch (tipo) {
            case completos:
                cout << "Escenario: grafos completos aleatorios" << endl;
                break;

            case arboles:
                cout << "Escenario: árboles aleatorios" << endl;
                break;

            case caminos:
                cout << "Escenario: caminos simples aleatorios" << endl;
                break;
            case caminos_alt:
                cout << "Escenario: caminos simples, generador alternativo" << endl;
                break;

            case m_arios:
                cout << "Escenario: árboles M-arios" << endl;
                break;
        }
        cout << "   #         M         N    It" << endl;
    }

    for (int i = 0; i < cant_muestras; i++) {
        int M = min_M + (i * (max_M - min_M) / (cant_muestras - 1));
        int N = 0;

        switch (tipo) {
            case arboles:
            case caminos:
            case caminos_alt:
            case m_arios:
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
            case caminos:
                grafo = generar_arbol_k_ario(N, 1, prop_aristas_esp);
                break;
            case caminos_alt:
                grafo = generar_camino_simple(N);
                break;
            case m_arios:
                grafo = generar_arbol_k_ario(N, M, 0);
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

vec_tiempos prueba_variando_M_incrementales(
    int min_M,
    int max_M,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones,
    float prop_aristas_esp
) {
    vec_tiempos tiempos(cant_muestras,
        {0, vector<double>(cant_repeticiones)});

    if (verbose) {
        cout << "Prueba: M variable, instancias incrementales. ";
        cout << "Escenario: árboles aleatorios" << endl;
        cout << "   #         M         N    It" << endl;
    }

    int M = min_M;
    int delta_M = (max_M - min_M) / (cant_muestras - 1);
    int N = M + 1;

    listas_ady grafo = generar_arbol_aleatorio(N, prop_aristas_esp);

    for (int i = 0; i < cant_muestras; i++) {
        if (verbose) {
            cout             << setfill(' ') << setw(4) << i
                 << "  "     << setfill(' ') << setw(8) << M
                 << "  "     << setfill(' ') << setw(8) << N
                 << "   ..." << flush;
        }

        if (i > 0) {
            expandir_arbol_aleatorio(grafo, delta_M, prop_aristas_esp);
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

        M  += delta_M;
        N = M + 1;
    }

    return tiempos;
}

vec_tiempos prueba_aleatorios(
    tipo_prueba tipo,
    int M,
    int cant_muestras,
    float prop_aristas_esp
) {
    vec_tiempos tiempos(cant_muestras, {0, vector<double>(1)});

    if (verbose) {
        cout << "Prueba: grafos aleatorios. ";
        switch (tipo) {
            case arboles:
                cout << "Escenario: árboles" << endl;
                break;
            case completos:
                cout << "Escenario: grafos completos" << endl;
                break;
            default:
                cout << "Escenario inválido" << endl;
                break;
        }
        cout << "Iteración:  ..." << flush;
    }

    int N = 0;

    switch (tipo) {
        case arboles:
            N = M + 1;
            break;
        case completos:
            N = (1 + sqrt(1 + 8 * M)) / 2;
            M = N * (N - 1) / 2;
            break;
        default:
            return tiempos;
            break;
    }

    for (int i = 0; i < cant_muestras; i++) {

        listas_ady grafo;

        switch (tipo) {
            case arboles:
                grafo = generar_arbol_aleatorio(N, prop_aristas_esp);
                break;
            case completos:
                grafo = generar_completo_aleatorio(N, prop_aristas_esp);
                break;
            default:
                break;
        }

        tiempos[i].first = M;

        if (verbose) {
            cout << "\b\b\b\b" << setfill(' ') << setw(4) << i << flush;
        }

        start_timer();
        resolver(N, grafo);
        double tiempo = stop_timer();

        tiempos[i].second[0] = tiempo;

    }

    if (verbose) {
        cout << "\b\b\b\b" << "   ✓" << endl;
    }

    return tiempos;
}

vec_tiempos prueba_aristas_especiales(
    tipo_prueba tipo,
    int M,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones
) {
    vec_tiempos tiempos(cant_muestras, {0, vector<double>(cant_repeticiones)});

    float delta_c = 1 / (float) (cant_muestras);
    float c = 0;
    listas_ady grafo;

    if (verbose) {
        cout << "Prueba: proporción de aristas especiales variable. M = "
             << M << ". ";
        switch (tipo) {
            case arboles:
                cout << "Escenario: árboles" << endl;
                break;
            case completos:
                cout << "Escenario: grafos completos" << endl;
                break;
            default:
                cout << "Escenario inválido" << endl;
                break;
        }
        cout << "   #         c    It" << endl;
    }

    int N = 0;

    switch (tipo) {
        case arboles:
            N = M + 1;
            break;
        case completos:
            N = (1 + sqrt(1 + 8 * M)) / 2;
            M = N * (N - 1) / 2;
            break;
        default:
            return tiempos;
            break;
    }

    for (int i = 0; i < cant_muestras; i++) {
        c += delta_c;
        tiempos[i].first = c;

        if (verbose) {
            cout             << setfill(' ') << setw(4) << i
                 << "  "     << setfill(' ') << setw(8) << c
                 << "   ..." << flush;
        }


        for (int j = -cant_descartadas; j < cant_repeticiones; j++) {
            if (verbose) {
                cout << "\b\b\b\b" << setfill(' ') << setw(4) << j << flush;
            }

            grafo = generar_arbol_aleatorio(M + 1, c);

            start_timer();
            resolver(M + 1, grafo);
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

vec_tiempos prueba_arboles_k_arios(
    int M,
    int k_min,
    int k_max,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones,
    float prop_aristas_esp
) {
    vec_tiempos tiempos(cant_muestras, {0, vector<double>(cant_repeticiones)});

    if (verbose) {
        cout << "Prueba: árboles k-arios. M = " << M << endl;
        cout << "   #     k    It" << endl;
    }

    int delta_k = (k_max - k_min) / (cant_muestras - 1);
    int k = k_min;

    listas_ady grafo;

    for (int i = 0; i < cant_muestras; i++) {
        tiempos[i].first = k;

        if (verbose) {
            cout             << setfill(' ') << setw(4) << i
                 << "  "     << setfill(' ') << setw(4) << k
                 << "   ..." << flush;
        }

        grafo = generar_arbol_k_ario(M + 1, k, prop_aristas_esp);

        // ofstream archivo_salida;
        // archivo_salida.open("../exp/arbol-" + to_string(k));
        // imprimir_grafo(archivo_salida, grafo);
        // archivo_salida.close();

        for (int j = - cant_descartadas; j < cant_repeticiones; j++) {
            if (verbose) {
                cout << "\b\b\b\b" << setfill(' ') << setw(4) << j << flush;
            }

            start_timer();
            resolver(M + 1, grafo);
            double tiempo = stop_timer();

            if (j >= 0) {
                tiempos[i].second[j] = tiempo;
            }
        }

        if (verbose) {
            cout << "\b\b\b\b" << "   ✓" << endl;
        }

        k += delta_k;
    }

    return tiempos;
}

vec_tiempos prueba_variando_N(
    int M,
    int cant_muestras,
    int cant_descartadas,
    int cant_repeticiones,
    float prop_aristas_esp
) {
    vec_tiempos tiempos(cant_muestras, {0, vector<double>(cant_repeticiones)});

    if (verbose) {
        cout << "Prueba: N variable. M = " << M << endl;
        cout << "   #         N    It" << endl;
    }

    int N_min = ceil((1 + sqrt(1 + 8 * M)) / 2);
    int N_max = M + 1;
    int delta_N = (N_max - N_min) / (cant_muestras - 1);

    int N = N_min;

    for (int i = 0; i < cant_muestras; i++) {

        if (verbose) {
            cout             << setfill(' ') << setw(4) << i
                 << "  "     << setfill(' ') << setw(8) << N
                 << "   ..." << flush;
        }

        listas_ady grafo = generar_conexo_aleatorio(N, M, prop_aristas_esp);

        tiempos[i].first = N;

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

        N += delta_N;
    }

    return tiempos;
}

/* --------------------
 * Ejecución de pruebas
 * -------------------- */

void correr_pruebas_performance() {
    vec_tiempos tiempos;

     // EXPERIMENTO Ia
     tiempos = prueba_variando_M_nuevos (
         arboles,        // tipo,
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-arboles", tiempos);

     // EXPERIMENTO II
     tiempos = prueba_variando_M_incrementales (
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-inc-arboles", tiempos);

     // EXPERIMENTO Ib
     tiempos = prueba_variando_M_nuevos (
         completos,      // tipo,
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-completos", tiempos);

     // EXPERIMENTO Ic
     tiempos = prueba_variando_M_nuevos (
         caminos,        // tipo,
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-caminos", tiempos);

     // EXPERIMENTO Ic-alt
     tiempos = prueba_variando_M_nuevos (
         caminos_alt,    // tipo,
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-caminos-alt", tiempos);

     // EXPERIMENTO Id
     tiempos = prueba_variando_M_nuevos (
         m_arios,        // tipo,
         20000,          // min_M,
         800000,         // max_M,
         40,             // cant_muestras,
         20,             // cant_descartadas,
         40,             // cant_repeticiones,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varM-m-arios", tiempos);

     // EXPERIMENTO IIIa

     tiempos = prueba_aleatorios(
         arboles,        // tipo,
         100000,         // M,
         200,            // cant_muestras,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-arb-m100k", tiempos);

     tiempos = prueba_aleatorios(
         arboles,        // tipo,
         200000,         // M,
         200,            // cant_muestras,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-arb-m200k", tiempos);

     tiempos = prueba_aleatorios(
         arboles,        // tipo,
         400000,         // M,
         200,            // cant_muestras,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-arb-m400k", tiempos);

     tiempos = prueba_aleatorios(
         arboles,        // tipo,
         800000,         // M,
         200,            // cant_muestras,
         .3              // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-arb-m800k", tiempos);

    // EXPERIMENTO IIIb

    tiempos = prueba_aleatorios(
        completos,      // tipo,
        100000,         // M,
        200,            // cant_muestras,
        .3              // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-comp-m100k", tiempos);

    tiempos = prueba_aleatorios(
        completos,      // tipo,
        200000,         // M,
        200,            // cant_muestras,
        .3              // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-comp-m200k", tiempos);

    tiempos = prueba_aleatorios(
        completos,      // tipo,
        400000,         // M,
        200,            // cant_muestras,
        .3              // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-comp-m400k", tiempos);

    tiempos = prueba_aleatorios(
        completos,      // tipo,
        800000,         // M,
        200,            // cant_muestras,
        .3              // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aleatorios-comp-m800k", tiempos);

    // EXPERIMENTO IVa

    tiempos = prueba_aristas_especiales(
        arboles,         // tipo,
        200000,          // M,
        24,              // cant_muestras,
        20,              // cant_descartadas,
        40               // cant_repeticiones
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aristas-esp-arb-m200k", tiempos);

    tiempos = prueba_aristas_especiales(
        arboles,         // tipo,
        400000,          // M,
        24,              // cant_muestras,
        20,              // cant_descartadas,
        40               // cant_repeticiones
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aristas-esp-arb-m400k", tiempos);

    // EXPERIMENTO IVb

    tiempos = prueba_aristas_especiales(
        completos,       // tipo,
        200000,          // M,
        24,              // cant_muestras,
        20,              // cant_descartadas,
        40               // cant_repeticiones
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aristas-esp-comp-m200k", tiempos);

    tiempos = prueba_aristas_especiales(
        completos,       // tipo,
        400000,          // M,
        24,              // cant_muestras,
        20,              // cant_descartadas,
        40               // cant_repeticiones
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-aristas-esp-comp-m400k", tiempos);

    // EXPERIMENTO V

    tiempos = prueba_arboles_k_arios(
        200000,        // M
        1,             // k_min
        200000,        // k_max
        40,            // cant_muestras
        20,            // cant_descartadas
        40,            // cant_repeticiones
        .3             // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-k-arios-m200k", tiempos);

    tiempos = prueba_arboles_k_arios(
        200000,        // M
        1,             // k_min
        100,           // k_max
        40,            // cant_muestras
        20,            // cant_descartadas
        40,            // cant_repeticiones
        .3             // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-k-arios-m200k-zoom", tiempos);

    tiempos = prueba_arboles_k_arios(
        400000,        // M
        1,             // k_min
        400000,        // k_max
        40,            // cant_muestras
        20,            // cant_descartadas
        40,            // cant_repeticiones
        .3             // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-k-arios-m400k", tiempos);

    tiempos = prueba_arboles_k_arios(
        400000,        // M
        1,             // k_min
        100,           // k_max
        40,            // cant_muestras
        20,            // cant_descartadas
        40,            // cant_repeticiones
        .3             // prop_aristas_esp
    );
    guardar_resultados("../exp/UnaNuevaEsperanza-k-arios-m400k-zoom", tiempos);

    // EXPERIMENTO IV

     tiempos = prueba_variando_N(
         100000,        // M,
         20,            // cant_muestras,
         20,            // cant_descartadas,
         40,            // cant_repeticiones,
         .3             // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varN-n100k", tiempos);

     tiempos = prueba_variando_N(
         200000,        // M,
         20,            // cant_muestras,
         20,            // cant_descartadas,
         40,            // cant_repeticiones,
         .3             // prop_aristas_esp
     );
     guardar_resultados("../exp/UnaNuevaEsperanza-varN-n200k", tiempos);

}
