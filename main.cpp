#include <iostream>
#include <string>
using namespace std;

// Menú de Profesor
void menuProfesor() {
    cout << "\n===== MENU PROFESOR =====" << endl;
    cout << "1. Visualizar estudiantes" << endl;
    cout << "2. Visualizar datos de la clase" << endl;
    cout << "3. Calculadora avanzada" << endl;
    cout << "4. Juego de adivinanza" << endl;
    cout << "0. Cerrar sesion" << endl;
    cout << "Opcion: ";
}

// Menú de Estudiante
void menuEstudiante() {
    cout << "\n===== MENU ESTUDIANTE =====" << endl;
    cout << "1. Cargar fichero a la mochila" << endl;
    cout << "2. Ver contenido de la mochila" << endl;
    cout << "3. Calculadora avanzada" << endl;
    cout << "4. Juego de adivinanza" << endl;
    cout << "0. Cerrar sesion" << endl;
    cout << "Opcion: ";
}

// Menú de Administrador
void menuAdministrador() {
    cout << "\n===== MENU ADMINISTRADOR =====" << endl;
    cout << "1. Dar de alta usuario" << endl;
    cout << "2. Dar de baja usuario" << endl;
    cout << "3. Gestionar datos de usuario" << endl;
    cout << "4. Listar usuarios" << endl;
    cout << "0. Cerrar sesion" << endl;
    cout << "Opcion: ";
}

// Función auxiliar para validar usuario y password y devolver código de rol
int codigoRol(const string& nombre, const string& password) {
    // Usuario: admin / admin123
    // Usuario: profe / profe123
    // Usuario: estudiante / estu123
    if (nombre == "admin" && password == "admin123")
        return 1;
    else if (nombre == "profe" && password == "profe123")
        return 2;
    else if (nombre == "estudiante" && password == "estu123")
        return 3;
    else
        return 0; // credenciales incorrectas
}

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