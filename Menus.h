#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "Usuario.h"
#include "Listas.h"
#include "RecursosComunes.h"
#include "RecursosMochila.h"
using namespace std;

// =============================================================
// Estructuras globales de gestión
// =============================================================
ListaDeObjetos<Estudiante>* estudiantes = new ListaDeObjetos<Estudiante>();
ListaDeObjetos<Profesor>* profesores = new ListaDeObjetos<Profesor>();
Admin* admin = new Admin("Admin", "Gonzalez", "xyz", 1);

// Contador automático de IDs
int nextId = 2;

// =============================================================
// Funciones auxiliares
// =============================================================
int generarId() { return nextId++; }

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
void menuAdministrador() {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== MENU ADMINISTRADOR =====\n"
             << "1. Dar de alta usuario\n"
             << "2. Dar de baja usuario\n"
             << "3. Listar usuarios\n"
             << "0. Salir\nOpción: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                string nombre, apellido, pass;
                int tipo;
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Apellido: "; getline(cin, apellido);
                cout << "Password: "; getline(cin, pass);
                cout << "Tipo (1=Estudiante, 2=Profesor): ";
                cin >> tipo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (tipo == 1) {
                    estudiantes->append(Estudiante(nombre, apellido, pass, generarId()));
                    cout << "Estudiante dado de alta correctamente.\n";
                } else {
                    profesores->append(Profesor(nombre, apellido, pass, generarId()));
                    cout << "Profesor dado de alta correctamente.\n";
                }
                break;
            }

            case 2: {
                int tipo, id;
                cout << "Tipo (1=Estudiante, 2=Profesor): ";
                cin >> tipo;
                cout << "ID a eliminar: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (tipo == 1) {
                    for (int i = 1; i <= estudiantes->getSize(); i++) {
                        if (estudiantes->get(i).getId() == id) {
                            estudiantes->erase(i);
                            cout << "Estudiante eliminado correctamente.\n";
                            break;
                        }
                    }
                } else {
                    for (int i = 1; i <= profesores->getSize(); i++) {
                        if (profesores->get(i).getId() == id) {
                            profesores->erase(i);
                            cout << "Profesor eliminado correctamente.\n";
                            break;
                        }
                    }
                }
                break;
            }

            case 3:
                cout << "=== Estudiantes ===\n" << estudiantes->toString();
                cout << "\n=== Profesores ===\n" << profesores->toString();
                break;

            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }
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

#endif