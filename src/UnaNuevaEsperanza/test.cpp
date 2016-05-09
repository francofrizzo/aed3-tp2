#include "../main.h"
#include "./UnaNuevaEsperanza.h"
#include "../mini_test.h" // framework para tests unitarios

/*
**  Ejercicio 1: Una nueva esperanza
**  Tests unitarios
*/

using namespace std;

void test_ir_y_volver() {
    int N = 5;
    vector<vector<int>> aristas = {{0, 4, 0},
                                   {4, 1, 0},
                                   {1, 2, 0},
                                   {2, 3, 1}};
    vector<int> esperado = {0, 4, 1, 2, 3, 2, 1, 4};
    vector<int> obtenido = hallar_solucion(N, aristas);
    ASSERT(compararVectores(obtenido, esperado));
}

void test_dos_rombos() {
    int N = 10;
    vector<vector<int>> aristas = {{0, 1, 0},
                                   {1, 2, 0},
                                   {1, 3, 1},
                                   {2, 4, 0},
                                   {3, 4, 0},
                                   {4, 5, 0},
                                   {5, 6, 0},
                                   {5, 7, 0},
                                   {6, 8, 1},
                                   {7, 8, 0},
                                   {8 ,9, 0}};
    vector<int> obtenido = hallar_solucion(N, aristas);
    ASSERT_EQ(obtenido.size(), 8);
}

void test_muchos_caminos() {
    int N = 8;
    vector<vector<int>> aristas = {{0, 1, 0},
                                   {0, 2, 0},
                                   {0, 3, 0},
                                   {0, 4, 0},
                                   {0, 5, 0},
                                   {0, 6, 0},
                                   {7, 1, 0},
                                   {7, 2, 0},
                                   {7, 3, 0},
                                   {7, 4, 0},
                                   {7, 5, 1},
                                   {7 ,6, 0}};
    vector<int> obtenido = hallar_solucion(N, aristas);
    ASSERT_EQ(obtenido.size(), 5);
}

void correr_tests_unitarios() {
    RUN_TEST(test_ir_y_volver);
    RUN_TEST(test_dos_rombos);
    RUN_TEST(test_muchos_caminos);
}
