#include "conjuntos.h"

int main() {
    Conjunto conjuntoA, conjuntoB;
    int tipoSeleccionado;

    std::cout << "Seleccione el tipo de datos para el conjunto A:\n";
    std::cout << "1. Nombres\n2. Números\n3. Expresiones matemáticas\n";
    std::cin >> tipoSeleccionado;
    ingresarConjuntos(conjuntoA, static_cast<TipoConjunto>(tipoSeleccionado - 1));

    std::cout << "Seleccione el tipo de datos para el conjunto B:\n";
    std::cin >> tipoSeleccionado;
    ingresarConjuntos(conjuntoB, static_cast<TipoConjunto>(tipoSeleccionado - 1));

    mostrarConjuntos(conjuntoA);
    mostrarConjuntos(conjuntoB);

    operacionesConjuntos(conjuntoA, conjuntoB);
    dibujarConjuntosGraficamente(conjuntoA, conjuntoB);

    return 0;
}
