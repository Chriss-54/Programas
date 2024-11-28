#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;

int NUM_DISCOS;
std::vector<std::string> movimientos;

void dibujarTorre(int x, int y, int altura) {
    line(x, y, x, y - altura);
}

void dibujarDisco(int x, int y, int ancho, int altura) {
    setfillstyle(SOLID_FILL, COLOR(rand() % 256, rand() % 256, rand() % 256));
    bar(x - ancho / 2, y - altura, x + ancho / 2, y);
}

void dibujarTorres(std::vector<std::vector<int>>& discos, std::vector<int>& alturas) {
    cleardevice();
    
    for (int i = 0; i < 3; i++) {
        dibujarTorre(200 + i * 200, 500, 300);
        for (int j = 0; j < alturas[i]; j++) {
            dibujarDisco(200 + i * 200, 500 - j * 30, discos[i][j] * 20, 25);
        }
    }
    
    delay(500);
}

void moverDisco(int desde, int hasta, std::vector<std::vector<int>>& discos, std::vector<int>& alturas) {
    int disco = discos[desde][alturas[desde] - 1];
    discos[hasta][alturas[hasta]] = disco;
    alturas[hasta]++;
    alturas[desde]--;
    
    std::string movimiento = "Mover disco " + std::to_string(disco) + " de torre " + std::to_string(desde + 1) + " a torre " + std::to_string(hasta + 1);
    movimientos.push_back(movimiento);
    
    outtextxy(10, 10, (char*)movimiento.c_str());
    
    dibujarTorres(discos, alturas);
}

void hanoi(int n, int origen, int auxiliar, int destino, std::vector<std::vector<int>>& discos, std::vector<int>& alturas) {
    if (n == 1) {
        moverDisco(origen, destino, discos, alturas);
    } else {
        hanoi(n - 1, origen, destino, auxiliar, discos, alturas);
        moverDisco(origen, destino, discos, alturas);
        hanoi(n - 1, auxiliar, origen, destino, discos, alturas);
    }
}

void guardarMovimientos() {
    std::ofstream archivo("movimientos_hanoi.txt");
    if (archivo.is_open()) {
        for (const auto& movimiento : movimientos) {
            archivo << movimiento << std::endl;
        }
        archivo.close();
        std::cout << "Movimientos guardados en 'movimientos_hanoi.txt'" << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo para guardar los movimientos." << std::endl;
    }
}

int main() {
    std::cout << "Ingrese el numero de discos: ";
    std::cin >> NUM_DISCOS;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, nullptr);
    
    initwindow(ANCHO_VENTANA, ALTO_VENTANA, "Torres de Hanoi");
    
    std::vector<std::vector<int>> discos(3, std::vector<int>(NUM_DISCOS, 0));
    std::vector<int> alturas(3, 0);

    for (int i = 0; i < NUM_DISCOS; i++) {
        discos[0][i] = NUM_DISCOS - i;
    }
    alturas[0] = NUM_DISCOS;
    
    dibujarTorres(discos, alturas);
    
    getch();
    
    hanoi(NUM_DISCOS, 0, 1, 2, discos, alturas);
    
    getch();
    closegraph();

    guardarMovimientos();

    return 0;
}
