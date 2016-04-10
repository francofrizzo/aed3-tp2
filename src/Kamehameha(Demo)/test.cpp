#include "../main.h"
#include "./Kamehameha.h"
#include "../mini_test.h" // framework para tests unitarios

using namespace std;

/*
**  Tests unitarios
*/

// Compara dos vectores
template <typename T>
bool compararVectores(const vector<T> calculado, const vector<T> esperado) {
    if (calculado.size() != esperado.size()) {
        return false;
    } else {
        for (unsigned int i = 0; i < calculado.size(); i++) {
            if (calculado[i] != esperado[i]) {
                return false;
            }
        }
    }
    return true;
}

void test_vacio() {
    N = 0;
    coordenadasEnemigos = vector<XY>(N);
    // coordenadasEnemigos[0][0] = 1;
    // coordenadasEnemigos[0][1] = 1;

    vector<vector<unsigned int> > solucion = resolverKamehameha();
    vector<vector<unsigned int> > esperado = vector<vector<unsigned int>>();

    ASSERT(compararVectores(solucion, esperado));
}

void test_unico() {
    N = 1;
    coordenadasEnemigos = vector<XY>(N);
    coordenadasEnemigos[0] = XY(0,0);

    vector<vector<unsigned int> > solucion = resolverKamehameha();

    vector<vector<unsigned int> > esperado = vector<vector<unsigned int>>(1);
    esperado[0].push_back(0);

    ASSERT(compararVectores(solucion, esperado));
}

void test_cuatro_en_linea() {
    N = 4;
    coordenadasEnemigos = vector<XY>(N);
    coordenadasEnemigos[0] = XY(0,0);
    coordenadasEnemigos[1] = XY(1,1);
    coordenadasEnemigos[2] = XY(2,2);
    coordenadasEnemigos[3] = XY(3,3);

    vector<vector<unsigned int> > solucion = resolverKamehameha();

    ASSERT_EQ(solucion.size(), 1);
    ASSERT_EQ(solucion[0].size(), 4);
}

void test_cuadrado() {
    N = 4;
    coordenadasEnemigos = vector<XY>(N);
    coordenadasEnemigos[0] = XY(50,100);
    coordenadasEnemigos[1] = XY(50,150);
    coordenadasEnemigos[2] = XY(100,150);
    coordenadasEnemigos[3] = XY(100,100);

    vector<vector<unsigned int> > solucion = resolverKamehameha();

    ASSERT_EQ(solucion.size(), 2);
    ASSERT_EQ(solucion[0].size(), 2);
    ASSERT_EQ(solucion[1].size(), 2);
}

void test_tres_radiales() {
    N = 9;
    coordenadasEnemigos = vector<XY>(N);
    coordenadasEnemigos[0] = XY(22,31);
    coordenadasEnemigos[1] = XY(44,62);
    coordenadasEnemigos[2] = XY(5,21);
    coordenadasEnemigos[3] = XY(10,42);
    coordenadasEnemigos[4] = XY(15,63);
    coordenadasEnemigos[5] = XY(1001,32);
    coordenadasEnemigos[6] = XY(2002,64);
    coordenadasEnemigos[7] = XY(4004,128);
    coordenadasEnemigos[8] = XY(8008,256);

    vector<vector<unsigned int> > solucion = resolverKamehameha();

    ASSERT_EQ(solucion.size(), 3);
}

void correr_tests_unitarios() {
    RUN_TEST(test_vacio);
    RUN_TEST(test_unico);
    RUN_TEST(test_cuatro_en_linea);
    RUN_TEST(test_cuadrado);
    RUN_TEST(test_tres_radiales);
}
