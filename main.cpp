#include <iostream>
#include <string>
#include "MochilaDigital.h"
#include "Usuario.h"
#include "Listas.h";
#include "JuegoAdivinaNumero.h"
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
        std::cout<< "       1.Estudiante " << std::endl;
        std::cout<< "       2. Profesor(a) " << std::endl;
        std::cout<< "       3. Administrador " << std::endl;
        std::cout << "Por favor, selecciona tu tipo de usuario:  " <<std::endl;

        std::cin >> opcion;
            
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

void menuAdministrador() {
    std::cout << "Bienvenido administrador." << std::endl;
}

void menuProfesor() {
    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\n===== MENU PROFESOR =====\n"
                  << "1. Jugar: Adivina el número\n"
                  << "0. Cerrar sesión\nOpción: ";
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no válida.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                jugarAdivinaNumero();
            break;
            case 0:
                std::cout << "Cerrando sesión...\n";
            break;
            default:
                std::cout << "Opción inválida.\n";
        }
    }
}

void menuEstudiante(Estudiante& est) {
    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\n===== MENU ESTUDIANTE =====\n"
                  << "1. Gestionar mochila digital\n"
                  << "2. Jugar: Adivina el número\n"
                  << "0. Cerrar sesión\nOpción: ";
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no válida.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuMochila(est.getMochila());
            break;
            case 2:
                jugarAdivinaNumero();
            break;
            case 0:
                std::cout << "Cerrando sesión...\n";
            break;
            default:
                std::cout << "Opción inválida.\n";
        }
    }
}
void menuMochila(MochilaDigital* mochila) {
    int opcion;
    do {
        std::cout << "\n--- Menú Mochila Digital ---\n";
        std::cout << "1. Agregar documento\n";
        std::cout << "2. Eliminar documento\n";
        std::cout << "3. Ver documentos\n";
        std::cout << "4. Ver contenido de un documento\n";
        std::cout << "5. Editar contenido de un documento\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::string nombre;
                std::cout << "Nombre del archivo a agregar: ";
                std::getline(std::cin, nombre);
                mochila->agregarDocumento(nombre);
                break;
            }
            case 2: {
                int pos;
                std::cout << "Posición del documento a eliminar (1,2,...): ";
                if (!(std::cin >> pos)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Debe ingresar un número válido.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                mochila->eliminarDocumento(pos - 1);
                break;
            }
            case 3:
                mochila->verDocumentos();
                break;
            case 4: {
                int pos;
                std::cout << "Posición del documento a ver contenido (1,2,...): ";
                if (!(std::cin >> pos)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Debe ingresar un número válido.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                mochila->verContenidoDocumento(pos - 1);
                break;
            }
            case 5: {
                int pos;
                std::cout << "Posición del documento a editar (1,2,...): ";
                if (!(std::cin >> pos)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Debe ingresar un número válido.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                mochila->editarContenidoDocumento(pos - 1);
                break;
            }
            case 0:
                std::cout << "Saliendo del menú de la mochila.\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
