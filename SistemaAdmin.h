#ifndef SISTEMAADMIN_H
#define SISTEMAADMIN_H

#include "Usuario.h"
#include "Listas.h"
#include <iostream>
#include <string>

class SistemaAdmin {
private:
    ListaDeObjetos<Usuario*> usuarios;
    ListaDeObjetos<int> idsLibres;
    int nextId;

public:
    SistemaAdmin() : nextId(1) {}

    ~SistemaAdmin() {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            delete usuarios.get(i);
        }
    }

    Estudiante* altaEstudiante(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Estudiante* nuevo = new Estudiante(nombre, apellido, passwd, id);
        usuarios.append(nuevo);
        return nuevo;
    }

    Profesor* altaProfesor(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Profesor* nuevo = new Profesor(nombre, apellido, passwd, id);
        usuarios.append(nuevo);
        return nuevo;
    }

    Admin* altaAdmin(const std::string& nombre, const std::string& apellido, const std::string& passwd) {
        int id = obtenerId();
        Admin* nuevo = new Admin(nombre, apellido, passwd, id);
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

    void mostrarUsuarios() const {
        std::cout << "Usuarios en el sistema:\n";
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u) std::cout << u->toString() << std::endl;
        }
    }

    int cantidadUsuarios() const { return usuarios.getSize(); }

    // Opcional: búsqueda directa por ID
    Usuario* buscarUsuario(int id) const {
        for (int i = 1; i <= usuarios.getSize(); ++i) {
            Usuario* u = usuarios.get(i);
            if (u && u->getId() == id && u->isAlta()) return u;
        }
        return nullptr;
    }
};

#endif //SISTEMAADMIN_H
