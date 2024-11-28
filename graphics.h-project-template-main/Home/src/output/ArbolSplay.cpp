#include "ArbolSplay.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <cmath>
#include <queue>

using namespace std;

template<typename T>
ArbolSplay<T>::ArbolSplay() : raiz(nullptr) {}

template<typename T>
ArbolSplay<T>::~ArbolSplay() {
    queue<Nodo<T>*> nodes;
    nodes.push(raiz);
    while (!nodes.empty()) {
        Nodo<T>* current = nodes.front();
        nodes.pop();
        if (current != nullptr) {
            nodes.push(current->getIzquierdo());
            nodes.push(current->getDerecho());
            delete current;
        }
    }
}

template<typename T>
Nodo<T>* ArbolSplay<T>::getRaiz() const {
    return raiz;
}

template<typename T>
bool ArbolSplay<T>::buscar(const T& cedula) const {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return false;
    }

    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo != nullptr) {
        const_cast<ArbolSplay*>(this)->splay(nodo); // Make it the root
        return true;
    }
    return false;
}

template<typename T>
Nodo<T>* ArbolSplay<T>::buscarNodo(Nodo<T>* nodo, const T& cedula) const {
    if (nodo == nullptr || cedula == nodo->getCedula()) {
        return nodo;
    }

    if (cedula < nodo->getCedula()) {
        return buscarNodo(nodo->getIzquierdo(), cedula);
    }
    return buscarNodo(nodo->getDerecho(), cedula);
}

template<typename T>
Nodo<T>* ArbolSplay<T>::minimo(Nodo<T>* nodo) const {
    while (nodo->getIzquierdo() != nullptr) {
        nodo = nodo->getIzquierdo();
    }
    return nodo;
}

template<typename T>
Nodo<T>* ArbolSplay<T>::maximo(Nodo<T>* nodo) const {
    while (nodo->getDerecho() != nullptr) {
        nodo = nodo->getDerecho();
    }
    return nodo;
}

template<typename T>
void ArbolSplay<T>::insertar(const T& cedula, const T& nombre, const T& apellido) {
    Nodo<T>* nodo = new Nodo<T>(cedula, nombre, apellido);

    Nodo<T>* y = nullptr;
    Nodo<T>* x = this->raiz;

    while (x != nullptr) {
        y = x;
        if (nodo->getCedula() < x->getCedula()) {
            x = x->getIzquierdo();
        } else {
            x = x->getDerecho();
        }
    }

    nodo->setPadre(y);
    if (y == nullptr) {
        raiz = nodo;
    } else if (nodo->getCedula() < y->getCedula()) {
        y->setIzquierdo(nodo);
    } else {
        y->setDerecho(nodo);
    }

    splay(nodo);
}

template<typename T>
void ArbolSplay<T>::eliminar(const T& cedula) {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == nullptr) {
        cout << "Dato no encontrado en el arbol." << endl;
        return;
    }

    splay(nodo);

    if (nodo->getIzquierdo() == nullptr) {
        raiz = nodo->getDerecho();
    } else {
        Nodo<T>* maxIzquierdo = maximo(nodo->getIzquierdo());
        splay(maxIzquierdo);
        maxIzquierdo->setDerecho(nodo->getDerecho());
        raiz = maxIzquierdo;
    }

    delete nodo;
}

template<typename T>
void ArbolSplay<T>::splay(Nodo<T>* nodo) {
    while (nodo->getPadre() != nullptr) {
        if (nodo->getPadre()->getPadre() == nullptr) {
            if (nodo == nodo->getPadre()->getIzquierdo()) {
                rotarDerecha(nodo->getPadre());
            } else {
                rotarIzquierda(nodo->getPadre());
            }
        } else if (nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == nodo->getPadre()->getPadre()->getIzquierdo()) {
            rotarDerecha(nodo->getPadre()->getPadre());
            rotarDerecha(nodo->getPadre());
        } else if (nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == nodo->getPadre()->getPadre()->getDerecho()) {
            rotarIzquierda(nodo->getPadre()->getPadre());
            rotarIzquierda(nodo->getPadre());
        } else if (nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == nodo->getPadre()->getPadre()->getDerecho()) {
            rotarDerecha(nodo->getPadre());
            rotarIzquierda(nodo->getPadre());
        } else {
            rotarIzquierda(nodo->getPadre());
            rotarDerecha(nodo->getPadre());
        }
    }
}

