#include "../main.h"
#include "./UnaNuevaEsperanza.h"

/*
**  Ejercicio 1: Una nueva esperanza
**  Resolución del ejercicio
*/

using namespace std;

void correr_solucion() {
    // Leer los datos de entrada
    uint N, M;
    vector<vector<int>> aristas;
    vector<vector<int>> grafo;

    cin >> N;
    cin >> M;

    aristas = vector<vector<int>>(M, vector<int>(3));

    for (uint i = 0; i < M; i++) {  // almacenar listas de aristas
        cin >> aristas[i][0];  // nodo 1
        cin >> aristas[i][1];  // nodo 2
        cin >> aristas[i][2];  // ¿es arista especial?
    }

    // Crear el grafo del problema (listas de adyacencia) a partir de las
    // listas de aristas y a continuación resolver el problema
    vector<int> solucion = hallar_solucion(N, aristas);

    // Imprimir la solución
    cout << solucion.size() - 1 << endl;

    for (uint i = 1; i < solucion.size() - 1; i++) {
        cout << solucion[i];
        if (i < solucion.size() - 1) {
            cout << " ";
        }
    }

    cout << endl;
}

vector<int> hallar_solucion(int N, const vector<vector<int>>& aristas) {
    vector<int> solucion = hallar_camino(crear_grafo(N, aristas));
    for (uint i = 0; i < solucion.size(); i++) {
        solucion[i] = solucion[i] % N;
    }
    return solucion;
}

vector<vector<int>> crear_grafo(int N, const vector<vector<int>>& aristas) {
    vector<vector<int>> grafo(3 * N);
    int nodo1, nodo2;

    for (uint i = 0; i < aristas.size(); i++) {
        nodo1 = aristas[i][0];
        nodo2 = aristas[i][1];

        if (aristas[i][2] == 0) {
            // Arista normal
            grafo[nodo1].push_back(nodo2);
            grafo[nodo2].push_back(nodo1);
            grafo[nodo1 + N].push_back(nodo2 + N);
            grafo[nodo2 + N].push_back(nodo1 + N);
            grafo[nodo1 + 2 * N].push_back(nodo2 + 2 * N);
            grafo[nodo2 + 2 * N].push_back(nodo1 + 2 * N);
        } else {
            // Arista especial
            grafo[nodo1].push_back(nodo2 + N);
            grafo[nodo2].push_back(nodo1 + N);
            grafo[nodo1 + N].push_back(nodo2 + 2 * N);
            grafo[nodo2 + N].push_back(nodo1 + 2 * N);
            grafo[nodo1 + 2 * N].push_back(nodo2 + 2 * N);
            grafo[nodo2 + 2 * N].push_back(nodo1 + 2 * N);
        }
    }

    // DEBUGGING
    // for (uint i = 0; i < grafo.size(); i++) {
    //     cout << i << ": ";
    //     for (uint j = 0; j < grafo[i].size(); j++) {
    //         cout << grafo[i][j] << " ";
    //     }
    //     cout << "\b" << endl;
    // }

    return grafo;
}

vector<int> hallar_camino(const vector<vector<int>>& grafo) {
    int N = grafo.size();
    vector<bool> marcado(N, false);
    vector<int> predecesor(N, -1);
    vector<int> solucion;
    queue<int> siguiente;

    siguiente.push(0);
    predecesor[0] = 0;

    while (! siguiente.empty()) {
        int i = siguiente.front();
        siguiente.pop();

        for (uint j = 0; j < grafo[i].size(); j++) {
            int vecino = grafo[i][j];
            if (! marcado[vecino]) {
                marcado[vecino] = true;
                predecesor[vecino] = i;
                siguiente.push(vecino);
            }
        }
    }

    int i = N - 1;
    while (i != 0) {
        solucion.push_back(i);
        i = predecesor[i];
    }
    solucion.push_back(i);

    reverse(solucion.begin(), solucion.end());
    return solucion;
}
