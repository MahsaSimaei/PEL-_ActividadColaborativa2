#include <iostream>
#include <string>
using namespace std;

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
