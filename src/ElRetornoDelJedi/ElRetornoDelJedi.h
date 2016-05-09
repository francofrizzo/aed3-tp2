
#ifndef EL_RETORNO_DEL_JEDI_H
#define EL_RETORNO_DEL_JEDI_H


#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

pair< int, vector<char>  > resolver( int N, int M ,int H, vector < vector <int> > &E ,
	vector < vector < pair < int, char > > > &DP );
void imprimirCamino(vector<char> camino);
/*
**  Ejercicio 3: El retorno del (que te) jedi
*/

// Declarar acá funciones exportadas por la resolución del problema,
// variables globales, etc.

#endif
