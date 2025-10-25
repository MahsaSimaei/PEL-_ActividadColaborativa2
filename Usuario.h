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

public:
    Usuario() : nombre(""), apellido(""), passwd(""), id(0), alta(false) {}

    Usuario(string nombre, string apellido, string passwd, int id)
        : nombre(nombre), apellido(apellido), passwd(passwd), id(id), alta(true) {}

    ~Usuario() = default;

    void darAlta() { alta = true; }
    void darBaja() { alta = false; }

    string getNombreCompleto() const { return nombre + " " + apellido; }
    string getNombre() const { return nombre; }
    string getPasswd() const { return passwd; }
    int getId() const { return id; }
    bool isAlta() const { return alta; }

    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }

    string toString() const {
        string estado = alta ? "Alta" : "Baja";
        return "ID: " + std::to_string(id) + " | " + nombre + " " + apellido + " (" + estado + ")";
    }
};

// =======================
// Clase Estudiante
// =======================
class Estudiante : public Usuario {
private:
    MochilaDigital* mochila; // En el heap

public:
    Estudiante() : Usuario() {
        mochila = new MochilaDigital("mochila_default");
    }

    Estudiante(std::string nombre, std::string apellido, std::string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {
        mochila = new MochilaDigital("mochila_" + nombre);
    }

    ~Estudiante() {
        delete mochila;
    }

    MochilaDigital* getMochila() const { return mochila; }
};

// =======================
// Clase Profesor
// =======================
class Profesor : public Usuario {
private:
    ListaDeObjetos<Estudiante> estudiantes;

public:
    Profesor() : Usuario() {}

    Profesor(std::string nombre, std::string apellido, std::string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {}

    void agregarEstudiante(const Estudiante& est) {
        estudiantes.append(est);
    }

    std::string toString() const {
        std::string info = Usuario::toString() + "\nEstudiantes:\n";
        for (int i = 0; i < estudiantes.getSize(); ++i) {
            info += "  - " + estudiantes.get(i + 1).getNombreCompleto() + "\n";
        }
        return info;
    }
};

// =======================
// Clase Admin
// =======================
class Admin : public Usuario {
public:
    Admin() : Usuario() {}

    Admin(std::string nombre, std::string apellido, std::string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {}

    std::string toString() const {
        return Usuario::toString() + " (Administrador)";
    }
};

#endif // USUARIO_H