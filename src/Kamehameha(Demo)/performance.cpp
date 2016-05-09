#include "../main.h"
#include "./Kamehameha.h"


/*
**  Pruebas de performance
*/

#define MAX_N                 12
#define CANT_REPETICIONES     40
#define CANT_INST_DESCARTADAS 20
#define CANT_REP_COMPLETAS     1

#define PRUEBA_PEOR_CASO       0
#define PRUEBA_CASO_INTERMEDIO 1
#define PRUEBA_MEJOR_CASO      2
#define PRUEBA_RANDOM          3

// Genera una instancia del problema de tamaño n donde no existen tres enemigos
// que se encuentren alineados
vector<XY> generarPeorCaso(unsigned int n) {
    vector<XY> enemigos;

    if (n >= 1) {
        enemigos.push_back(XY(rand(), rand()));
    }

    if (n >=2) {
        XY enemigo;
        do {
            enemigo = XY(rand(), rand());
        } while (enemigo == enemigos[0]);
        enemigos.push_back(enemigo);
    }

    for (unsigned int i = 2; i < n; i++) {
        XY enemigo;
        bool repetido = true;
        while (repetido) {
            enemigo = XY(rand(), rand());
            repetido = false;
            for (unsigned int j = 0; j < enemigos.size(); j++) {
                for (unsigned int k = j + 1; k < enemigos.size(); k++) {
                    Recta r = Recta(enemigos[j], enemigos[k]);
                    if (r.pasaPor(enemigo)) {
                        repetido = true;
                        break;
                        break;
                    }
                }
            }
        }
        enemigos.push_back(enemigo);
    }

    // cout << "PEOR   " << enemigos.size() << endl;

    return enemigos;
}

// Genera una instancia del problema de tamaño n donde todos los enemigos se
// encuentran sobre una única línea recta
vector<XY> generarMejorCaso(unsigned int n) {
    vector<XY> enemigos;

    if (n >= 1) {
        enemigos.push_back(XY(rand(), rand()));
    }

    if (n >=2) {
        XY enemigo;
        do {
            enemigo = XY(rand(), rand());
        } while (enemigo == enemigos[0]);
        enemigos.push_back(enemigo);
    }

    if (n >= 3) {
        Recta r = Recta(enemigos[0], enemigos[1]);

        for (unsigned int i = 2; i < n; i++) {
            XY enemigo;
            bool repetido = true;
            while (repetido) {
                enemigo = r.puntoAleatorio();
                repetido = false;
                for (unsigned int j = 2; j < enemigos.size(); j++) {
                    if (enemigo == enemigos[j]) {
                        repetido = true;
                        break;
                    }
                }
            }
            enemigos.push_back(enemigo);
        }
    }

    // cout << "MEJOR  " << enemigos.size() << endl;

    return enemigos;
}

// Genera una instancia del problema de tamaño n donde la mitad de los enemigos
// se encuentran sobre una línea recta y la otra mitad, sobre otra línea recta
// NOTA: las rectas podrían no ser distintas. Sin embargo, la probabilidad de
// que esto suceda es despreciable
vector<XY> generarCasoIntermedioRandom(unsigned int n) {
    vector<XY> enemigos;

    unsigned int k;
    unsigned int restantes = n;

    while (restantes > 0) {
        if (restantes < 4) {
            k = restantes;
        } else {
            k = (rand() % (restantes - 3)) + 3;
        }
        vector<XY> subEnemigos = generarMejorCaso(k);
        enemigos.insert(enemigos.end(), subEnemigos.begin(), subEnemigos.end());
        restantes = restantes - k;
    }

    random_shuffle(enemigos.begin(), enemigos.end());

    // cout << "INTERM " << enemigos.size() << endl;

    return enemigos;
}

// Genera una instancia del problema de tamaño n de forma totalmente aleatoria
vector<XY> generarCasoRandom(unsigned int n) {
    vector<XY> enemigos;

    for (unsigned int i = 0; i < n; i ++) {
        enemigos.push_back(XY(rand(), rand()));
    }

    // cout << "RANDOM " << enemigos.size() << endl;

    return enemigos;
}

