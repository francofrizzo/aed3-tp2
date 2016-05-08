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

#endif
