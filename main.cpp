#include <iostream>
#include <string>
#include "Usuario.h"
#include "SistemaAdmin.h"
#include "Menus.h"

using namespace std;

// Devuelve el código de rol para el usuario autenticado
int codigoRol(const string& nombre, const string& password, const SistemaAdmin& sistema) {
    for (int i = 1; i <= sistema.cantidadUsuarios(); ++i) {
        Usuario* u = sistema.buscarUsuario(i);
        if (u && u->getNombre() == nombre && u->getPasswd() == password && u->isAlta()) {
            return u->getRol();
        }
    }
    return 0;
}

int main() {
    string nombre, password;
    int rolCode;
    bool acceso = false;
    int opcion;
    SistemaAdmin sistema;

    // Usuarios base
    sistema.altaAdmin("admin", "Principal", "admin123");
    sistema.altaProfesor("profe", "Ejemplo", "profe123");
    sistema.altaProfesor("Maria", "Gomez", "profe123");
    sistema.altaEstudiante("Juan", "Perez", "e123");
    sistema.altaEstudiante("Ana", "Lopez", "e123");
    sistema.altaEstudiante("Luis", "Martinez", "e123");
    sistema.altaEstudiante("Sofia", "Garcia", "e123");

    do {
        cout << "===== BIENVENIDO AL SISTEMA =====" << endl;
        cout << "       1. Estudiante " << endl;
        cout << "       2. Profesor(a) " << endl;
        cout << "       3. Administrador " << endl;
        cout << "Por favor, selecciona tu tipo de usuario:  ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ingrese su nombre: ";
        getline(cin, nombre);

        cout << "Ingrese su password: ";
        getline(cin, password);

        rolCode = codigoRol(nombre, password, sistema);

        switch (rolCode) {
            case 1:
                cout << "Bienvenido, administrador " << nombre << "!\n";
                menuAdministrador(sistema);
                acceso = true;
                break;
            case 2: {
                cout << "Bienvenido, profesor " << nombre << "!\n";
                // Busca el usuario para pasar referencia al menú
                for (int i = 1; i <= sistema.cantidadUsuarios(); ++i) {
                    Usuario* u = sistema.buscarUsuario(i);
                    if (u && u->getNombre() == nombre && u->getRol() == 2 && u->isAlta()) {
                        menuProfesor();
                        acceso = true;
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "Bienvenido, estudiante " << nombre << "!\n";
                // Busca el usuario para pasar referencia al menú
                for (int i = 1; i <= sistema.cantidadUsuarios(); ++i) {
                    Usuario* u = sistema.buscarUsuario(i);
                    if (u && u->getNombre() == nombre && u->getRol() == 3 && u->isAlta()) {
                        menuEstudiante(*(Estudiante*)u);
                        acceso = true;
                        break;
                    }
                }
                break;
            }
            default:
                cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n" << endl;
                break;
        }
    } while (!acceso);

    return 0;
}