template<typename T>
void ArbolSplay<T>::rotarIzquierda(Nodo<T>* nodo) {
    Nodo<T>* derecho = nodo->getDerecho();
    nodo->setDerecho(derecho->getIzquierdo());
    if (derecho->getIzquierdo() != nullptr) {
        derecho->getIzquierdo()->setPadre(nodo);
    }
    derecho->setPadre(nodo->getPadre());
    if (nodo->getPadre() == nullptr) {
        raiz = derecho;
    } else if (nodo == nodo->getPadre()->getIzquierdo()) {
        nodo->getPadre()->setIzquierdo(derecho);
    } else {
        nodo->getPadre()->setDerecho(derecho);
    }
    derecho->setIzquierdo(nodo);
    nodo->setPadre(derecho);
}

template<typename T>
void ArbolSplay<T>::rotarDerecha(Nodo<T>* nodo) {
    Nodo<T>* izquierdo = nodo->getIzquierdo();
    nodo->setIzquierdo(izquierdo->getDerecho());
    if (izquierdo->getDerecho() != nullptr) {
        izquierdo->getDerecho()->setPadre(nodo);
    }
    izquierdo->setPadre(nodo->getPadre());
    if (nodo->getPadre() == nullptr) {
        raiz = izquierdo;
    } else if (nodo == nodo->getPadre()->getDerecho()) {
        nodo->getPadre()->setDerecho(izquierdo);
    } else {
        nodo->getPadre()->setIzquierdo(izquierdo);
    }
    izquierdo->setDerecho(nodo);
    nodo->setPadre(izquierdo);
}

template<typename T>
void ArbolSplay<T>::mostrarDatos() const {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    cout << "Cedula\tNombre\tApellido" << endl;
    cout << "-------------------------" << endl;

    auto preOrdenHelper = [](Nodo<T>* nodo, auto& ref) -> void {
        if (nodo != nullptr) {
            cout << nodo->getCedula() << "\t" << nodo->getNombre() << "\t" << nodo->getApellido() << endl;
            ref(nodo->getIzquierdo(), ref);
            ref(nodo->getDerecho(), ref);
        }
    };

    preOrdenHelper(raiz, preOrdenHelper);
    cout << endl;
}

template<typename T>
void ArbolSplay<T>::graficarArbol(Campo campo) const {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    dibujarNodo(raiz, getmaxx() / 2, 50, getmaxx() / 4, campo);
    getch();
    closegraph();
}

template<typename T>
void ArbolSplay<T>::graficarBusqueda(const T& cedula, Campo campo) const {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    
    int width = getmaxx();
    int height = getmaxy();
    
    int msgX = 10;
    int msgY = 10;
    
    Nodo<T>* nodo = raiz;
    int x = width / 2, y = 50, offset = width / 4;
    bool found = false;
    
    while (nodo != nullptr) {
        cleardevice();
        
        if (nodo->getCedula() == cedula) {
            setcolor(GREEN);
            outtextxy(msgX, msgY, const_cast<char*>("Dato encontrado"));
            found = true;
        } else {
            setcolor(BLACK);
            outtextxy(msgX, msgY, const_cast<char*>("Buscando..."));
        }
        
        dibujarNodo(raiz, width / 2, 80, width / 4, nodo->getCedula(), campo);
        
        if (found) break;

        if (cedula < nodo->getCedula()) {
            nodo = nodo->getIzquierdo();
            x -= offset / 2;
        } else {
            nodo = nodo->getDerecho();
            x += offset / 2;
        }
        y += 60;
        delay(2000); 
    }
    
    if (!found) {
        cleardevice();
        setcolor(RED);
        outtextxy(msgX, msgY, const_cast<char*>("Dato no encontrado"));
        dibujarNodo(raiz, width / 2, 80, width / 4, "", campo);
    }

    getch();
    closegraph();
}

