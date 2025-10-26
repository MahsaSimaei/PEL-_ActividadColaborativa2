#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <string>
#include "Usuario.h"
#include "Listas.h"
#include "RecursosComunes.h"
#include "RecursosMochila.h"
#include "SistemaAdmin.h"
#include "GestionAulas.h"
using namespace std;

// =============================================================
// Menú del Estudiante
// =============================================================

// Declaración de función del menú de mochila digital
void menuMochila(MochilaDigital* mochila);

// Menú principal para el estudiante
void menuEstudiante(Estudiante& est) {
    int opcion = -1; // Variable para la opción elegida
    while (opcion != 0) { // Bucle hasta que el usuario decida salir
        cout << "\n===== MENU ESTUDIANTE =====\n"
             << "1. Gestionar mochila digital\n"
             << "2. Jugar: Adivina el número\n"
             << "3. Calculadora avanzada\n"
             << "0. Cerrar sesión\nOpción: ";
        if (!(cin >> opcion)) { // Validación de entrada
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) { // Ejecuta según la opción seleccionada
            case 1:
                menuMochila(est.getMochila()); // Menú mochila digital
                break;
            case 2:
                jugarAdivinaNumero(); // Juego adivina el número
                break;
            case 3:
                inicioCalculadora(); // Calculadora avanzada
                break;
            case 0:
                cout << "Cerrando sesión...\n"; // Salir
                break;
            default:
                cout << "Opción inválida.\n"; // Opción no válida
        }
    }
}

// =============================================================
// Menú del Profesor
// =============================================================

// Menú para el profesor (inline)
inline void menuProfesor(GestionAulas* gestionAula) {
    int opcion = -1; // Variable para la opción elegida
    while (opcion != 0) { // Bucle hasta que el usuario decida salir
        std::cout << "\n===== MENU PROFESOR =====\n"
                  << "1. Jugar: Adivina el número\n"
                  << "2. Calculadora avanzada\n"
                  << "3. Ver número de inscritos en el aula\n"
                  << "4. Ver listado de estudiantes\n"
                  << "5. Ver datos de un estudiante\n"
                  << "0. Cerrar sesión\nOpción: ";
        if (!(std::cin >> opcion)) { // Validación de entrada
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no válida.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) { // Ejecuta según la opción seleccionada
            case 1:
                jugarAdivinaNumero(); // Juego adivina el número
                break;
            case 2:
                 inicioCalculadora(); // Calculadora avanzada
                break;
            case 3:
                std::cout << "Número de inscritos: " << gestionAula->getNumeroInscritos() << std::endl; // Muestra inscritos
                break;
            case 4:
                std::cout << gestionAula->listadoEstudiantes(); // Muestra listado de estudiantes
                break;
            case 5: {
                int id;
                std::cout << "Ingrese el ID del estudiante: ";
                std::cin >> id;
                std::cin.ignore();
                auto est = gestionAula->buscarEstudiante(id); // Busca estudiante por ID
                if (est)
                    std::cout << est->toString() << std::endl; // Muestra datos del estudiante
                else
                    std::cout << "Estudiante no encontrado.\n";
                break;
            }
            case 0:
                std::cout << "Cerrando sesión...\n"; // Salir
                break;
            default:
                std::cout << "Opción inválida.\n"; // Opción no válida
        }
    }
}


// =============================================================
// Menú del Administrador
// =============================================================

// Menú principal para el administrador
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

        switch (opcion) { // Ejecuta según la opción seleccionada
            case 1: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Estudiante* nuevo = sistema.altaEstudiante(nombre, apellido, passwd); // Alta estudiante
                std::cout << "Estudiante creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 2: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Profesor* nuevo = sistema.altaProfesor(nombre, apellido, passwd); // Alta profesor
                std::cout << "Profesor creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 3: {
                std::string nombre, apellido, passwd;
                std::cout << "Nombre: "; std::getline(std::cin, nombre);
                std::cout << "Apellido: "; std::getline(std::cin, apellido);
                std::cout << "Contraseña: "; std::getline(std::cin, passwd);
                Admin* nuevo = sistema.altaAdmin(nombre, apellido, passwd); // Alta administrador
                std::cout << "Administrador creado: " << nuevo->toString() << std::endl;
                break;
            }
            case 4: {
                int id;
                std::cout << "ID a dar de baja: ";
                std::cin >> id;
                std::cin.ignore();
                if (sistema.bajaUsuario(id)) // Baja usuario por ID
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
                if (sistema.modificarUsuario(id, nombre, apellido)) // Modifica usuario
                    std::cout << "Usuario modificado.\n";
                else
                    std::cout << "Usuario no encontrado.\n";
                break;
            }
            case 6:
                sistema.mostrarUsuarios(); // Muestra todos los usuarios
                break;
            case 0:
                std::cout << "Saliendo del menú administrador.\n"; // Salir
                break;
            default:
                std::cout << "Opción inválida.\n"; // Opción no válida
        }
    } while (opcion != 0);
}

// =============================================================
// Menú Mochila Digital
// =============================================================

// Menú para gestionar la mochila digital
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

        switch (opcion) { // Ejecuta según la opción seleccionada
            case 1: {
                string nombre;
                cout << "Nombre del archivo a agregar: ";
                getline(cin, nombre);
                mochila->agregarDocumento(nombre); // Agrega documento
                break;
            }
            case 2: {
                int pos;
                cout << "Posición del documento a eliminar (1,2,...): ";
                if (!(cin >> pos)) { // Validación de entrada
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->eliminarDocumento(pos); // Elimina documento
                break;
            }
            case 3:
                mochila->verDocumentos(); // Muestra documentos
                break;
            case 4: {
                int pos;
                cout << "Posición del documento a ver contenido (1,2,...): ";
                if (!(cin >> pos)) { // Validación de entrada
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->verContenidoDocumento(pos); // Muestra contenido
                break;
            }
            case 5: {
                int pos;
                cout << "Posición del documento a editar (1,2,...): ";
                if (!(cin >> pos)) { // Validación de entrada
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Debe ingresar un número válido.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mochila->editarContenidoDocumento(pos); // Edita contenido
                break;
            }
            case 0:
                cout << "Saliendo del menú de la mochila.\n"; // Salir
                break;
            default:
                cout << "Opción inválida.\n"; // Opción no válida
        }
    } while (opcion != 0);
}

#endif // MENUS_H