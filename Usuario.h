#ifndef USUARIO_H
#define USUARIO_H
#include "MochilaDigital.h"
#include <string>
using std::string;

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

    virtual ~Usuario() = default;

    void darAlta() { alta = true; }
    void darBaja() { alta = false; }

    string getNombreCompleto() const { return nombre + " " + apellido; }
    string getNombre() const { return nombre; }
    string getPasswd() const { return passwd; }
    int getId() const { return id; }
    bool isAlta() const { return alta; }

    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }

    virtual string toString() const {
        string estado = alta ? "Alta" : "Baja";
        return "ID: " + std::to_string(id) + " | " + nombre + " " + apellido + " (" + estado + ")";
    }
};

class Estudiante : public Usuario {
private:
    MochilaDigital* mochila; // En el heap

public:
    Estudiante() : Usuario() {
        // Por defecto, usamos "mochila_default" como carpeta
        mochila = new MochilaDigital("mochila_default");
    }

    Estudiante(std::string nombre, std::string apellido, std::string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {
        // Carpeta mochila personalizada por nombre de usuario
        mochila = new MochilaDigital("mochila_" + nombre);
    }

    ~Estudiante() {
        delete mochila;
    }

    MochilaDigital* getMochila() const { return mochila; }
};

#endif
