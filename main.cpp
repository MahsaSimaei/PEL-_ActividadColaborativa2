#include <iostream>
#include <string>
#include "Usuario.h"
#include "Listas.h"
#include "Menus.h"

// Prototipos de los menús
void menuAdministrador();
void menuProfesor();
void menuEstudiante(Estudiante& est);
void menuMochila(MochilaDigital* mochila);

int codigoRol(const std::string& nombre, const std::string& password) {
    if (nombre == "admin" && password == "admin123")
        return 1;
    else if (nombre == "profe" && password == "profe123")
        return 2;
    else if (nombre == "estudiante" && password == "e123")
        return 3;
    else if (nombre == "estudiante2" && password == "e123")
        return 3;
    else
        return 0;
}

int main() {
    std::string nombre, password;
    int rolCode;
    bool acceso = false;
    int opcion;
    do {
        std::cout << "===== BIENVENIDO AL SISTEMA =====" << std::endl;
        std::cout << "- - - - - - - - - - - - - - - - -"<< std::endl;
        std::cout << "       1. Estudiante " << std::endl;
        std::cout << "       2. Profesor(a) " << std::endl;
        std::cout << "       3. Administrador " << std::endl;
        std::cout << "Por favor, selecciona tu tipo de usuario:  " << std::endl;

        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpia el buffer

        std::cout << "Ingrese su nombre: ";
        std::getline(std::cin, nombre);

        std::cout << "Ingrese su password: ";
        std::getline(std::cin, password);

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
            case 3: {
                Estudiante* est = new Estudiante(nombre, "Apellido", password, 1);
                menuEstudiante(*est);
                delete est;
                acceso = true;
                break;
            }
            default:
                std::cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n" << std::endl;
                break;
        }
    } while (!acceso);

    return 0;
}