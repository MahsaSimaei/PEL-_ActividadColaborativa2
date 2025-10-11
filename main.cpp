#include <iostream>
#include <string>
using namespace std;


// Simulación de login y menú por rol usando switch
int main() {
    string nombre, password;
    int rolCode;
    bool acceso = false;

    do {
        cout << "===== BIENVENIDO AL SISTEMA =====" << endl;
        cout << "Ingrese su nombre de usuario: ";
        getline(cin, nombre);

        cout << "Ingrese su password: ";
        getline(cin, password);

        rolCode = codigoRol(nombre, password);

        switch (rolCode) {
            case 1:
                menuAdministrador();
                acceso = true;
                break;
            case 2:
                menuProfesor();
                acceso = true;
                break;
            case 3:
                menuEstudiante();
                acceso = true;
                break;
            default:
                cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n" << endl;
                break;
        }
    } while (!acceso);

    // Aquí iría la lógica de selección de opciones y bucles (no solicitada)
    return 0;
}
