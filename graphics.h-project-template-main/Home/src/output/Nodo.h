#ifndef NODO_H
#define NODO_H

#include <string>

using namespace std;

template<typename T>
class Nodo {
private:
    T* cedula;
    T* nombre;
    T* apellido;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

public:
    Nodo(const T& cedula, const T& nombre, const T& apellido);
    ~Nodo();

    T getCedula() const;
    T getNombre() const;
    T getApellido() const;
    Nodo* getIzquierdo() const;
    Nodo* getDerecho() const;
    Nodo* getPadre() const;

    void setCedula(const T& cedula);
    void setNombre(const T& nombre);
    void setApellido(const T& apellido);
    void setIzquierdo(Nodo* izquierdo);
    void setDerecho(Nodo* derecho);
    void setPadre(Nodo* padre);
};

#endif // NODO_H
