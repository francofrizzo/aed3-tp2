#include "../main.h"
#include "./ElRetornoDelJedi.h"

using namespace std;
/*
**  Ejercicio 3: El retorno del (que te) jedi
**  Resolución del ejercicio
*/

int calcularEnergiaGastada(int xDsd ,int yDsd , int xHst, int yHst, int H , vector < vector <int> > &E){
	int delta = abs(E[xDsd][yDsd] - E[xHst][yHst]); 
	if(H > delta){
		return  (delta - H) ;
	}else{
		return 0;
	}
}

pair< int, vector<char>  > resolver( int N, int M ,int H, vector < vector <int> > &E ,
	vector < vector < pair < int, char > > > &DP ){
	// Instacio el DP
	DP = vector< vector< pair < int, char > > >(N, vector < pair < int, char > > (M, make_pair (-1,'X')));
	DP[0][0] = pair<int,char>(0,'I');
	// Calculo la primera columnas
	for (int i = 1; i < N; ++i){
		int X = DP[i - 1][0].first + calcularEnergiaGastada(i-1,0,i,0,H,E);
		DP[i][0] = pair<int,char>(X,'X');
		
	}
	// Calculo la primera filas
	for (int j = 1; j < M; ++j){
		int Y = DP[0][j - 1].first + calcularEnergiaGastada(0,j-1,0,j,H,E);
		DP[0][j] =  pair<int,char>(Y,'Y');
	}

	// LLeno la matriz ;)
	for (int i = 1; i < N; ++i){
		for (int j = 1; j < M; ++j){
			// si me moveria por el eje X
			int X = DP[i-1][j].first + calcularEnergiaGastada(i-1,j,i,j,H,E);
			// si me moveria por el eje Y
			int Y = DP[i][j-1].first + calcularEnergiaGastada(i,j-1,i,j,H,E);
			if (X < Y){
				DP[i][j] = pair<int,char>(Y,'Y');
			}else{
				DP[i][j] = pair<int,char>(X,'X');
			}

		}
	}
	int i = N;
	int j = M;
	vector<char> r;
	while(DP[i][j].second != 'I'){
		r.push_back(DP[i][j].second);
		if (DP[i][j].second == 'Y'){
			j--;
		}else{
			i--;
		}
	}
	reverse(r.begin(),r.end());
	return make_pair(DP[N][M].second,r);
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







