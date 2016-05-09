#ifndef UNA_NUEVA_ESPERANZA_H
#define UNA_NUEVA_ESPERANZA_H

#include <vector>        // vector
#include <queue>         // queue
#include <algorithm>     // reverse

/*
**  Ejercicio 1: Una nueva esperanza
*/

// Declarar acá funciones exportadas por la resolución del problema,
// variables globales, etc.

// Recibe la cantidad de nodos y la lista de aristas del grafo que modela
// el problema, y retorna la solución esperada, es decir, la lista ordenada
// de las cuevas visitadas. La solución INCLUYE la primera y última cuevas
std::vector<int> hallar_solucion(
    int N,
    const std::vector<std::vector<int>>& aristas
);

// Recibe la cantidad de nodos y la lista de aristas del grafo original,
// indicando cuáles son especiales. Crea el grafo modificad utilizado en la
// resolución del problema (replicando tres veces cada nodo y colocando las
// aristas necesarias) y devuelve las listas de adyacencia del mismo
std::vector<std::vector<int>> crear_grafo(
    int N,
    const std::vector<std::vector<int>>& aristas
);

// Encuentra el camino más corto entre el primer y el último nodo del grafo
// que le es pasado por listas de adyacencia, utilizando el algoritmo BFS
std::vector<int> hallar_camino(
    const std::vector<std::vector<int>>& grafo
);

#endif