// Genera una instancia del problema de tamaño n dividiendo a los enemigos en
// subconjuntos de tamaño aleatorio y ubicando a cada subconjunto sobre una
// línea recta
vector<XY> generarCasoIntermedio(unsigned int n) {
    unsigned int k = n / 2;

    vector<XY> subEnemigos1 = generarMejorCaso(k);
    vector<XY> subEnemigos2 = generarMejorCaso(n - k);

    subEnemigos1.insert(subEnemigos1.end(), subEnemigos2.begin(), subEnemigos2.end());

    random_shuffle(subEnemigos1.begin(), subEnemigos1.end());
    // cout << "INTERM " << subEnemigos1.size() << endl;
    
    return subEnemigos1;

}

void ejecutarPruebas(int prueba_id, ofstream& archivoSalida, bool quiet) {
    if (!quiet) {
        switch (prueba_id) {
            case PRUEBA_MEJOR_CASO:
                cout << "Escenario: mejor caso" << endl; break;
            case PRUEBA_CASO_INTERMEDIO:
                cout << "Escenario: caso intermedio" << endl; break;
            case PRUEBA_PEOR_CASO:
                cout << "Escenario: peor caso" << endl; break;
            case PRUEBA_RANDOM:
                cout << "Escenario: aleatorio" << endl; break;
        }
    }

    for (unsigned int i = 1; i <= MAX_N; i++) {
        double tiempos[CANT_REPETICIONES];
        double tiempo_promedio = 0;
        double desv_estandar = 0;
        bool instancias_random = false;

        N = i;

        if (!quiet) {
            cout << "  N = " << setfill(' ') << setw(2) << i << "    " << flush;
        }

        switch (prueba_id) {
            case PRUEBA_MEJOR_CASO:
                coordenadasEnemigos = generarMejorCaso(N);
                break;

            case PRUEBA_CASO_INTERMEDIO:
                coordenadasEnemigos = generarCasoIntermedio(N);
                break;

            case PRUEBA_PEOR_CASO:
                coordenadasEnemigos = generarPeorCaso(N);
                break;

            case PRUEBA_RANDOM:
                instancias_random = true;
                break;
        }
        
        for (int r = -CANT_INST_DESCARTADAS; r < CANT_REPETICIONES; r++) {
            if (!quiet) {
                cout << "\b\b\b" << setfill(' ') << setw(3) << r << flush;
            }

            double tiempo;
            if (instancias_random) {
                coordenadasEnemigos = generarCasoRandom(N);
            }
            start_timer();
            resolverKamehameha();
            tiempo = stop_timer();

            if (r >= 0) {
                tiempos[r] = tiempo;
                tiempo_promedio += tiempos[r];
            }
        }

        tiempo_promedio = tiempo_promedio / CANT_REPETICIONES;

        for (unsigned int r = 0; r < CANT_REPETICIONES; r++) {
            desv_estandar += pow(tiempos[r] - tiempo_promedio, 2);
        }
        desv_estandar = sqrt(desv_estandar / CANT_REPETICIONES);

        archivoSalida << i << " " << tiempo_promedio << " " << desv_estandar << endl;

        if (!quiet) {
            cout << "\b\b\b  ✓" << endl;
        }
    }
}

void correr_pruebas_performance() {
    bool quiet = ! verbose;

    ofstream archivoSalida;
    for (int i = 0; i < CANT_REP_COMPLETAS; i++) {

        archivoSalida.open("../exp/kamehamehaPeor");
        ejecutarPruebas(PRUEBA_PEOR_CASO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/kamehamehaIntermedio");
        ejecutarPruebas(PRUEBA_CASO_INTERMEDIO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/kamehamehaMejor");
        ejecutarPruebas(PRUEBA_MEJOR_CASO, archivoSalida, quiet);
        archivoSalida.close();

        archivoSalida.open("../exp/kamehamehaRandom");
        ejecutarPruebas(PRUEBA_RANDOM, archivoSalida, quiet);
        archivoSalida.close();
    }
}
