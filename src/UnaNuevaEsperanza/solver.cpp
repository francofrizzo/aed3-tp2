#include "../main.h"
#include "./UnaNuevaEsperanza.h"

/*
**  Ejercicio 1: Una nueva esperanza
**  Resolución del ejercicio
*/

stack<int> resolver(int n, const vector< vector< pair<int, bool>>> &lista_ady){
	nodo_cueva nodo_inicial;

	nodo_inicial.padre = NULL;

	vector< vector<nodo_cueva>> listas_cuevas = vector< vector<nodo_cueva>>(3, vector<nodo_cueva>(n, nodo_inicial));

	for(int i = 0; i < n; i++){
		listas_cuevas[0][i].id = i;
		listas_cuevas[0][i].caminos_especiales = 0;
		listas_cuevas[1][i].id = i;
		listas_cuevas[1][i].caminos_especiales = 1;
		listas_cuevas[2][i].id = i;
		listas_cuevas[2][i].caminos_especiales = 2;
	}

	queue<nodo_cueva*> cola_nodos;

	// Al nodo incial lo marco como su propio padre
	listas_cuevas[0][0].padre = &listas_cuevas[0][0];
	cola_nodos.push(&listas_cuevas[0][0]);

	nodo_cueva* ptr_nodo_cueva;
	int id_nodo, id_nodo_ady, caminos_especiales;
	// Mientras queden nodos sin visitar
	while(!cola_nodos.empty()){
		ptr_nodo_cueva = cola_nodos.front();
		cola_nodos.pop();
		id_nodo = ptr_nodo_cueva->id;
		// Encolo todos los vecinos
		for(unsigned int i = 0; i < lista_ady[id_nodo].size(); i++){
			id_nodo_ady = lista_ady[id_nodo][i].first;
			caminos_especiales = ptr_nodo_cueva->caminos_especiales;
			// Si tengo un camino especial, encolo el nodo del grafo siguiente
			if(lista_ady[id_nodo][i].second == true){
				caminos_especiales = (caminos_especiales == 0) ? 1 : 2;
			}
			// Si ya recorrí este nodo no es necesario encolarlo
			if(listas_cuevas[caminos_especiales][id_nodo_ady].padre == NULL){
				listas_cuevas[caminos_especiales][id_nodo_ady].padre = ptr_nodo_cueva;
				cola_nodos.push(&listas_cuevas[caminos_especiales][id_nodo_ady]);
			}
		}
	}

	stack<int> camino_optimo;

	ptr_nodo_cueva = listas_cuevas[2][n - 1].padre;
	while(ptr_nodo_cueva->padre != ptr_nodo_cueva){
		camino_optimo.push(ptr_nodo_cueva->id);
		ptr_nodo_cueva = ptr_nodo_cueva->padre;
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
