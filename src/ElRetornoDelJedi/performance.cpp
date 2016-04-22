#include "../main.h"
#include "./ElRetornoDelJedi.h"

/*
**  Ejercicio 3: El retorno del (que te) jedi
**  Pruebas de performance
*/
int N,M,H;
vector< vector <int> > E;
vector< vector <int> > DP;

void correr_pruebas_performance() {
    // levanto el input
	cin << N << M << H;
	E = vector< vector<int>>(N, vector<int>(M));
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < M; ++j){
			cin << E[i][j] ;
		}
	}
	
	// Instacio el DP
	DP = vector< vector<int>>(N, vector<int>(M));
	DP[0][0] = 0;
	for (int i = 1; i < N; ++i){
		int delta = math.abs(E[i][0] - E[i-1][0]) 
		if(H < delta){
			DP[i][0] =  (delta - H) + DP[i-1][0];
		}else{
			DP[i][0] = DP[i-1][0];
		}
	}
	for (int i = 1; i < N; ++i){
		int delta = math.abs(E[0][i] - E[0][i-1]) 
		if(H < delta){
			DP[0][i] =  (delta - H) + DP[0][i-1];
		}else{
			DP[0][i] = DP[0][i-1];
		}
	}
	//
}
