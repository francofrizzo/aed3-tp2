#include "../main.h"
#include "./ElImperioContraataca.h"

#include <limits>        // numeric_limits

/*
**  Ejercicio 2: El Imperio contraataca
**  Resolución del ejercicio
*/

using namespace std;

void correr_solucion() {
    std::cout << "Acá todavía no hay nada" << std::endl;
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
        contenedor[i]  = {i, 0};
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
    while (i != 0 &&
           contenedor[(i + 1) / 2 - 1].second > contenedor[i].second)
    {
        std::iter_swap(contenedor.begin() + i,
                       contenedor.begin() + (i + 1) / 2 - 1);
        pos_en_heap[contenedor[i].first] = i;
        pos_en_heap[contenedor[(i + 1) / 2 - 1].first] = (i + 1) / 2 - 1;
        i = (i + 1) / 2 - 1;
    }
}

void cola_prioridad::bajar(uint i) {
    while ((2 * i + 1 < contenedor.size() &&
           contenedor[i].second > contenedor[2 * i + 1].second) ||
           (2 * i + 2 < contenedor.size() &&
           contenedor[i].second > contenedor[2 * i + 2].second))
    {
        if (2 * i + 2 < contenedor.size() &&
            contenedor[2 * i + 1].second > contenedor[2 * i + 2].second)
        {
            std::iter_swap(contenedor.begin() + i,
                           contenedor.begin() + 2 * i + 2);
            pos_en_heap[contenedor[i].first] = i;
            pos_en_heap[contenedor[2 * i + 2].first] = 2 * i + 2;
            i = 2 * i + 2;
        } else {
            std::iter_swap(contenedor.begin() + i,
                           contenedor.begin() + 2 * i + 1);
            pos_en_heap[contenedor[i].first] = i;
            pos_en_heap[contenedor[2 * i + 1].first] = 2 * i + 1;
            i = 2 * i + 1;
        }
    }
}
