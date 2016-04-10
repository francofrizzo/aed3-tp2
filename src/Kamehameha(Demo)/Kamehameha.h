#ifndef KAMEHAMEHA_H
#define KAMEHAMEHA_H

#include <vector>        // vector
#include <algorithm>
#include <cmath>

using std::ostream;
using std::vector;
// Representa un punto en el plano bidimensional
class XY {
 public:
    XY ();
    XY (int, int);

    int x;
    int y;

    bool operator==(const XY&) const;
    bool operator!=(const XY&) const;
};

// Representa una recta en el plano bidimensional
class Recta {
 public:
    Recta(XY, XY);
    bool pasaPor(const XY) const;
    bool operator==(const Recta&) const;

    ostream& imprimir(ostream& os) const;

    XY puntoAleatorio() const;

 private:
    XY a;
    XY b;
};

ostream& operator<<(ostream&, const Recta&);

extern unsigned int N;
extern vector<XY> coordenadasEnemigos;
vector<vector<unsigned int>> resolverKamehameha();

#endif