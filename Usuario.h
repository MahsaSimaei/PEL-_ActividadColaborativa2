#ifndef USUARIO_H
#define USUARIO_H
#include "MochilaDigital.h"
#include <string>
using std::string;

class Usuario {
protected:
    std::string nombre;
    std::string apellido;
    std::string passwd;
    int id;
    bool alta;

public:
    Usuario() : nombre(""), apellido(""), passwd(""), id(0), alta(false) {}

    Usuario(std::string nombre, std::string apellido, std::string passwd, int id)
        : nombre(nombre), apellido(apellido), passwd(passwd), id(id), alta(true) {}

    ~Usuario() = default;

    void darAlta() { alta = true; }
    void darBaja() { alta = false; }

    std::string getNombreCompleto() const { return nombre + " " + apellido; }
    std::string getNombre() const { return nombre; }
    std::string getPasswd() const { return passwd; }
    int getId() const { return id; }
    bool isAlta() const { return alta; }

    void setNombre(std::string n) { nombre = n; }
    void setApellido(std::string a) { apellido = a; }

    std::string toString() const {
        std::string estado = alta ? "Alta" : "Baja";
        return "ID: " + std::to_string(id) + " | " + nombre + " " + apellido + " (" + estado + ")";
    }
};

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

#endif
