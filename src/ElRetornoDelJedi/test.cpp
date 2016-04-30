#include "../main.h"
#include "./ElRetornoDelJedi.h"
#include "../mini_test.h" // framework para tests unitarios

/*
**  Ejercicio 3: El retorno del (que te) jedi
**  Tests unitarios
*/



void test_unico() {
	int N = 1;
	int M = 1;
	int H = 666;
	vector < vector <int> > E = vector < vector <int> >(N, vector <int> (M,700));
	vector < vector < pair < int, char > > > DP;
	pair < int, vector <char>  > solucion = resolver(N,M,H,E,DP);
	pair < int, vector <char>  > esperado = make_pair(0,vector <char> ());

	ASSERT_EQ(esperado.first, solucion.first);
	ASSERT(compararVectores(solucion.second, esperado.second));

}

void correr_tests_unitarios() {
    RUN_TEST(test_unico);
}
