#ifndef EL_IMPERIO_CONTRAATACA_H
#define EL_IMPERIO_CONTRAATACA_H

#include <vector>        // vector
#include <algorithm>     // iter_swap

/*
**  Ejercicio 2: El Imperio contraataca
*/



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
