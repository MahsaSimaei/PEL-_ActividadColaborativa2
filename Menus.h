#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <string>
#include "Usuario.h"
#include "Listas.h"
#include "RecursosComunes.h"
#include "RecursosMochila.h"
#include "SistemaAdmin.h"
using namespace std;

// =============================================================
// Menú del Estudiante
// =============================================================
void menuMochila(MochilaDigital* mochila);

void menuEstudiante(Estudiante& est) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== MENU ESTUDIANTE =====\n"
             << "1. Gestionar mochila digital\n"
             << "2. Jugar: Adivina el número\n"
             << "3. Calculadora avanzada\n"
             << "0. Cerrar sesión\nOpción: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuMochila(est.getMochila());
                break;
            case 2:
                jugarAdivinaNumero();
                break;
            case 3:
                inicioCalculadora();
                break;
            case 0:
                cout << "Cerrando sesión...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }
}

// =============================================================
// Menú del Profesor
// =============================================================
void menuProfesor() {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== MENU PROFESOR =====\n"
             << "1. Jugar: Adivina el número\n"
             << "2. Calculadora avanzada\n"
             << "0. Cerrar sesión\nOpción: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                jugarAdivinaNumero();
                break;
            case 2:
                inicioCalculadora();
                break;
            case 0:
                cout << "Cerrando sesión...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }
}

// =============================================================
// Menú del Administrador
// =============================================================
void menuAdministrador(SistemaAdmin& sistema) {
    int opcion;
    do {
        std::cout << "\n== MENU ADMINISTRADOR ==\n";
        std::cout << "1. Alta estudiante\n";
        std::cout << "2. Alta profesor\n";
        std::cout << "3. Alta administrador\n";
        std::cout << "4. Baja usuario\n";
        std::cout << "5. Modificar usuario\n";
        std::cout << "6. Mostrar usuarios\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Estudiante* nuevo = sistema.altaEstudiante(nombre, apellido, passwd);
                std::cout << "Estudiante creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 2: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Profesor* nuevo = sistema.altaProfesor(nombre, apellido, passwd);
                std::cout << "Profesor creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 3: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Admin* nuevo = sistema.altaAdmin(nombre, apellido, passwd);
                std::cout << "Administrador creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 4: {
                int id;
                std::cout << "ID a dar de baja: ";
                std::cin >> id;
                std::cin.ignore();
                if (sistema.bajaUsuario(id))
                    std::cout << "Usuario dado de baja correctamente.\n";
                else
                    std::cout << "Usuario no encontrado.\n";
                break;
            }
            case 5: {
                int id;
                std::string nombre, apellido;
                std::cout << "ID a modificar: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Nuevo nombre: "; std::getline(std::cin, nombre);
                std::cout << "Nuevo apellido: "; std::getline(std::cin, apellido);
                if (sistema.modificarUsuario(id, nombre, apellido))
                    std::cout << "Usuario modificado.\n";
                else
                    std::cout << "Usuario no encontrado.\n";
                break;
            }
            case 6:
                sistema.mostrarUsuarios();
                break;
            case 0:
                std::cout << "Saliendo del menú administrador.\n";
                break;
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

// =============================================================
// Menú Mochila Digital
// =============================================================
void menuMochila(MochilaDigital* mochila) {
    int opcion;
    do {
        cout << "\n--- Menú Mochila Digital ---\n";
        cout << "1. Agregar documento\n";
        cout << "2. Eliminar documento\n";
        cout << "3. Ver documentos\n";
        cout << "4. Ver contenido de un documento\n";
        cout << "5. Editar contenido de un documento\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                string nombre;
                cout << "Nombre del archivo a agregar: ";
                getline(cin, nombre);
                mochila->agregarDocumento(nombre);
                break;
            }
            case 2: {
                int pos;
                cout << "Posición del documento a eliminar (1,2,...): ";
                if (!(cin >> pos)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->eliminarDocumento(pos);
                break;
            }
            case 3:
                mochila->verDocumentos();
                break;
            case 4: {
                int pos;
                cout << "Posición del documento a ver contenido (1,2,...): ";
                if (!(cin >> pos)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->verContenidoDocumento(pos);
                break;
            }
            case 5: {
                int pos;
                cout << "Posición del documento a editar (1,2,...): ";
                if (!(cin >> pos)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->editarContenidoDocumento(pos);
                break;
            }
            case 0:
                cout << "Saliendo del menú de la mochila.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

#endif // MENUS_H