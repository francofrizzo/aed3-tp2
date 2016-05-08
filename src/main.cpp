#include "./main.h"

using namespace std;

// Modos de ejecución
#define MODE_DEFAULT           0
#define MODE_UNIT_TESTS        1
#define MODE_PERFORMANCE_TESTS 2

bool verbose = false;


int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    // bool verbose = false;
    int mode = MODE_DEFAULT;

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "htvp:")) != -1) {
        switch (opt) {
            case 'h': { // mostrar ayuda
                mostrar_ayuda(argv[0]);
                exit(0);
                break;
            }
            case 'v': { // ser verboso
                verbose = true;
                break;
            }
            case 't': { // correr tests unitarios
                mode = MODE_UNIT_TESTS;
                break;
            }
            case 'p': { // correr pruebas de performance
                srand(stoi(optarg)); // configura el seed que recibe por parámetro
                mode = MODE_PERFORMANCE_TESTS;
                break;
            }
            default: { // si las opciones son inválidas
                mostrar_ayuda(argv[0]);
                exit(1);
                break;
            }
        }
    }

    switch (mode) {
        case MODE_DEFAULT:
            correr_solucion();
            break;

        case MODE_UNIT_TESTS:
            correr_tests_unitarios();
            break;

        case MODE_PERFORMANCE_TESTS:
            correr_pruebas_performance();
            break;
    }
}

// Imprime por pantalla un texto de ayuda
void mostrar_ayuda(char* path_ejecutable) {
    cout << "  Modo de uso: " << setw(12) << path_ejecutable << endl;
    cout << endl;
    cout << "  Los parámetros se reciben a través de la entrada estándar." << endl;
    cout << endl;
    cout << "  Opciones:" << endl;
    cout << "    -h          Muestra este texto de ayuda" << endl;
    cout << "    -t          Ejecuta los tests unitarios provistos para el algoritmo" << endl;
    cout << "    -p <seed>   Ejecuta las pruebas de performance diseñadas para el algoritmo" << endl;
}

// Medición de tiempos
void start_timer() {
    start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
    chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
    return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}
