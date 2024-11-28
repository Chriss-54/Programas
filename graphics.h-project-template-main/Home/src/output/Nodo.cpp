#include "Nodo.h"

template<typename T>
Nodo<T>::Nodo(const T& cedula, const T& nombre, const T& apellido)
    : cedula(new T(cedula)), nombre(new T(nombre)), apellido(new T(apellido)),
      izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}

template<typename T>
Nodo<T>::~Nodo() {
    delete cedula;
    delete nombre;
    delete apellido;
}

template<typename T>
T Nodo<T>::getCedula() const {
    return *cedula;
}

template<typename T>
T Nodo<T>::getNombre() const {
    return *nombre;
}

template<typename T>
T Nodo<T>::getApellido() const {
    return *apellido;
}

template<typename T>
Nodo<T>* Nodo<T>::getIzquierdo() const {
    return izquierdo;
}

template<typename T>
Nodo<T>* Nodo<T>::getDerecho() const {
    return derecho;
}

template<typename T>
Nodo<T>* Nodo<T>::getPadre() const {
    return padre;
}

template<typename T>
void Nodo<T>::setCedula(const T& cedula) {
    *(this->cedula) = cedula;
}

template<typename T>
void Nodo<T>::setNombre(const T& nombre) {
    *(this->nombre) = nombre;
}

template<typename T>
void Nodo<T>::setApellido(const T& apellido) {
    *(this->apellido) = apellido;
}

template<typename T>
void Nodo<T>::setIzquierdo(Nodo* izquierdo) {
    this->izquierdo = izquierdo;
}

template<typename T>
void Nodo<T>::setDerecho(Nodo* derecho) {
    this->derecho = derecho;
}

template<typename T>
void Nodo<T>::setPadre(Nodo* padre) {
    this->padre = padre;
}
