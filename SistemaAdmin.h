#ifndef SISTEMAADMIN_H
#define SISTEMAADMIN_H

#include "Usuario.h"
#include "Listas.h"
#include <iostream>
#include <string>

class SistemaAdmin {
private:
    ListaDeObjetos<Usuario*> usuarios;
    ListaDeObjetos<Admin*> admins;
    ListaDeObjetos<Profesor*> profesores;
    ListaDeObjetos<Estudiante*> estudiantes;
    ListaDeObjetos<int> idsLibres;
    int nextId;

public:
    SistemaAdmin() : nextId(1) {}

    ~SistemaAdmin() {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            delete usuarios.get(i);
        }
        for (int i = 1; i <= admins.getSize(); ++i)
            delete admins.get(i);
        for (int i = 1; i <= profesores.getSize(); ++i)
            delete profesores.get(i);
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            delete estudiantes.get(i);
    }

    Admin* altaAdmin(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Admin* nuevo = new Admin(nombre, apellido, passwd, id);
        admins.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

    Profesor* altaProfesor(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Profesor* nuevo = new Profesor(nombre, apellido, passwd, id);
        profesores.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

    Estudiante* altaEstudiante(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Estudiante* nuevo = new Estudiante(nombre, apellido, passwd, id);
        estudiantes.append(nuevo);
        usuarios.append(nuevo);
        return nuevo;
    }

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

    bool modificarAdmin(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        Admin* a = buscarAdmin(id);
        if (a && a->isAlta()) {
            a->setNombre(nuevoNombre);
            a->setApellido(nuevoApellido);
            return true;
        }
        return false;
    }

    bool modificarProfesor(int id, const std::string& nuevoNombre, const std::string& nuevoApellido) {
        Profesor* p = buscarProfesor(id);
        if (p && p->isAlta()) {
            p->setNombre(nuevoNombre);
            p->setApellido(nuevoApellido);
            return true;
        }
        return false;
    }

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
    int obtenerId() {
        if (idsLibres.getSize() > 0) {
            int id = idsLibres.get(1);
            idsLibres.erase(1);
            return id;
        }
        return nextId++;
    }

public:
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

    void mostrarUsuarios() const {
        std::cout << "Usuarios en el sistema:\n";
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u) std::cout << u->toString() << std::endl;
        }
    }
    void mostrarAdmins() const {
        std::cout << "Administradores:\n";
        for (int i = 1; i <= admins.getSize(); ++i) {
            Admin* a = admins.get(i);
            if (a) std::cout << a->toString() << std::endl;
        }
    }
    void mostrarProfesores() const {
        std::cout << "Profesores:\n";
        for (int i = 1; i <= profesores.getSize(); ++i) {
            Profesor* p = profesores.get(i);
            if (p) std::cout << p->toString() << std::endl;
        }
    }
    void mostrarEstudiantes() const {
        std::cout << "Estudiantes:\n";
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            Estudiante* e = estudiantes.get(i);
            if (e) std::cout << e->toString() << std::endl;
        }
    }

    int cantidadUsuarios() const { return usuarios.getSize(); }
    int cantidadAdmins() const { return admins.getSize(); }
    int cantidadProfesores() const { return profesores.getSize(); }
    int cantidadEstudiantes() const { return estudiantes.getSize(); }

    Usuario* buscarUsuario(int id) const {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u && u->getId() == id && u->isAlta()) return u;
        }
        return nullptr;
    }
    Admin* buscarAdmin(int id) const {
        for (int i = 1; i <= admins.getSize(); ++i) {
            Admin* a = admins.get(i);
            if (a && a->getId() == id && a->isAlta()) return a;
        }
        return nullptr;
    }
    Profesor* buscarProfesor(int id) const {
        for (int i = 1; i <= profesores.getSize(); ++i) {
            Profesor* p = profesores.get(i);
            if (p && p->getId() == id && p->isAlta()) return p;
        }
        return nullptr;
    }
    Estudiante* buscarEstudiante(int id) const {
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            Estudiante* e = estudiantes.get(i);
            if (e && e->getId() == id && e->isAlta()) return e;
        }
        return nullptr;
    }
};

#endif //SISTEMAADMIN_H