template<typename T>
void ArbolSplay<T>::dibujarNodo(Nodo<T>* nodo, int x, int y, int offset, Campo campo) const {
    if (nodo == nullptr || nodo->getCedula() == "") return;

    setfillstyle(SOLID_FILL, BLACK);
    setcolor(BLACK);
    fillellipse(x, y, 20, 20);

    setcolor(BLACK);
    string texto;
    switch (campo) {
        case Campo::CEDULA:
            texto = nodo->getCedula();
            break;
        case Campo::NOMBRE:
            texto = nodo->getNombre();
            break;
        case Campo::APELLIDO:
            texto = nodo->getApellido();
            break;
    }
    outtextxy(x - 10, y - 10, const_cast<char*>(texto.c_str()));

    if (nodo->getIzquierdo() != nullptr) {
        line(x, y, x - offset, y + 60);
        dibujarNodo(nodo->getIzquierdo(), x - offset, y + 60, offset / 2, campo);
    }
    if (nodo->getDerecho() != nullptr) {
        line(x, y, x + offset, y + 60);
        dibujarNodo(nodo->getDerecho(), x + offset, y + 60, offset / 2, campo);
    }
}

template<typename T>
void ArbolSplay<T>::dibujarNodo(Nodo<T>* nodo, int x, int y, int offset, const T& buscado, Campo campo) const {
    if (nodo == nullptr) return;

    int color = BLACK;
    if (nodo->getCedula() == buscado) {
        setfillstyle(SOLID_FILL, GREEN);
    } else {
        setfillstyle(SOLID_FILL, color);
    }
    setcolor(color);
    fillellipse(x, y, 20, 20);

    setcolor(BLACK);
    string texto;
    switch (campo) {
        case Campo::CEDULA:
            texto = nodo->getCedula();
            break;
        case Campo::NOMBRE:
            texto = nodo->getNombre();
            break;
        case Campo::APELLIDO:
            texto = nodo->getApellido();
            break;
    }
    outtextxy(x - 10, y - 10, const_cast<char*>(texto.c_str()));

    if (nodo->getIzquierdo() != nullptr) {
        line(x, y, x - offset, y + 60);
        dibujarNodo(nodo->getIzquierdo(), x - offset, y + 60, offset / 2, buscado, campo);
    }
    if (nodo->getDerecho() != nullptr) {
        line(x, y, x + offset, y + 60);
        dibujarNodo(nodo->getDerecho(), x + offset, y + 60, offset / 2, buscado, campo);
    }
}

template<typename T>
void ArbolSplay<T>::graficarEliminacion(const T& cedula, Campo campo) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    
    int width = getmaxx();
    int height = getmaxy();
    
    int msgX = 10;
    int msgY = 10;
    
    Nodo<T>* nodo = raiz;
    int x = width / 2, y = 50, offset = width / 4;
    bool found = false;
    
    while (nodo != nullptr) {
        cleardevice();
        
        if (nodo->getCedula() == cedula) {
            setcolor(RED);
            outtextxy(msgX, msgY, const_cast<char*>("Nodo encontrado. Eliminando..."));
            found = true;
        } else {
            setcolor(BLACK);
            outtextxy(msgX, msgY, const_cast<char*>("Buscando nodo para eliminar..."));
        }
        
        dibujarNodo(raiz, width / 2, 80, width / 4, nodo->getCedula(), campo);
        
        if (found) break;

        if (cedula < nodo->getCedula()) {
            nodo = nodo->getIzquierdo();
            x -= offset / 2;
        } else {
            nodo = nodo->getDerecho();
            x += offset / 2;
        }
        y += 60;
        delay(2000); 
    }
    
    if (found) {
        eliminar(cedula);
        delay(2000); 
        cleardevice();
        setcolor(GREEN);
        outtextxy(msgX, msgY, const_cast<char*>("Nodo eliminado. Actualizando arbol..."));
        dibujarNodo(raiz, width / 2, 80, width / 4, "", campo);
    } else {
        cleardevice();
        setcolor(RED);
        outtextxy(msgX, msgY, const_cast<char*>("Nodo no encontrado para eliminar"));
        dibujarNodo(raiz, width / 2, 80, width / 4, "", campo);
    }

    getch();
    closegraph();
}

