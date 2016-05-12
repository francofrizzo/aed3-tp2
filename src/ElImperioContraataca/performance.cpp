#include "../main.h"
#include "./ElImperioContraataca.h"

#include <cmath>

/*
**  Ejercicio 2: El Imperio contraataca
**  Pruebas de performance
*/

using namespace std;

#define CANT_INSTANCIAS         30
#define CANT_REPETICIONES       20
#define CANT_INST_DESCARTADAS   10

#define M_FIJO                  1000000
#define N_FIJO                  400
#define M_INICIAL               500000
#define M_FINAL                 700000
#define LONG_MAX_ARISTA         100


// Genera una instancia del problema con n vertices y m ejes de manera
// aleatoria. Al comienzo se genera un camino simple para asegurar
// que el grafo sea conexo. La disposicion de las aristas no afecta
// a la complejidad del algoritmo que lo resuelve.
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
        // cout << "\b\b\b\b\b\b\b\b\b\b" << setfill(' ') << setw(10) << aristasRestantes << flush;
        int nodo1 = rand() % n;
        int nodo2 = rand() % n;

        // Busca la arista para no repetir
        vector<pair<int, int>> vecinosDeNodo1 = rutas[nodo1];
        bool esta = false;
        unsigned int i = 0;
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
    if (!quiet){
        cout << "Escenario: N = " << n << endl;
        cout << "   #    aristas   OK" << endl;
    }

    vector<vector<pair<int, int>>> rutas;
    int maxAristas = n * (n - 1) / 2;
    int minAristas = n - 1;
    int rangoAristas =  maxAristas - minAristas;

    int m = minAristas;
    for (unsigned int i = 0; i < CANT_INSTANCIAS; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;

        if(!quiet)
            cout << setfill(' ') << setw(4) << i << "    " << setfill(' ') << setw(7) << m << "     " << flush;
        
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

        m += rangoAristas / CANT_INSTANCIAS;
    
    }
}

void ejecutarPruebaConMFijo(ofstream& archivoSalida, bool quiet, int m) {
    if (!quiet){
        cout << "Escenario: M = " << m << endl;
        cout << "   #      nodos   OK" << endl;
    }

    vector<vector<pair<int, int>>> rutas;
    int maxNodos = m + 1;
    int minNodos =  ceil((1 + sqrt(1 + 8 * m)) / 2);
    int rangoNodos =  maxNodos - minNodos;
    int n = minNodos;

    for (unsigned int i = 0; i < CANT_INSTANCIAS; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;

        if(!quiet)
            cout << setfill(' ') << setw(4) << i << "    " << setfill(' ') << setw(7) << n << "     " << flush;
        
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

        archivoSalida << n  << " " << tiempo_promedio << " " << desv_estandar << endl;

        if (!quiet)
            cout << "\b\b\b  ✓" << endl;

        n += rangoNodos / CANT_INSTANCIAS;
    
    }
}

void ejecutarPruebaArboles(ofstream& archivoSalida, bool quiet) {
    if (!quiet){
        cout << "Escenario: Arboles" << endl;
        cout << "   #    aristas       nodos   OK" << endl;
    }

    vector<vector<pair<int, int>>> rutas;
    int rangoAristas =  M_FINAL - M_INICIAL;
    int m = M_INICIAL;
    int n = m + 1;

    for (unsigned int i = 0; i < CANT_INSTANCIAS; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;

        if(!quiet)
            cout << setfill(' ') << setw(4) << i << "    " << setfill(' ') << setw(7) << m << "     " << setfill(' ') << setw(7) << n << "     " << flush;
        
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

        m += rangoAristas / CANT_INSTANCIAS;
        n = m + 1;
    
    }
}

void correr_pruebas_performance() {
    bool quiet = ! verbose;

    ofstream archivoSalida;

    archivoSalida.open("../exp/elImperioContraatacaMFijo");
    ejecutarPruebaConMFijo(archivoSalida, quiet, M_FIJO);
    archivoSalida.close();

    // archivoSalida.open("../exp/elImperioContraatacaNFijo");
    // ejecutarPruebaConNFijo(archivoSalida, quiet, N_FIJO);
    // archivoSalida.close();

    // archivoSalida.open("../exp/elImperioContraatacaArboles");
    // ejecutarPruebaArboles(archivoSalida, quiet);
    // archivoSalida.close();

}
