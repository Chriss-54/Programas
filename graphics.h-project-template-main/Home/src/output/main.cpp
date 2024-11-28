#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ArbolSplay.cpp"
#include "validar.cpp"

using namespace std;

void gotoxy(int x, int y);
void printMenu(const char* menu[], int size, int currentSelection);
void submenuFamilia(ArbolSplay<string>* arbol);

int main() {
    system("cls");

    ArbolSplay<string>* arbol = new ArbolSplay<string>();

    arbol->cargarDesdeArchivo();

    const char* menu[] = {
        "Ingresar dato",
        "Buscar dato",
        "Eliminar dato",
        "Mostrar datos",
        "Graficar arbol (Cedula)",
        "Mostrar arbol (Nombre)",
        "Mostrar arbol (Apellido)",
        "Menu familia",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU DE ARBOL SPLAY:." << endl;
        printMenu(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                switch (currentSelection) {
                    case 0: {
                        string cedula = ingresarCedula<string>("Ingrese la cedula");

                        if (!esNumeroCedulaValido<string>(cedula)) {
                            cout << "Cedula no valida. Debe contener exactamente 10 numeros." << endl;
                            break;
                        }

                        long int cedulaNum;
                        try {
                            cedulaNum = stol(cedula);
                        } catch (exception& e) {
                            cout << "Error de conversion de cedula." << endl;
                            break;
                        }

                        if (validarCedula<long int>(cedulaNum)) {
                            if (!cedulaRepetida<string>(arbol->getRaiz(), cedula)) {
                                string nombre = ingresarLetras<string>("Ingrese el nombre", false);
                                string apellido = ingresarLetras<string>("Ingrese el apellido", false);
                                nombre = convertirMayusculas<string>(nombre);
                                apellido = convertirMayusculas<string>(apellido);
                                arbol->insertar(cedula, nombre, apellido);
                                arbol->guardarEnArchivo(); 
                                cout << "Datos ingresados y guardados correctamente." << endl;
                            } else {
                                cout << "Cedula ya existe en el sistema." << endl;
                            }
                        } else {
                            cout << "Cedula no valida." << endl;
                        }
                        break;
                    }
                    case 1: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            string cedula = ingresarCedula<string>("Ingrese la cedula del dato a buscar");

                            if (!esNumeroCedulaValido<string>(cedula)) {
                                cout << "Cedula no valida. Debe contener exactamente 10 numeros." << endl;
                                break;
                            }

                            long int cedulaNum;
                            try {
                                cedulaNum = stol(cedula);
                            } catch (exception& e) {
                                cout << "Error de conversion de cedula." << endl;
                                break;
                            }

                            if (validarCedula<long int>(cedulaNum)) {
                                arbol->graficarBusqueda(cedula, Campo::CEDULA);
                                if (arbol->buscar(cedula)) {
                                    cout << "Dato encontrado." << endl;
                                } else {
                                    cout << "Dato no encontrado." << endl;
                                }
                            } else {
                                cout << "Cedula no valida." << endl;
                            }
                        }
                        break;
                    }
                    case 2: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            string cedula = ingresarCedula<string>("Ingrese la cedula del dato a eliminar");

                            if (!esNumeroCedulaValido<string>(cedula)) {
                                cout << "Cedula no valida. Debe contener exactamente 10 numeros." << endl;
                                break;
                            }

                            long int cedulaNum;
                            try {
                                cedulaNum = stol(cedula);
                            } catch (exception& e) {
                                cout << "Error de conversion de cedula." << endl;
                                break;
                            }

                            if (validarCedula<long int>(cedulaNum)) {
                                arbol->graficarEliminacion(cedula, Campo::CEDULA);
                                arbol->guardarEnArchivo();
                            } else {
                                cout << "Cedula no valida." << endl;
                            }
                        }
                        break;
                    }
                    case 3: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            arbol->mostrarDatos();
                        }
                        break;
                    }
                    case 4: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            arbol->graficarArbol(Campo::CEDULA);
                        }
                        break;
                    }
                    case 5: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            arbol->graficarArbol(Campo::NOMBRE);
                        }
                        break;
                    }
                    case 6: {
                        if (arbol->getRaiz() == nullptr) {
                            cout << "El arbol esta vacio." << endl;
                        } else {
                            arbol->graficarArbol(Campo::APELLIDO);
                        }
                        break;
                    }
                    case 7:
                        submenuFamilia(arbol);
                        break;
                    case 8:
                        cout << "Saliendo del programa..." << endl;
                        delete arbol; 
                        return 0;
                    default:
                        cout << "Opcion invalida. Intentalo nuevamente." << endl;
                        break;
                }
                if (currentSelection != 8) {
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);

    delete arbol; 
    return 0;
}

void submenuFamilia(ArbolSplay<string>* arbol) {
    const char* submenu[] = {
        "Mostrar padre",
        "Mostrar hijos",
        "Mostrar abuelo",
        "Mostrar tio",
        "Mostrar nietos",
        "Mostrar primos",
        "Regresar al menu principal"
    };
    int size = sizeof(submenu) / sizeof(submenu[0]);
    int currentSelection = 0;
    int key;
    string cedula;

    do {
        system("cls");
        cout << "\t\t.:MENU DE FAMILIA:." << endl;
        printMenu(submenu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                if (currentSelection == 6) {
                    return; 
                }

                string cedula = ingresarCedula<string>("Ingrese la cedula para buscar");

                if (!esNumeroCedulaValido<string>(cedula)) {
                    cout << "Cedula no valida. Debe contener exactamente 10 numeros." << endl;
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                    break;
                }

                long int cedulaNum;
                try {
                    cedulaNum = stol(cedula);
                } catch (exception& e) {
                    cout << "Error de conversion de cedula." << endl;
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                    break;
                }

                if (!validarCedula<long int>(cedulaNum)) {
                    cout << "Cedula no valida." << endl;
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                    break;
                }

                if (!arbol->buscar(cedula)) {
                    cout << "La cedula ingresada no existe en el sistema." << endl;
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                    break;
                }

                switch (currentSelection) {
                    case 0:
                        arbol->mostrarPadre(cedula);
                        break;
                    case 1:
                        arbol->mostrarHijos(cedula);
                        break;
                    case 2:
                        arbol->mostrarAbuelo(cedula);
                        break;
                    case 3:
                        arbol->mostrarTio(cedula);
                        break;
                    case 4:
                        arbol->mostrarNietos(cedula);
                        break;
                    case 5:
                        arbol->mostrarPrimos(cedula);
                        break;
                    default:
                        cout << "Opcion invalida. Intentalo nuevamente." << endl;
                        break;
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
                break;
        }
    } while (true);
}

void gotoxy(int x, int y) { 
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenu(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; ++i) {
        if (i == currentSelection) {
            cout << "> " << menu[i] << " <" << endl;
        } else {
            cout << "  " << menu[i] << endl;
        }
    }
}
