#ifndef ARBOLSPLAY_H
#define ARBOLSPLAY_H

#include "Nodo.cpp"
#include <fstream>
#include <sstream>

using namespace std;

enum class Campo { CEDULA, NOMBRE, APELLIDO };

template<typename T>
class ArbolSplay {
private:
    Nodo<T>* raiz;

    void splay(Nodo<T>* nodo);
    void rotarIzquierda(Nodo<T>* nodo);
    void rotarDerecha(Nodo<T>* nodo);
    Nodo<T>* buscarNodo(Nodo<T>* nodo, const T& cedula) const;
    Nodo<T>* minimo(Nodo<T>* nodo) const;
    Nodo<T>* maximo(Nodo<T>* nodo) const;
    void dibujarNodo(Nodo<T>* nodo, int x, int y, int offset, Campo campo) const;
    void dibujarNodo(Nodo<T>* nodo, int x, int y, int offset, const T& buscado, Campo campo) const;

public:
    ArbolSplay();
    ~ArbolSplay();

    void insertar(const T& cedula, const T& nombre, const T& apellido);
    void eliminar(const T& cedula);
    bool buscar(const T& cedula) const;
    void mostrarDatos() const;
    void graficarArbol(Campo campo) const;
    void graficarBusqueda(const T& cedula, Campo campo) const;
    void graficarEliminacion(const T& cedula, Campo campo);

    void guardarEnArchivo() const;
    void cargarDesdeArchivo();

    void mostrarPadre(const T& cedula) const;
    void mostrarHijos(const T& cedula) const;
    void mostrarAbuelo(const T& cedula) const;
    void mostrarTio(const T& cedula) const;
    void mostrarNietos(const T& cedula) const;
    void mostrarPrimos(const T& cedula) const;

    Nodo<T>* getRaiz() const;
};

#endif // ARBOLSPLAY_H
