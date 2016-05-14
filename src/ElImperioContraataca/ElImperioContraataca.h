#ifndef EL_IMPERIO_CONTRAATACA_H
#define EL_IMPERIO_CONTRAATACA_H

#include <vector>        // vector
#include <algorithm>     // iter_swap

/*
**  Ejercicio 2: El Imperio contraataca
*/

// Recibe un grafo en forma de listas de adyacencia. Calcula, utilizando el
// algoritmo de Prim, un árbol generador mínimo del grafo, y lo devuelve a
// través de un vector indicando el predecesor de cada nodo en dicho árbol
std::vector<int> prim(
    const std::vector<std::vector<std::pair<int, int>>>& vecinos
);

// Calcula el peso total de un árbol generador de un grafo, dados el árbol en
// forma de vector de predecesores y el grafo en forma de listas de adyacencia
int peso_arbol_generador(
    std::vector<int>& arbol,
    const std::vector<std::vector<std::pair<int, int>>>& vecinos
);



/*
**  Estructura de datos:
**  Cola de prioridad implementada sobre heap binario
*/

class cola_prioridad {
 private:
    uint                             cant_items;
    std::vector<int>                 pos_en_heap;
    std::vector<std::pair<int, int>> contenedor;

    void subir(uint i);
    void bajar(uint i);

 public:
    cola_prioridad(uint n);

    bool vacia() const;
    int  min_indice() const;
    int  min_prioridad() const;
    void desencolar();
    int  prioridad(int i) const;
    void setear_prioridad(int indice, int prioridad);
};

#endif
