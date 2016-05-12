#include "../main.h"
#include "./ElImperioContraataca.h"

#include <limits>        // numeric_limits

/*
**  Ejercicio 2: El Imperio contraataca
**  Resolución del ejercicio
*/

using namespace std;

void correr_solucion() {

    // Leer los datos de entrada
    uint N, M;
    vector<vector<pair<int, int>>> rutas;

    cin >> N;
    cin >> M;

    rutas = vector<vector<pair<int, int>>>(N);

    int planeta1;
    int planeta2;
    int longitud;

    for (uint i = 0; i < M; i++) {  // crear de listas de adyacencia
        cin >> planeta1;
        cin >> planeta2;
        cin >> longitud;

        rutas[planeta1].push_back(pair<int, int>(planeta2, longitud));
        rutas[planeta2].push_back(pair<int, int>(planeta1, longitud));
    }

    // Resolver el problema
    vector<int> agm = prim(rutas);

    // Calcular el total de combustible utilizado
    int total_combustible = peso_arbol_generador(agm, rutas);

    // Imprimir la solución
    cout << total_combustible << endl;

    for (uint i = 1; i < N; i++) {
        cout << agm[i] << endl;
    }

}

vector<int> prim(const vector<vector<pair<int, int>>>& vecinos) {
    uint N = vecinos.size();

    // Crear una cola de prioridad que contiene a todos los nodos
    // La prioridad inicial es infinita (máximo int posible)
    cola_prioridad vertices(N);

    // Establecer en 0 la prioridad del primer vértice
    vertices.setear_prioridad(0, 0);

    // En este vector se registrarán los nodos que ya no deben procesarse
    vector<bool> vertices_marcados(N, false);

    // Aquí se irá formando la solución del problema
    vector<int> predecesores(N, 0);

    // Iterar hasta que la cola esté vacía
    while (! vertices.vacia()) {
        // Desencolar el vértice con menor prioridad (esto representa al
        // vértice unido al árbol generado hasta el momento por la arista
        // más corta posible). Marcarlo como visitado
        int vert_actual = vertices.min_indice();
        vertices.desencolar();
        vertices_marcados[vert_actual] = true;

        // Iterar sobre los vecinos no marcados del nodo seleccionado
        for (uint j = 0; j < vecinos[vert_actual].size(); j++) {
            int ind_vecino  = vecinos[vert_actual][j].first;

            if (! vertices_marcados[ind_vecino]) {
                int long_arista = vecinos[vert_actual][j].second;

                // Comparar la longitud de la arista recién examinada con
                // el valor almacenado como prioridad del vecino, y en caso
                // de que sea necesario, actualizar este valor
                if (long_arista < vertices.prioridad(ind_vecino) ||
                    vertices.prioridad(ind_vecino) == -1) {
                    vertices.setear_prioridad(ind_vecino, long_arista);
                    predecesores[ind_vecino] = vert_actual;
                }
            }
        }
    }

    return predecesores;
}

int peso_arbol_generador(
    vector<int>& arbol,
    const vector<vector<pair<int, int>>>& vecinos
) {
    int peso = 0;
    for (uint i = 0; i < vecinos.size(); i++) {
        uint j;
        for (j = 0; j < vecinos[i].size(); j++) {
            if (vecinos[i][j].first == arbol[i]) {
                break;
            }
        }
        peso += vecinos[i][j].second;
    }

    return peso;
}



/*
**  Estructura de datos:
**  Cola de prioridad implementada sobre heap binario
*/

// Constructor

cola_prioridad::cola_prioridad(uint n) {
    cant_items  = n;
    pos_en_heap = std::vector<int>(n);
    contenedor  = std::vector<std::pair<int, int>>(n);

    for (uint i = 0; i < n; i++) {
        pos_en_heap[i] = i;
        contenedor[i]  = {i, numeric_limits<int>::max()};
    }
}

// Métodos públicos

bool cola_prioridad::vacia() const {
    return cant_items == 0;
}

int cola_prioridad::min_indice() const {
    return contenedor.front().first;
}

int cola_prioridad::min_prioridad() const {
    return contenedor.front().second;
}

void cola_prioridad::desencolar() {
    std::iter_swap(contenedor.begin(), contenedor.end() - 1);
    pos_en_heap[contenedor[0].first] = 0;
    pos_en_heap[contenedor[contenedor.size() - 1].first] = -1;
    contenedor.pop_back();
    cant_items--;
    bajar(0);
}

int cola_prioridad::prioridad(int i) const {
    return contenedor[pos_en_heap[i]].second;
}

void cola_prioridad::setear_prioridad(int indice, int prioridad) {
    int prioridad_actual = contenedor[pos_en_heap[indice]].second;
    contenedor[pos_en_heap[indice]].second = prioridad;

    if (prioridad > prioridad_actual) {
        bajar(pos_en_heap[indice]);
    } else if (prioridad < prioridad_actual) {
        subir(pos_en_heap[indice]);
    }
}

// Métodos privados

void cola_prioridad::subir(uint i) {
    uint nuevo_i = (i + 1) / 2 - 1;

    while (i != 0 &&
           contenedor[nuevo_i].second > contenedor[i].second)
    {
        std::iter_swap(contenedor.begin() + i,
                       contenedor.begin() + nuevo_i);
        pos_en_heap[contenedor[i].first] = i;
        pos_en_heap[contenedor[nuevo_i].first] = nuevo_i;

        i = nuevo_i;
        nuevo_i = (i + 1) / 2 - 1;
    }
}

void cola_prioridad::bajar(uint i) {
    uint nuevo_i_1 = 2 * i + 1;
    uint nuevo_i_2 = 2 * i + 2;

    while ((nuevo_i_1 < contenedor.size() &&
           contenedor[i].second > contenedor[nuevo_i_1].second) ||
           (nuevo_i_2 < contenedor.size() &&
           contenedor[i].second > contenedor[nuevo_i_2].second))
    {
        if (nuevo_i_2 < contenedor.size() &&
            contenedor[nuevo_i_1].second > contenedor[nuevo_i_2].second)
        {
            std::iter_swap(contenedor.begin() + i,
                           contenedor.begin() + nuevo_i_2);
            pos_en_heap[contenedor[i].first] = i;
            pos_en_heap[contenedor[nuevo_i_2].first] = nuevo_i_2;
            i = nuevo_i_2;
        } else {
            std::iter_swap(contenedor.begin() + i,
                           contenedor.begin() + nuevo_i_1);
            pos_en_heap[contenedor[i].first] = i;
            pos_en_heap[contenedor[nuevo_i_1].first] = nuevo_i_1;
            i = nuevo_i_1;
        }

        nuevo_i_1 = 2 * i + 1;
        nuevo_i_2 = 2 * i + 2;
    }
}
