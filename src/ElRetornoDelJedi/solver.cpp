#include "../main.h"
#include "./ElRetornoDelJedi.h"

using namespace std;
/*
**  Ejercicio 3: El retorno del (que te) jedi
**  Resolución del ejercicio
*/

void imprimirCamino(vector<char> camino){
	for (unsigned int i = 0; i < camino.size(); ++i){
		cout << camino[i] << " -> " ;
	}
	cout << endl;
}
int calcularEnergiaGastada(int xOrigen ,int yOrigen , int xDestino, int yDestino, int H , vector < vector <int> > &E){
	int delta = abs(E[yOrigen][xOrigen] - E[yDestino][xDestino]);
	// cout << "delta: " << delta << endl;
	// cout << "H: " << H << endl;
	if(H > delta){
		return  0 ;
	}else{
		return delta - H;
	}
}

pair< int, vector<char>  > resolver( int N, int M ,int H, vector < vector <int> > &E ,
	vector < vector < pair < int, char > > > &DP ) {
	//cout << " Strat resolver" << endl;
	// Instancio el DP
	DP = vector< vector< pair < int, char > > >(N, vector < pair < int, char > > (M, make_pair (-1,'Z')));
	DP[0][0] = pair<int,char>(0,'I');
	int costoY = 0;
	int costoX = 0;
	//cout << " Calculo la primera columna. " << endl;
	for (int i = 1; i < N; ++i){
		// cout << "i : " << i << " j : " << 0 << endl;
		costoY = DP[i - 1][0].first + calcularEnergiaGastada(0, i-1, 0, i, H, E);
		DP[i][0] = pair<int,char>(costoY,'X');
		
	}
	//cout << " Calculo la primera Fila. " << endl;
	for (int j = 1; j < M; ++j){
		// cout << "i : " << 0 << " j : " << j << endl;
		costoX = DP[0][j - 1].first + calcularEnergiaGastada(j-1, 0, j, 0, H, E);
		DP[0][j] =  pair<int,char>(costoX,'Y');
	}

	//cout << " LLeno la matriz ;) " << endl;
	for (int i = 1; i < N; ++i){
		for (int j = 1; j < M; ++j){
			// cout << "i : " << i << " j : " << j << endl;
			// si me moviera por el eje Y
			int costoY = DP[i-1][j].first + calcularEnergiaGastada(j, i-1,j, i, H, E);
			// si me moviera por el eje X
			int costoX = DP[i][j-1].first + calcularEnergiaGastada(j-1, i, j, i, H, E);
			if (costoX > costoY){
				DP[i][j] = pair<int,char>(costoY,'X');
			}else{
				DP[i][j] = pair<int,char>(costoX,'Y');
			}

		}
	}
	int i = N - 1;
	int j = M - 1;
	vector<char> camino = vector<char>(N + M - 2);
	// cout << " Armo el camino." << endl;
	// cout << "i : " << i << " j : " << j << endl;
	// cout << "DP[i][j].second : " << DP[i][j].second << endl;
	// cout << "DP[i][j].first : " << DP[i][j].first << endl;
	while(i + j > 0){
		// cout << "i : " << i << " j : " << j << endl;
		// cout << "DP[i][j].second : " << DP[i][j].second << endl;
		camino[i + j - 1] = DP[i][j].second;
		if (DP[i][j].second == 'Y'){
			j--;
		}else{
			i--;
		}
	}
	
	pair< int, vector<char>  > result = make_pair(DP[N-1][M-1].first,camino);
	// cout << "result.first: " << result.first << endl;
	return result;
}

void correr_solucion() {
	int N,M,H;
	vector < vector <int> > E;
	vector < vector < pair < int, char > > > DP;
    // levanto el input
	cin >> N >> M >> H;
	E = vector< vector<int> >(N, vector < int >(M));
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < M; ++j){
			cin >> E[i][j] ;
		}
	}
	
	pair < int, vector < char >  > res = resolver(N,M,H,E,DP);
	cout << res.first << endl;
	vector < char > camino = res.second;
	for (unsigned int i = 0; i < camino.size(); ++i){
		cout << camino[i] << endl;
	}
}







