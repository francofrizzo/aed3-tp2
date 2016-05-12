#include "../main.h"
#include "./UnaNuevaEsperanza.h"

/*
**  Ejercicio 1: Una nueva esperanza
**  Resolución del ejercicio
*/

stack<int> resolver(int n, const vector< vector< pair<int, bool>>> &lista_ady){
	// Representación para los estados de un nodo
	// 0..n - 1: No se recorrió ningún pasillo especial
	// n..2*n - 1: Se recorrió un pasillo especial
	// 2*n..3*n - 1: Se recorrieron al menos dos pasillos especiales
	vector<int> lista_cuevas = vector<int>(3*n, -1);

	queue<int> cola_nodos;

	// Al nodo incial lo marco como su propio padre
	lista_cuevas[0] = 0;
	cola_nodos.push(0);

	int id_nodo, id_nodo_efectivo, id_nodo_ady;
	// Mientras queden nodos sin visitar
	while(!cola_nodos.empty()){
		id_nodo	= cola_nodos.front();
		id_nodo_efectivo = id_nodo % n;
		cola_nodos.pop();
		// Encolo todos los vecinos
		for(unsigned int i = 0; i < lista_ady[id_nodo_efectivo].size(); i++){
			id_nodo_ady = (id_nodo - id_nodo_efectivo) + lista_ady[id_nodo_efectivo][i].first;

			// Si tengo un camino especial, encolo el nodo del grafo siguiente
			if(lista_ady[id_nodo_efectivo][i].second == true && id_nodo_ady/n < 2){
				id_nodo_ady += n;
			}

			// Si ya recorrí este nodo no es necesario encolarlo
			if(lista_cuevas[id_nodo_ady] == -1){
				lista_cuevas[id_nodo_ady] = id_nodo;
				cola_nodos.push(id_nodo_ady);
			}
		}
	}

	stack<int> camino_optimo;

	int j = lista_cuevas[3*n - 1];
	while(lista_cuevas[j] != j){
		camino_optimo.push(j % n);
		j = lista_cuevas[j];
	}

	return camino_optimo;
}

void correr_solucion() {
	int n, m;

	cin >> n >> m;

	vector< vector< pair<int, bool>>> lista_ady = vector< vector< pair<int, bool>>>(n);

	int tmp_a, tmp_b, tmp_e;

	for(int i = 0; i < m; i++){
		cin >> tmp_a >> tmp_b >> tmp_e;
		lista_ady[tmp_a].push_back(pair<int, bool>(tmp_b, tmp_e));
		lista_ady[tmp_b].push_back(pair<int, bool>(tmp_a, tmp_e));
	}

	stack<int> solucion = resolver(n, lista_ady);

	cout << solucion.size() + 1 << endl;
	while(!solucion.empty()){
		cout << solucion.top() << " ";
		solucion.pop();
	}
}