template<typename T>
void ArbolSplay<T>::guardarEnArchivo() const {
    string rutaArchivo = "usuarios.txt";
    ofstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir: " << rutaArchivo << endl;
        return;
    }

    auto guardarNodoEnArchivo = [&archivo, this](Nodo<T>* nodo, auto& ref) -> void {
        if (nodo == nullptr) return;
        archivo << nodo->getCedula() << "|" << nodo->getNombre() << "|" << nodo->getApellido() << endl;
        ref(nodo->getIzquierdo(), ref);
        ref(nodo->getDerecho(), ref);
    };

    guardarNodoEnArchivo(raiz, guardarNodoEnArchivo);

    archivo.close();
    cout << "Datos guardados correctamente en " << rutaArchivo << endl;
}

template<typename T>
void ArbolSplay<T>::cargarDesdeArchivo() {
    string rutaArchivo = "usuarios.txt";
    ifstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para leer: " << rutaArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string numCedula, primerNombre, apellido;

        if (!getline(iss, numCedula, '|')) continue;
        if (!getline(iss, primerNombre, '|')) continue;
        if (!getline(iss, apellido, '|')) continue;

        insertar(numCedula, primerNombre, apellido);
    }

    archivo.close();
    cout << "Datos cargados correctamente desde " << rutaArchivo << endl;
}

template<typename T>
void ArbolSplay<T>::mostrarPadre(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == nullptr) {
        cout << "No se encontro el nodo con la cedula ingresada." << endl;
    } else if (nodo == raiz) {
        cout << "El nodo raiz no puede tener padre." << endl;
    } else if (nodo->getPadre() == nullptr) {
        cout << "No se encontro el padre para la cedula ingresada." << endl;
    } else {
        Nodo<T>* padre = nodo->getPadre();
        cout << "Padre: " << padre->getCedula() << " - " << padre->getNombre() << " " << padre->getApellido() << endl;
    }
}

template<typename T>
void ArbolSplay<T>::mostrarHijos(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == nullptr) {
        cout << "No se encontraron hijos para la cedula ingresada." << endl;
    } else if (nodo->getIzquierdo() == nullptr && nodo->getDerecho() == nullptr) {
        cout << "El nodo hoja no tiene hijos." << endl;
    } else {
        if (nodo->getIzquierdo() != nullptr) {
            cout << "Hijo izquierdo: " << nodo->getIzquierdo()->getCedula() << " - " << nodo->getIzquierdo()->getNombre() << " " << nodo->getIzquierdo()->getApellido() << endl;
        }
        if (nodo->getDerecho() != nullptr) {
            cout << "Hijo derecho: " << nodo->getDerecho()->getCedula() << " - " << nodo->getDerecho()->getNombre() << " " << nodo->getDerecho()->getApellido() << endl;
        }
    }
}

template<typename T>
void ArbolSplay<T>::mostrarAbuelo(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == raiz) {
        cout << "El nodo raiz no puede tener abuelos." << endl;
    } else if (nodo == nullptr || nodo->getPadre() == nullptr || nodo->getPadre()->getPadre() == nullptr) {
        cout << "No se encontro el abuelo para la cedula ingresada." << endl;
    } else {
        Nodo<T>* abuelo = nodo->getPadre()->getPadre();
        cout << "Abuelo: " << abuelo->getCedula() << " - " << abuelo->getNombre() << " " << abuelo->getApellido() << endl;
    }
}

