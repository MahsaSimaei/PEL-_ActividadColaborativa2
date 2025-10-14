#include <iostream>
#include <string>

// Prototipos de los menús
void menuAdministrador();
void menuProfesor();
void menuEstudiante();

// Función auxiliar para validar usuario y password y devolver código de rol
int codigoRol(const std::string& nombre, const std::string& password) {
    if (nombre == "admin" && password == "admin123")
        return 1;
    else if (nombre == "profe" && password == "profe123")
        return 2;
    else if (nombre == "estudiante" && password == "estu123")
        return 3;
    else
        return 0; // credenciales incorrectas
}

int main() {
    std::string nombre, password;
    int rolCode;
    bool acceso = false;

    do {
        std::cout << "===== BIENVENIDO AL SISTEMA =====" << std::endl;
        std::cout << "Ingrese su nombre de usuario: ";
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
            case 3:
                menuEstudiante();
            acceso = true;
            break;
            default:
                std::cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n" << std::endl;
            break;
        }
    } while (!acceso);

    return 0;
}

// Ejemplo de definiciones vacías de menús
void menuAdministrador() {
    std::cout << "Bienvenido administrador." << std::endl;
    // Aquí va el menú real
}
void menuProfesor() {
    std::cout << "Bienvenido profesor." << std::endl;
    // Aquí va el menú real
}
void menuEstudiante() {
    std::cout << "Bienvenido estudiante." << std::endl;
    // Aquí va el menú real
}