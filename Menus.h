#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <limits>
#include "Usuario.h"
#include "Recursos.h"
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
void menuEstudiante(Estudiante& est) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== MENU ESTUDIANTE =====\n"
             << "1. Agregar archivo a mochila\n"
             << "2. Ver mochila\n"
             << "3. Eliminar archivo\n"
             << "4. Calculadora avanzada\n"
             << "5. Juego de adivinanza\n"
             << "0. Cerrar sesion\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string archivo;
                cout << "Ingrese nombre del archivo: ";
                cin >> archivo;
                est.agregarArchivo(archivo);
                cout << "Archivo agregado correctamente.\n";
                break;
            }
            case 2:
                cout << est.verMochila();
                break;
            case 3: {
                int pos;
                cout << "Posición a eliminar: ";
                cin >> pos;
                est.eliminarArchivo(pos);
                cout << "Archivo eliminado.\n";
                break;
            }
            case 4:
                inicioCalculadora();
                break;
            case 5:
                juegoRecurso5();
                break;
            case 0:
                cout << "Cerrando sesión...\n";
                break;
        }
    }
}

// =============================================================
// Menú del Profesor
// =============================================================
void menuProfesor(Profesor& prof) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== MENU PROFESOR =====\n"
             << "1. Ver estudiantes\n"
             << "2. Agregar estudiante a clase\n"
             << "3. Calculadora avanzada\n"
             << "4. Juego de adivinanza\n"
             << "0. Cerrar sesion\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << prof.toString();
                break;
            case 2: {
                string nombre, apellido, pass;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Password: "; cin >> pass;
                Estudiante nuevo(nombre, apellido, pass, generarId());
                prof.agregarEstudiante(nuevo);
                cout << "Estudiante agregado a la clase.\n";
                break;
            }
            case 3:
                inicioCalculadora();
                break;
            case 4:
                juegoRecurso5();
                break;
            case 0:
                cout << "Cerrando sesión...\n";
                break;
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
             << "0. Salir\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombre, apellido, pass;
                int tipo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Password: "; cin >> pass;
                cout << "Tipo (1=Estudiante, 2=Profesor): ";
                cin >> tipo;

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
        }
    }
}

#endif