template<typename T>
void ArbolSplay<T>::mostrarTio(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == raiz) {
        cout << "El nodo raiz no puede tener tios." << endl;
        return;
    }
    if (nodo == nullptr || nodo->getPadre() == nullptr || nodo->getPadre()->getPadre() == nullptr) {
        cout << "No se encontro el tio para la cedula ingresada." << endl;
        return;
    }

    Nodo<T>* abuelo = nodo->getPadre()->getPadre();
    bool tieneTio = false;
    if (abuelo->getIzquierdo() != nullptr && abuelo->getIzquierdo() != nodo->getPadre()) {
        Nodo<T>* tio = abuelo->getIzquierdo();
        cout << "Tio (lado izquierdo): " << tio->getCedula() << " - " << tio->getNombre() << " " << tio->getApellido() << endl;
        tieneTio = true;
    }
    if (abuelo->getDerecho() != nullptr && abuelo->getDerecho() != nodo->getPadre()) {
        Nodo<T>* tio = abuelo->getDerecho();
        cout << "Tio (lado derecho): " << tio->getCedula() << " - " << tio->getNombre() << " " << tio->getApellido() << endl;
        tieneTio = true;
    }
    if (!tieneTio) {
        cout << "No se encontraron tios para la cedula ingresada." << endl;
    }
}

template<typename T>
void ArbolSplay<T>::mostrarNietos(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == nullptr) {
        cout << "No se encontraron nietos para la cedula ingresada." << endl;
        return;
    } else if (nodo->getIzquierdo() == nullptr && nodo->getDerecho() == nullptr) {
        cout << "El nodo hoja no tiene nietos." << endl;
    }
    auto mostrarHijosDe = [this](Nodo<T>* n) {
        if (n != nullptr) {
            if (n->getIzquierdo() != nullptr) {
                cout << "Nieto: " << n->getIzquierdo()->getCedula() << " - " << n->getIzquierdo()->getNombre() << " " << n->getIzquierdo()->getApellido() << endl;
            }
            if (n->getDerecho() != nullptr) {
                cout << "Nieto: " << n->getDerecho()->getCedula() << " - " << n->getDerecho()->getNombre() << " " << n->getDerecho()->getApellido() << endl;
            }
        }
    };
    mostrarHijosDe(nodo->getIzquierdo());
    mostrarHijosDe(nodo->getDerecho());
}

template<typename T>
void ArbolSplay<T>::mostrarPrimos(const T& cedula) const {
    Nodo<T>* nodo = buscarNodo(raiz, cedula);
    if (nodo == raiz) {
        cout << "El nodo raiz no puede tener primos." << endl;
        return;
    }
    if (nodo == nullptr || nodo->getPadre() == nullptr || nodo->getPadre()->getPadre() == nullptr) {
        cout << "No se encontraron primos para la cedula ingresada." << endl;
        return;
    }

    Nodo<T>* abuelo = nodo->getPadre()->getPadre();
    bool tienePrimos = false;
    if (abuelo->getIzquierdo() != nullptr && abuelo->getIzquierdo() != nodo->getPadre()) {
        Nodo<T>* tio = abuelo->getIzquierdo();
        if (tio->getIzquierdo() != nullptr) {
            cout << "Primo: " << tio->getIzquierdo()->getCedula() << " - " << tio->getIzquierdo()->getNombre() << " " << tio->getIzquierdo()->getApellido() << endl;
            tienePrimos = true;
        }
        if (tio->getDerecho() != nullptr) {
            cout << "Primo: " << tio->getDerecho()->getCedula() << " - " << tio->getDerecho()->getNombre() << " " << tio->getDerecho()->getApellido() << endl;
            tienePrimos = true;
        }
    }
    if (abuelo->getDerecho() != nullptr && abuelo->getDerecho() != nodo->getPadre()) {
        Nodo<T>* tio = abuelo->getDerecho();
        if (tio->getIzquierdo() != nullptr) {
            cout << "Primo: " << tio->getIzquierdo()->getCedula() << " - " << tio->getIzquierdo()->getNombre() << " " << tio->getIzquierdo()->getApellido() << endl;
            tienePrimos = true;
        }
        if (tio->getDerecho() != nullptr) {
            cout << "Primo: " << tio->getDerecho()->getCedula() << " - " << tio->getDerecho()->getNombre() << " " << tio->getDerecho()->getApellido() << endl;
            tienePrimos = true;
        }
    }
    if (!tienePrimos) {
        cout << "No se encontraron primos para la cedula ingresada." << endl;
    }
}

template class ArbolSplay<string>;
