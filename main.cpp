#include <iostream>
#include <string>
using namespace std;
int main(){
    float estatura;
    string nombre, lugarFavorito, colorFavorito;
    char inicialApellido, simboloRepresentativo;
    int numeroSuerte, añoNacimiento;
    short hermanos;
    double numeroMagico;

    cout<<"=== GENERADOR DE DNI CURIOSO ==="<<endl;
    cout<<"Ingrese su nombre: ";
    getline(cin,nombre);

    cout<<"Ingrese la inicial de su apellido: ";
    cin>>inicialApellido;
    cin.ignore();

    cout<<"Ingrese su estatura (m): ";
    cin>>estatura;

    cout<<"Ingrese su numero magico favorito: ";
    cin>>numeroMagico;

    cout<<"Ingrese su lugar favorito: ";
    getline(cin,lugarFavorito);

    cout<<"Ingrese numero de hermanos:";
    cin>>hermanos;

    cout<<"Ingrese su año de nacimiento:";
    cin>>añoNacimiento;

    cout<<"Ingrese su numero de la suerte: ";
    cin>>numeroSuerte;
    cin.ignore();

    cout<<"Ingrese su color favorito:";
    getline(cin, colorFavorito);

    int edad = 2024 - añoNacimiento;
    long codigoPersonal = static_cast<long>(numeroSuerte * numeroMagico);

    cout<<"\n=== DOCUMENTO DE IDENTIDAD CURIOSO ==="<<endl;
    cout<<"Nombre Completo:" <<nombre<<""<<inicialApellido<<"."<<endl;
    cout<<"Simbolo Personal:"<<simboloRepresentativo<<endl;
    cout<<"edad:"<<edad<<"años"<<endl;
    cout<<"Codigo personal:" <<simboloRepresentativo<<endl;
    cout<<"Lugar favorito: "<<lugarFavorito<<endl;
    cout<<"Color Favorito: "<<colorFavorito<<endl;
    cout<<"Estatura: "<<estatura<<"m"<<endl;
    cout<<"Numero Hermanos: "<<hermanos<<endl;

    return 0;
}
