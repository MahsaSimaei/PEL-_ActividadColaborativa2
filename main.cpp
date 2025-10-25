#include <iostream>
#include <string>
#include "Usuario.h"
#include "SistemaAdmin.h"
#include "Menus.h"
#include "GestionAulas.h"
#include "Listas.h"

using namespace std;

// Estructura para asociar id de profesor y su aula
struct ParIdAula {
    int id;
    GestionAulas* aula;
    ParIdAula(int i = -1, GestionAulas* a = nullptr) : id(i), aula(a) {}
};

// Buscar aula por id en la lista
GestionAulas* buscarAulaPorId(ListaDeObjetos<ParIdAula>& aulas, int id) {
    for (int i = 1; i <= aulas.getSize(); ++i) {
        if (aulas.get(i).id == id)
            return aulas.get(i).aula;
    }
    return nullptr;
}

// Inicializa usuarios y retorna el sistema
SistemaAdmin inicializarSistema() {
    SistemaAdmin sistema;
    sistema.altaAdmin("admin", "Principal", "admin123");
    sistema.altaProfesor("profe", "Ejemplo", "profe123");
    sistema.altaProfesor("Maria", "Gomez", "profe123");
    sistema.altaEstudiante("Juan", "Perez", "e123");
    sistema.altaEstudiante("Ana", "Lopez", "e123");
    sistema.altaEstudiante("Luis", "Martinez", "e123");
    sistema.altaEstudiante("Sofia", "Garcia", "e123");
    return sistema;
}

// Asocia profesores con aulas y estudiantes con profesores
void asociarAulasYEstudiantes(SistemaAdmin& sistema, ListaDeObjetos<ParIdAula>& aulas) {
    int idProfe = -1, idMaria = -1;

    // Crear aulas para cada profesor
    for (int i = 1; i <= sistema.cantidadProfesores(); ++i) {
        Profesor* profe = sistema.buscarProfesor(i);
        if (profe) {
            GestionAulas* gestion = new GestionAulas(profe);
            aulas.append(ParIdAula(profe->getId(), gestion));
            if (profe->getNombre() == "profe") idProfe = profe->getId();
            if (profe->getNombre() == "Maria") idMaria = profe->getId();
        }
    }

    // Asignar estudiantes a profesores
    for (int i = 1; i <= sistema.cantidadEstudiantes(); ++i) {
        Estudiante* est = sistema.buscarEstudiante(i);
        if (est) {
            if ((est->getNombre() == "Juan" || est->getNombre() == "Ana") && idProfe != -1)
                buscarAulaPorId(aulas, idProfe)->agregarEstudiante(est);
            else if (idMaria != -1)
                buscarAulaPorId(aulas, idMaria)->agregarEstudiante(est);
        }
    }
}

int main() {
    string nombre, password;
    int opcion, rolCode;
    bool acceso = false;

    SistemaAdmin sistema = inicializarSistema();
    ListaDeObjetos<ParIdAula> aulas;
    asociarAulasYEstudiantes(sistema, aulas);

    do {
        cout << "===== BIENVENIDO AL SISTEMA =====\n";
        cout << "       1. Estudiante\n";
        cout << "       2. Profesor(a)\n";
        cout << "       3. Administrador\n";
        cout << "Por favor, selecciona tu tipo de usuario: ";
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

        switch (opcion) {
        case 1: { // Estudiante
            bool encontrado = false;
            for (int i = 1; i <= sistema.cantidadEstudiantes(); ++i) {
                Estudiante* est = sistema.buscarEstudiante(i);
                if (est && est->getNombre() == nombre && est->getPasswd() == password && est->isAlta()) {
                    cout << "Bienvenido, estudiante " << nombre << "!\n";
                    menuEstudiante(*est);
                    acceso = true;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
                cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n\n";
            break;
        }
        case 2: { // Profesor
            bool encontrado = false;
            for (int i = 1; i <= sistema.cantidadProfesores(); ++i) {
                Profesor* profe = sistema.buscarProfesor(i);
                if (profe && profe->getNombre() == nombre && profe->getPasswd() == password && profe->isAlta()) {
                    cout << "Bienvenido, profesor " << nombre << "!\n";
                    GestionAulas* aula = buscarAulaPorId(aulas, profe->getId());
                    if (aula) {
                        menuProfesor(aula);
                        acceso = true;
                    } else {
                        cout << "No se encontró aula para el profesor.\n";
                    }
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
                cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n\n";
            break;
        }
        case 3: { // Admin
            bool encontrado = false;
            for (int i = 1; i <= sistema.cantidadAdmins(); ++i) {
                Admin* admin = sistema.buscarAdmin(i);
                if (admin && admin->getNombre() == nombre && admin->getPasswd() == password && admin->isAlta()) {
                    cout << "Bienvenido, administrador " << nombre << "!\n";
                    menuAdministrador(sistema);
                    acceso = true;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
                cout << "\n*** ERROR: Usuario o password incorrecto. Intente de nuevo. ***\n\n";
            break;
        }
        default:
            cout << "Opción inválida\n";
            break;
        }
    } while (!acceso);

    // Liberar memoria de aulas
    for (int i = 1; i <= aulas.getSize(); ++i)
        delete aulas.get(i).aula;

    return 0;
}