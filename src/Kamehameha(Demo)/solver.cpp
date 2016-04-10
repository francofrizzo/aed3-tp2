#include "../main.h"
#include "./Kamehameha.h"

using namespace std;

unsigned int N;
vector<XY> coordenadasEnemigos;

// Clase XY
XY::XY () {}

XY::XY (int x, int y) : x(x), y(y) {}

bool XY::operator==(const XY& otro) const {
    return this->x == otro.x && this->y == otro.y;
}

bool XY::operator!=(const XY& otro) const {
    return this->x != otro.x || this->y != otro.y;
}

ostream& operator<<(ostream& os, const XY& xy){
    os << "(" << xy.x << "," << xy.y << ")";
    return os;
}

// Representa una recta en el plano bidimensional
Recta::Recta (XY a, XY b) : a(a), b(b) {};

bool Recta::pasaPor(const XY p) const {
    return (b.x - a.x) * (p.y - a.y) == (p.x - a.x) * (b.y - a.y);
}

bool Recta::operator==(const Recta& otra) const {
    return this->pasaPor(otra.a) && this->pasaPor(otra.b);
}

ostream& Recta::imprimir(ostream& os) const {
    os << "<" << this->a << ";" << this->b << ">";
    return os;
}

XY Recta::puntoAleatorio() const {
    XY punto;
    do {
        int deltaX = this->a.x - this->b.x;
        int deltaY = this->a.y - this->b.y;
        int mult = rand();
        punto = XY(abs(this->a.x + mult * deltaX), abs(this->a.y + mult * deltaY));
    } while (punto == this->b || ! this->pasaPor(punto));
    return punto;
}

ostream& operator<<(ostream& os, const Recta& r) {
    r.imprimir(os);
    return os;
}

// Imprime la solución con el formato esperado
void imprimirSolucion(vector< vector <unsigned int> > solucion) {
    cout << solucion.size() << endl;
    for (unsigned int i = 0; i < solucion.size(); i++) {
        cout << solucion[i].size();
        for (unsigned int j = 0; j < solucion[i].size(); j++) {
            cout << " " << solucion[i][j] + 1;
        }
        cout << endl;
    }
}

/*
**  Variables globales
*/

// Imprime por la salida estándar las coordenadas de los enemigos
void imprimirEnemigos() {
    for (unsigned int i = 0; i < coordenadasEnemigos.size(); i++) {
        cout << coordenadasEnemigos[i] << "; ";
    }
    cout << endl;
}

/*
**  Resolución del ejercicio
*/

// Saca los enemigos que destruye de enemigosRestantes y los agrega a
// enemigosDestruidos
vector<unsigned int> destruirEnemigos(vector<unsigned int> &enemigosRestantes, Recta kamehameha){
    vector<unsigned int> destruidos;

    unsigned int i = 0;
    while (i < enemigosRestantes.size()) {
        if (kamehameha.pasaPor(coordenadasEnemigos[enemigosRestantes[i]])){
            destruidos.push_back(enemigosRestantes[i]);
            enemigosRestantes.erase(enemigosRestantes.begin() + i);
        }
        else {
            i++;
        }
    }

    return destruidos;
}

bool resolverKamehamehaRecursivo(vector<unsigned int> enemigos, vector<vector<unsigned int>>& solucion, unsigned int limite) {
    // solucion = vector<vector<unsigned int>>();

    if (enemigos.size() == 0) {
        return true;
    } else if (limite > 0) {
        if (enemigos.size() == 1 || enemigos.size() == 2) {
            solucion.push_back(enemigos);
            return true;
        } else {
            vector<vector<unsigned int> > mejorSubsolucion;
            bool haySubsolucionValida = false;
            vector<Recta> kamehamehasProbados;

            // Todas las posibles combinaciones de Kamehamehas sin contar las que ya hice al reves
            // Ejempĺo: si hice un kamehameha de 0,0 a 1,1 no voy a hacer de 1,1 a 0,0 porque es lo mismo
            for (unsigned int i = 0; i < enemigos.size() - 1; i++){
                for (unsigned int j = i + 1; j < enemigos.size(); j++){
                    Recta kamehameha = Recta(coordenadasEnemigos[enemigos[i]], coordenadasEnemigos[enemigos[j]]);

                    bool repetido = false;
                    for (unsigned int k = 0; k < kamehamehasProbados.size(); k++) {
                        if (kamehameha == kamehamehasProbados[k]) {
                            repetido = true;
                            break;
                        }
                    }

                    if (!repetido) {
                        kamehamehasProbados.push_back(kamehameha);
                        vector<unsigned int> enemigosRestantes = enemigos;
                        vector<vector<unsigned int> > subsolucion;
                        subsolucion.push_back(destruirEnemigos(enemigosRestantes, kamehameha));

                        if (enemigosRestantes.size() > 0) {
                            vector<vector<unsigned int> > subsolucionRecursiva;
                            if (resolverKamehamehaRecursivo(enemigosRestantes, subsolucionRecursiva, limite - 1)) {
                                haySubsolucionValida = true;
                                subsolucion.insert(subsolucion.end(), subsolucionRecursiva.begin(), subsolucionRecursiva.end());
                                mejorSubsolucion = subsolucion;
                                limite = subsolucion.size();
                            }
                        } else {
                            haySubsolucionValida = true;
                            mejorSubsolucion = subsolucion;
                            limite = 1;
                        }
                    }
                }
            }

            if (haySubsolucionValida) {
                solucion.insert(solucion.end(), mejorSubsolucion.begin(), mejorSubsolucion.end());
                return true;
            }
        }
    }

    return false;
}

vector<vector<unsigned int> > resolverKamehameha() {
    vector<unsigned int> enemigos = vector<unsigned int>(N);
    iota(enemigos.begin(), enemigos.end(), 0);

    vector<vector<unsigned int> > solucion;
    resolverKamehamehaRecursivo(enemigos, solucion, N);
    return solucion;
}

void correr_solucion() {
    cin >> N;

    for (unsigned int i = 0; i < N; i++){
        XY enemigo;
        cin >> enemigo.x >> enemigo.y;
        coordenadasEnemigos.push_back(enemigo);
    }

    vector< vector< unsigned int > > solucion = resolverKamehameha();

    imprimirSolucion(solucion);
}

