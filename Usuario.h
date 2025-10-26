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
    string nombre;      // Nombre del usuario
    string apellido;    // Apellido del usuario
    string passwd;      // Contraseña
    int id;             // Identificador único
    bool alta;          // Estado de alta/baja
    int rol;            // 1=Admin, 2=Profesor, 3=Estudiante

public:
    // Constructor por defecto
    Usuario()
        : nombre(""), apellido(""), passwd(""), id(0), alta(false), rol(0) {}

    // Constructor con parámetros
    Usuario(const string& nombre, const string& apellido, const string& passwd, int id, int rol)
        : nombre(nombre), apellido(apellido), passwd(passwd), id(id), alta(true), rol(rol) {}

    // Destructor
    ~Usuario() {}

    // Marca al usuario como dado de alta
    void darAlta() { alta = true; }
    // Marca al usuario como dado de baja
    void darBaja() { alta = false; }

    // Devuelve el nombre completo del usuario
    string getNombreCompleto() const { return nombre + " " + apellido; }
    // Devuelve solo el nombre
    string getNombre() const { return nombre; }
    // Devuelve solo el apellido
    string getApellido() const { return apellido; }
    // Devuelve la contraseña
    string getPasswd() const { return passwd; }
    // Devuelve el ID del usuario
    int getId() const { return id; }
    // Devuelve el estado de alta
    bool isAlta() const { return alta; }
    // Devuelve el rol del usuario
    int getRol() const { return rol; }

    // Modifica el nombre
    void setNombre(const string& n) { nombre = n; }
    // Modifica el apellido
    void setApellido(const string& a) { apellido = a; }
    // Modifica la contraseña
    void setPasswd(const string& pw) { passwd = pw; }
    // Modifica el ID
    void setId(int i) { id = i; }
    // Modifica el rol
    void setRol(int r) { rol = r; }

    // Devuelve una cadena con la información del usuario
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
    MochilaDigital* mochila; // Mochila digital asociada (en el heap)

    // Previene copias accidentales (prohibido copiar estudiantes)
    Estudiante(const Estudiante&) = delete;
    Estudiante& operator=(const Estudiante&) = delete;

public:
    // Constructor por defecto
    Estudiante()
        : Usuario("", "", "", 0, 3), mochila(new MochilaDigital("mochila_default")) {}

    // Constructor con parámetros
    Estudiante(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 3),
          mochila(new MochilaDigital("mochila_" + nombre)) {}

    // Destructor: libera la mochila del heap
    ~Estudiante() {
        delete mochila;
    }

    // Devuelve el puntero a la mochila digital
    MochilaDigital* getMochila() const { return mochila; }

    // Devuelve una cadena con la información del estudiante
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
    ListaDeObjetos<Estudiante*> estudiantes; // Lista de estudiantes asociados

public:
    // Constructor por defecto
    Profesor() : Usuario("", "", "", 0, 2) {}
    // Constructor con parámetros
    Profesor(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 2) {}

    // Agrega un estudiante a la lista de estudiantes asociados
    void agregarEstudiante(Estudiante* est) {
        estudiantes.append(est);
    }

    // Devuelve una cadena con la información del profesor y sus estudiantes
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
    // Constructor por defecto
    Admin() : Usuario("", "", "", 0, 1) {}
    // Constructor con parámetros
    Admin(const string& nombre, const string& apellido, const string& passwd, int id)
        : Usuario(nombre, apellido, passwd, id, 1) {}

    // Devuelve una cadena con la información del administrador
    string toString() const {
        return Usuario::toString() + " [Administrador]";
    }
};

#endif // USUARIO_H