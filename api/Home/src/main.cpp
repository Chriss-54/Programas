#include <graphics.h>
#include <iostream>
#include <string>
#include "api_handler.h"
#include "dictionary.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inicializar gráficos

    outtextxy(10, 10, (char*)"Ingrese una palabra para traducir:");  // Mostrar texto en la pantalla gráfica

    char word[100];
    std::cin >> word;

    std::string translatedWord = translateWord(word);

    if (!translatedWord.empty()) {
        outtextxy(10, 50, (char*)translatedWord.c_str());  // Mostrar traducción en la pantalla gráfica
    } else {
        outtextxy(10, 50, (char*)"Palabra no encontrada");  // Mostrar mensaje de error
    }

    getch();
    closegraph();

    return 0;
}


