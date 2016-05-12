#ifndef EL_RETORNO_DEL_JEDI_H
#define EL_RETORNO_DEL_JEDI_H

#include <algorithm>
#include <cmath>
#include <utility>

/*
**  Ejercicio 3: El retorno del (que te) jedi
*/

// Declarar acá funciones exportadas por la resolución del problema,
// variables globales, etc.

std::pair<int, std::vector<char>> resolver(
    int N,
    int M,
    int H,
    std::vector<std::vector<int>> &E ,
    std::vector<std::vector<std::pair<int, char >>> &DP
);

void imprimirCamino(std::vector<char> camino);

#endif
