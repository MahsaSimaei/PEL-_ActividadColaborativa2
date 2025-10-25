#ifndef USUARIO_H
#define USUARIO_H

#include "Listas.h"
#include "RecursosMochila.h"
#include <string>
using std::string;

// =======================
// Clase Usuario
// =======================
class Usuario {
protected:
    string nombre;
    string apellido;
    string passwd;
    int id;
    bool alta;
    int rol; // 1=Admin, 2=Profesor, 3=Estudiante

public:
    Usuario()
        : nombre(""), apellido(""), passwd(""), id(0), alta(false), rol(0) {}

    Usuario(const string& nombre, const string& apellido, const string& passwd, int id, int rol)
        : nombre(nombre), apellido(apellido), passwd(passwd), id(id), alta(true), rol(rol) {}

    ~Usuario() {}

    void darAlta() { alta = true; }
    void darBaja() { alta = false; }

    string getNombreCompleto() const { return nombre + " " + apellido; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getPasswd() const { return passwd; }
    int getId() const { return id; }
    bool isAlta() const { return alta; }
    int getRol() const { return rol; }

    void setNombre(const string& n) { nombre = n; }
    void setApellido(const string& a) { apellido = a; }
    void setPasswd(const string& pw) { passwd = pw; }
    void setId(int i) { id = i; }
    void setRol(int r) { rol = r; }

    string toString() const {
        string estado = alta ? "Alta" : "Baja";
        string tipo;
        switch (rol) {
            case 1: tipo = "[Administrador]"; break;
            case 2: tipo = "[Profesor]"; break;
            case 3: tipo = "[Estudiante]"; break;
            default: tipo = "[Desconocido]";
        }
        return "ID: " + std::to_string(id) + " | " + nombre + " " + apellido + " (" + estado + ") " + tipo;
    }
};

// =======================
// Clase Estudiante
// =======================
class Estudiante : public Usuario {
private:
    MochilaDigital* mochila; // En el heap

    // Previene copias accidentales
    Estudiante(const Estudiante&) = delete;
    Estudiante& operator=(const Estudiante&) = delete;

public:
    Estudiante()
        : Usuario("", "", "", 0, 3), mochila(new MochilaDigital("mochila_default")) {}

    Estudiante(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 3),
          mochila(new MochilaDigital("mochila_" + nombre)) {}

    ~Estudiante() {
        delete mochila;
    }

    MochilaDigital* getMochila() const { return mochila; }

    string toString() const {
        string estado = alta ? "Alta" : "Baja";
        return "ID: " + std::to_string(id) + " | " + nombre + " " + apellido +
               " (" + estado + ") [Estudiante]";
    }
};

// =======================
// Clase Profesor
// =======================
class Profesor : public Usuario {
private:
    ListaDeObjetos<Estudiante*> estudiantes;

public:
    Profesor() : Usuario("", "", "", 0, 2) {}
    Profesor(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 2) {}

    void agregarEstudiante(Estudiante* est) {
        estudiantes.append(est);
    }

    string toString() const {
        string info = Usuario::toString() + " [Profesor]\nEstudiantes:\n";
        for (int i = 0; i < estudiantes.getSize(); ++i) {
            info += "  - " + estudiantes.get(i + 1)->getNombreCompleto() + "\n";
        }
        return info;
    }
};

// =======================
// Clase Admin
// =======================
class Admin : public Usuario {
public:
    Admin() : Usuario("", "", "", 0, 1) {}
    Admin(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 1) {}

    string toString() const {
        return Usuario::toString() + " [Administrador]";
    }
};

#endif // USUARIO_H