#ifndef VALIDAR_H
#define VALIDAR_H

using namespace std;

#include <string>

template<typename T>
bool validarCedula(T cedula);

template<typename T>
bool esNumeroCedulaValido(const string &numCedula);

template<typename T>
string ingresarCedula(const string &msj);

template<typename T>
bool cedulaRepetida(Nodo<T>* raiz, const string &numCedula);

template<typename T>
string ingresarLetras(const string &msj, bool opcional);

template<typename T>
string convertirMayusculas(string str);


#endif // VALIDAR_H