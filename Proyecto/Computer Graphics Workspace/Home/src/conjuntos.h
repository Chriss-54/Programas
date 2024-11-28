#ifndef CONJUNTOS_H
#define CONJUNTOS_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

enum TipoConjunto { NOMBRES, NUMEROS, EXPRESIONES };

struct Conjunto {
    std::set<std::string> elementos;
    TipoConjunto tipo;
};

void ingresarConjuntos(Conjunto& conjunto, TipoConjunto tipo);
void mostrarConjuntos(const Conjunto& conjunto);
void operacionesConjuntos(const Conjunto& A, const Conjunto& B);
void dibujarConjuntosGraficamente(const Conjunto& A, const Conjunto& B);

#endif