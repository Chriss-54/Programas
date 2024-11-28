#include "conjuntos.h"
#include <graphics.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <regex>

bool esNombre(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isalpha(c) || std::isspace(c);
    });
}

bool esNumero(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool esExpresionMatematica(const std::string& str) {
    std::regex patron("^[0-9+\\-*/()\\s]+$");
    return std::regex_match(str, patron);
}

void ingresarConjuntos(Conjunto& conjunto, TipoConjunto tipo) {
    int n;
    std::string entrada;
    std::cout << "Ingrese la cantidad de elementos del conjunto: ";
    std::cin >> n;
    std::cin.ignore();

    conjunto.tipo = tipo;

    for (int i = 0; i < n; ++i) {
        std::cout << "Ingrese el elemento " << i + 1 << ": ";
        std::getline(std::cin, entrada);

        bool valido = false;
        switch (tipo) {
            case NOMBRES:
                valido = esNombre(entrada);
                break;
            case NUMEROS:
                valido = esNumero(entrada);
                break;
            case EXPRESIONES:
                valido = esExpresionMatematica(entrada);
                break;
        }

        if (valido) {
            conjunto.elementos.insert(entrada);
        } else {
            std::cout << "Entrada no válida. Intente de nuevo.\n";
            --i;
        }
    }
}

void mostrarConjuntos(const Conjunto& conjunto) {
    std::cout << "Elementos: ";
    for (const auto& e : conjunto.elementos) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void operacionesConjuntos(const Conjunto& A, const Conjunto& B) {
    // Implementar operaciones lógicas y de probabilidad aquí
}

void dibujarConjuntosGraficamente(const Conjunto& A, const Conjunto& B) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setcolor(WHITE);    
    circle(200, 200, 100); // Círculo para conjunto A
    circle(300, 200, 100); // Círculo para conjunto B

    outtextxy(150, 100, "Conjunto A");
    outtextxy(350, 100, "Conjunto B");

    // Dibujar elementos de los conjuntos
       int yA = 150, yB = 150;
    for (const auto& elem : A.elementos) {
        outtextxy(120, yA, (char*)elem.c_str());
        yA += 20;
    }

    for (const auto& elem : B.elementos) {
        outtextxy(380, yB, (char*)elem.c_str());
        yB += 20;
    }

    getch();
    closegraph();
}