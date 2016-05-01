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
int calcularEnergiaGastada(int xDsd ,int yDsd , int xHst, int yHst, int H , vector < vector <int> > &E){
	int delta = abs(E[xDsd][yDsd] - E[xHst][yHst]); 
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
	// cout << " Strat resolver" << endl;
	// Instacio el DP
	DP = vector< vector< pair < int, char > > >(N, vector < pair < int, char > > (M, make_pair (-1,'X')));
	DP[0][0] = pair<int,char>(0,'I');

	// cout << " Calculo la primera columnas. " << endl;
	for (int i = 1; i < N; ++i){
		// cout << "i : " << i << " j : " << 0 << endl;
		int X = DP[i - 1][0].first + calcularEnergiaGastada(i-1,0,i,0,H,E);
		DP[i][0] = pair<int,char>(X,'Y');
		
	}
	// cout << " Calculo la primera filas. " << endl;
	for (int j = 1; j < M; ++j){
		// cout << "i : " << 0 << " j : " << j << endl;
		int Y = DP[0][j - 1].first + calcularEnergiaGastada(0,j-1,0,j,H,E);
		DP[0][j] =  pair<int,char>(Y,'X');
	}

	// cout << " LLeno la matriz ;) " << endl;
	for (int i = 1; i < N; ++i){
		for (int j = 1; j < M; ++j){
			// cout << "i : " << i << " j : " << j << endl;
			// si me moveria por el eje X
			int X = DP[i-1][j].first + calcularEnergiaGastada(i-1,j,i,j,H,E);
			// si me moveria por el eje Y
			int Y = DP[i][j-1].first + calcularEnergiaGastada(i,j-1,i,j,H,E);
			if (X > Y){
				DP[i][j] = pair<int,char>(Y,'X');
			}else{
				DP[i][j] = pair<int,char>(X,'Y');
			}

		}
	}
	int i = N -1;
	int j = M -1 ;
	vector<char> camino;
	// cout << " Armo el camino." << endl;
	// cout << "i : " << i << " j : " << j << endl;
	// cout << "DP[i][j].second : " << DP[i][j].second << endl;
	// cout << "DP[i][j].first : " << DP[i][j].first << endl;
	while(DP[i][j].second != 'I'){
		// cout << "i : " << i << " j : " << j << endl;
		// cout << "DP[i][j].second : " << DP[i][j].second << endl;
		camino.push_back(DP[i][j].second);
		if (DP[i][j].second == 'X'){
			j--;
		}else{
			i--;
		}
	}
	
	reverse(camino.begin(),camino.end());
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







