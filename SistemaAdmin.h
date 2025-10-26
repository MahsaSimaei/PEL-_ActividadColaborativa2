#ifndef SISTEMAADMIN_H
#define SISTEMAADMIN_H

#include "Usuario.h"
#include "Listas.h"
#include <iostream>
#include <string>

// ============================================================
// Clase SistemaAdmin: Administración de usuarios del sistema
// ============================================================
class SistemaAdmin {
private:
    ListaDeObjetos<Usuario*> usuarios;      // Lista general de usuarios
    ListaDeObjetos<Admin*> admins;          // Lista de administradores
    ListaDeObjetos<Profesor*> profesores;   // Lista de profesores
    ListaDeObjetos<Estudiante*> estudiantes;// Lista de estudiantes
    ListaDeObjetos<int> idsLibres;          // IDs disponibles para reutilizar
    int nextId;                             // Siguiente ID a asignar

public:
    // Constructor: inicializa el siguiente ID en 1
    SistemaAdmin() : nextId(1) {}

    // Destructor: libera la memoria de todos los usuarios
    ~SistemaAdmin() {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            delete usuarios.get(i); // Libera cada Usuario
        }
        for (int i = 1; i <= admins.getSize(); ++i)
            delete admins.get(i); // Libera cada Admin
        for (int i = 1; i <= profesores.getSize(); ++i)
            delete profesores.get(i); // Libera cada Profesor
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            delete estudiantes.get(i); // Libera cada Estudiante
    }

    // Crea un nuevo administrador y lo agrega a las listas correspondientes
    Admin* altaAdmin(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Admin* nuevo = new Admin(nombre, apellido, passwd, id);
        admins.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

    // Crea un nuevo profesor y lo agrega a las listas correspondientes
    Profesor* altaProfesor(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Profesor* nuevo = new Profesor(nombre, apellido, passwd, id);
        profesores.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

    // Crea un nuevo estudiante y lo agrega a las listas correspondientes
    Estudiante* altaEstudiante(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Estudiante* nuevo = new Estudiante(nombre, apellido, passwd, id);
        estudiantes.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

    // Modifica el nombre y apellido de un usuario por su ID
    bool modificarUsuario(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u && u->getId() == id && u->isAlta()) {
                u->setNombre(nuevoNombre);
                u->setApellido(nuevoApellido);
                return true;
            }
        }
        return false;
    }

    // Modifica nombre y apellido de un admin por ID
    bool modificarAdmin(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        Admin* a = buscarAdmin(id);
        if (a && a->isAlta()) {
            a->setNombre(nuevoNombre);
            a->setApellido(nuevoApellido);
            return true;
        }
        return false;
    }

    // Modifica nombre y apellido de un profesor por ID
    bool modificarProfesor(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        Profesor* p = buscarProfesor(id);
        if (p && p->isAlta()) {
            p->setNombre(nuevoNombre);
            p->setApellido(nuevoApellido);
            return true;
        }
        return false;
    }

    // Modifica nombre y apellido de un estudiante por ID
    bool modificarEstudiante(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        Estudiante* e = buscarEstudiante(id);
        if (e && e->isAlta()) {
            e->setNombre(nuevoNombre);
            e->setApellido(nuevoApellido);
            return true;
        }
        return false;
    }

private:
    // Obtiene un nuevo ID, reutilizando si hay disponibles
    int obtenerId() {
        if (idsLibres.getSize() > 0) {
            int id = idsLibres.get(1);
            idsLibres.erase(1); // Quita el ID libre de la lista
            return id;
        }
        return nextId++; // Si no hay libres, usa el siguiente
    }

public:
    // Da de baja y elimina a un usuario por ID
    bool bajaUsuario(int id) {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u && u->getId() == id && u->isAlta()) {
                u->darBaja();
                idsLibres.append(id);
                delete u;
                usuarios.erase(i);
                return true;
            }
        }
        return false;
    }

    // Da de baja y elimina a un admin por ID
    bool bajaAdmin(int id) {
        for (int i = 1; i <= admins.getSize(); ++i) {
            Admin* a = admins.get(i);
            if (a && a->getId() == id && a->isAlta()) {
                a->darBaja();
                idsLibres.append(id);
                delete a;
                admins.erase(i);
                return true;
            }
        }
        return false;
    }

    // Da de baja y elimina a un profesor por ID
    bool bajaProfesor(int id) {
        for (int i = 1; i <= profesores.getSize(); ++i) {
            Profesor* p = profesores.get(i);
            if (p && p->getId() == id && p->isAlta()) {
                p->darBaja();
                idsLibres.append(id);
                delete p;
                profesores.erase(i);
                return true;
            }
        }
        return false;
    }

    // Da de baja y elimina a un estudiante por ID
    bool bajaEstudiante(int id) {
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            Estudiante* e = estudiantes.get(i);
            if (e && e->getId() == id && e->isAlta()) {
                e->darBaja();
                idsLibres.append(id);
                delete e;
                estudiantes.erase(i);
                return true;
            }
        }
        return false;
    }

    // Muestra todos los usuarios registrados en el sistema
    void mostrarUsuarios() const {
        std::cout << "Usuarios en el sistema:\n";
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u) std::cout << u->toString() << std::endl;
        }
    }

    // Muestra todos los administradores
    void mostrarAdmins() const {
        std::cout << "Administradores:\n";
        for (int i = 1; i <= admins.getSize(); ++i) {
            Admin* a = admins.get(i);
            if (a) std::cout << a->toString() << std::endl;
        }
    }

    // Muestra todos los profesores
    void mostrarProfesores() const {
        std::cout << "Profesores:\n";
        for (int i = 1; i <= profesores.getSize(); ++i) {
            Profesor* p = profesores.get(i);
            if (p) std::cout << p->toString() << std::endl;
        }
    }

    // Muestra todos los estudiantes
    void mostrarEstudiantes() const {
        std::cout << "Estudiantes:\n";
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            Estudiante* e = estudiantes.get(i);
            if (e) std::cout << e->toString() << std::endl;
        }
    }

    // Devuelve la cantidad de usuarios, admins, profesores y estudiantes
    int cantidadUsuarios() const { return usuarios.getSize(); }
    int cantidadAdmins() const { return admins.getSize(); }
    int cantidadProfesores() const { return profesores.getSize(); }
    int cantidadEstudiantes() const { return estudiantes.getSize(); }

    // Busca un usuario por ID
    Usuario* buscarUsuario(int id) const {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u && u->getId() == id && u->isAlta()) return u;
        }
        return nullptr;
    }

    // Busca un admin por ID
    Admin* buscarAdmin(int id) const {
        for (int i = 1; i <= admins.getSize(); ++i) {
            Admin* a = admins.get(i);
            if (a && a->getId() == id && a->isAlta()) return a;
        }
        return nullptr;
    }

    // Busca un profesor por ID
    Profesor* buscarProfesor(int id) const {
        for (int i = 1; i <= profesores.getSize(); ++i) {
            Profesor* p = profesores.get(i);
            if (p && p->getId() == id && p->isAlta()) return p;
        }
        return nullptr;
    }

    // Busca un estudiante por ID
    Estudiante* buscarEstudiante(int id) const {
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            Estudiante* e = estudiantes.get(i);
            if (e && e->getId() == id && e->isAlta()) return e;
        }
        return nullptr;
    }

    // Busca estudiante por índice en la lista (1-indexado)
    Estudiante* buscarEstudiantePorIndice(int idx) const {
        if (idx >= 1 && idx <= estudiantes.getSize())
            return estudiantes.get(idx);
        return nullptr;
    }

    // Busca profesor por índice en la lista (1-indexado)
    Profesor* buscarProfesorPorIndice(int idx) const {
        if (idx >= 1 && idx <= profesores.getSize())
            return profesores.get(idx);
        return nullptr;
    }
};

#endif //SISTEMAADMIN_H