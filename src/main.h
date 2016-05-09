#ifndef MAIN_H
#define MAIN_H

#include <chrono>        // medición de tiempos de ejecución
#include <iostream>      // cout, cin, <<
#include <fstream>       // open, close, <<
#include <iomanip>       // stoi
#include <unistd.h>      // getopt
#include <vector>        // vector

// Medición de tiempos
static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
void start_timer();
double stop_timer();

// Imprimir ayuda por pantalla
void mostrar_ayuda(char* path_ejecutable);

// Funciones principales
extern bool verbose;
void correr_solucion();
void correr_tests_unitarios();
void correr_pruebas_performance();

// Compara dos vectores
template <typename T>
bool compararVectores(const std::vector<T> v1, const std::vector<T> v2) {
    if (v1.size() != v2.size()) {
        return false;
    } else {
        for (unsigned int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
    }
    return true;
}

// Imprime un vector
template <typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (typename std::vector<T>::const_iterator it = v.begin();
        it != v.end(); ++it)
    {
        os << *it << ", ";
    }
    os << "\b\b]";
    return os;
}

#endif
